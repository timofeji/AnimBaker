// Copyright Epic Games, Inc. All Rights Reserved.
#include "SAnimBaker.h"
#include "AnimBaker.h"
#include "AnimBakerStyle.h"
#include "Templates/SharedPointer.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Views/STreeView.h"
#include "ControlRigEditor/Private/ControlRigEditorStyle.h"
#include "Containers/Set.h"
#include "Widgets/SWidget.h"
#include "EditMode/ControlRigEditMode.h"
#include "Toolkits/IToolkitHost.h"
#include "MovieScene.h"
#include "Editor.h"
#include "ISequencer.h"
#include "SPrimaryButton.h"
#include "Dialogs/DlgPickPath.h"
#include "Exporters/AnimSeqExportOption.h"
#include "Modules/ModuleManager.h"
#include "MVVM/Selection/Selection.h"
#include "MVVM/ViewModels/SequencerEditorViewModel.h"

FSimpleDelegate SAnimBaker::OnSourceDataUpdated;

#define LOCTEXT_NAMESPACE "AnimBaker"


//////////////////////////////////////////////////////////////
/// SAnimBakeSectionRow  
///////////////////////////////////////////////////////////

class SAnimBakeSectionRow : public STableRow<FAnimBakerElement>
{
	SLATE_BEGIN_ARGS(SAnimBakeSectionRow)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, FAnimBakerElement Item)
	{
		UMovieSceneSection* SectionPtr = Cast<UMovieSceneSection>(Item->ObjectPtr);
		if (!SectionPtr)
		{
			return;
		}

		const UMovieSceneTrack* Track = SectionPtr->GetTypedOuter<UMovieSceneTrack>();
		const FText DisplayName = Track->GetTrackRowDisplayName(SectionPtr->GetRowIndex());

		TSharedRef<SWidget> DeleteButton = SNew(SButton)
		.OnClicked_Lambda([Item]
		                                                {
			                                                Item->Remove();
			                                                SAnimBaker::OnSourceDataUpdated.Execute();
			                                                return FReply::Handled();
		                                                })
			.HAlign(HAlign_Right)
			.ButtonStyle(FAppStyle::Get(), "SimpleButton")
			.Content()
		[
			SNew(SImage)
			.Image(FAppStyle::GetBrush("Icons.X"))
		];

		STableRow<FAnimBakerElement>::Construct(
			STableRow<FAnimBakerElement>::FArguments()
			.Padding(0.0f),
			InOwnerTable);

		ChildSlot
		[
			SNew(SBorder)
					.BorderImage(FAppStyle::Get().GetBrush("NoBorder"))
					 .HAlign(HAlign_Fill)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				  .AutoWidth()
				  .VAlign(VAlign_Center)
				  .Padding(2.0f, 0.0f, 2.0f, 0.0f)
				[
					SNew(SExpanderArrow, SharedThis(this))
							.IndentAmount(10.0f).ShouldDrawWires(true)
				]
				+ SHorizontalBox::Slot()
				  .FillWidth(1.f)
				  .VAlign(VAlign_Center)
				  .Padding(2.0f, 0.0f, 2.0f, 0.0f)
				[
					SNew(STextBlock)
					.Text(DisplayName)
				]
				+ SHorizontalBox::Slot()
				  .AutoWidth()
				  .VAlign(VAlign_Center)
				  .HAlign(HAlign_Right)
				  .Padding(2.0f, 0.0f, 2.0f, 0.0f)
				[
					DeleteButton
				]
			]
		];
	}
};


//////////////////////////////////////////////////////////////
/// SAnimBakeTargetItemRow  
///////////////////////////////////////////////////////////
class SAnimBakeTargetItemRow : public STableRow<FAnimBakerElement>
{
	SLATE_BEGIN_ARGS(SAnimBakeTargetItemRow)
		{
		}

	SLATE_END_ARGS()

	TObjectPtr<UAnimBakeTarget> TargetPtr;

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable,
	               FAnimBakerElement InTargetPtr)
	{
		TargetPtr = Cast<UAnimBakeTarget>(InTargetPtr->ObjectPtr);
		if (!TargetPtr)
		{
			return;
		}

		STableRow<FAnimBakerElement>::Construct(
			STableRow<FAnimBakerElement>::FArguments()
			.Padding(0.0f),
			InOwnerTable);

		TSharedRef<SButton> AssetButton = SNew(SButton)
		.OnClicked_Lambda([this]
		                                               {
			                                               GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->
			                                                        OpenEditorForAsset(
				                                                        TargetPtr->AssetPath + TEXT("/") + TargetPtr->
				                                                        AssetName);

			                                               return FReply::Handled();
		                                               })
		.ToolTipText(FText::FromString(FString::Printf(TEXT("Open Linked Asset -- %s"), *TargetPtr->AssetName)))
		.ButtonStyle(FAppStyle::Get(), "FlatButton.Dark")
		.HAlign(HAlign_Fill)
		.Content()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			  .AutoWidth()
			  .VAlign(VAlign_Center)
			  .HAlign(HAlign_Fill)
			[
				SNew(STextBlock)
				.AutoWrapText(true)
				.Justification(ETextJustify::Left)
				.Text_Lambda([this] { return FText::FromString(TargetPtr->AssetName); })
				.TextStyle(FAppStyle::Get(), "FlatButton.DefaultTextStyle")
			]
			+ SHorizontalBox::Slot()
			  .FillWidth(1.f)
			  .VAlign(VAlign_Center)
			  .HAlign(HAlign_Right)
			[
				SNew(SImage)
				.Image(FAppStyle::GetBrush("ContentBrowser.AssetActions.OpenInExternalEditor"))
			]
		];


		TSharedRef<SWidget> LockButton = SNew(SCheckBox)
        	.Padding(3.0f)
        	.ToolTipText(
			                                                LOCTEXT("AnimTargetLockTooltip",
			                                                        "Lock BakeTarget, preventing it from being exported on save "))
        	.Style(FAppStyle::Get(), "ToggleButtonCheckbox")
        	.OnCheckStateChanged_Lambda([this](ECheckBoxState InCheckBoxState)
		                                                {
			                                                TargetPtr->bIsLocked =
				                                                InCheckBoxState == ECheckBoxState::Checked
					                                                ? true
					                                                : false;
		                                                })
        	.IsChecked_Lambda([this]
		                                                {
			                                                return TargetPtr->bIsLocked
				                                                       ? ECheckBoxState::Checked
				                                                       : ECheckBoxState::Unchecked;
		                                                })
		[
			SNew(SImage)
			.Image(FAppStyle::GetBrush("Sequencer.Column.Locked"))
		];

		TSharedRef<SWidget> SoloButton = SNew(SCheckBox)
        	.Padding(3.0f)
        	.Style(FAppStyle::Get(), "ToggleButtonCheckbox")
        	.OnCheckStateChanged_Lambda([this](ECheckBoxState InCheckBoxState)
		                                                {
			                                                UAnimBaker::SoloTarget(
				                                                InCheckBoxState == ECheckBoxState::Checked
					                                                ? TargetPtr
					                                                : nullptr);
		                                                })
        	.IsChecked_Lambda([this]
		                                                {
			                                                return UAnimBaker::SoloedTarget == TargetPtr.Get()
				                                                       ? ECheckBoxState::Checked
				                                                       : ECheckBoxState::Unchecked;
		                                                })
        	.ToolTipText(LOCTEXT("AnimTargetSoloButton_Tooltip",
                                 "Solo out the sections that are part of this bake target and set the sequencer length to the custom render length"))
		[
			SNew(SImage)
			.Image(FAppStyle::GetBrush("Sequencer.Column.Solo"))
		];

		TSharedRef<SWidget> BakeButton = SNew(SButton)
        	.OnClicked_Lambda([this]
		                                              {
			                                              UAnimBaker::BakeTarget(TargetPtr);
			                                              return FReply::Handled();
		                                              })
        					.HAlign(HAlign_Right)
        					.ButtonStyle(FAppStyle::Get(), "SimpleButton")
        					.ToolTipText(LOCTEXT("RefreshButtonTooltip",
                                                 "Bake Target and outputs the corresponding assets"))
        					.Content()
		[
			SNew(SImage)
			.Image(FControlRigEditorStyle::Get().GetBrush("ControlRig.AnimBakerRefresh"))
		];

		TSharedRef<SWidget> DeleteButton = SNew(SButton)
        	         			.OnClicked_Lambda([InTargetPtr]
		                                                {
			                                                InTargetPtr->Remove();
			                                                SAnimBaker::OnSourceDataUpdated.Execute();
			                                                return FReply::Handled();
		                                                })
        	         				.HAlign(HAlign_Right)
        	         				.ButtonStyle(FAppStyle::Get(), "SimpleButton")
        	         				.ButtonColorAndOpacity(FLinearColor(FColor(255, 40, 40)))
        	         				.Content()
		[
			SNew(SImage)
			.Image(FAppStyle::GetBrush("Icons.Delete"))
		];


		ChildSlot
		[
			SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("NoBorder"))
				 .HAlign(HAlign_Fill)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				  .AutoWidth()
				  .VAlign(VAlign_Center)
				  .Padding(2.0f, 2.0f, 2.0f, 2.0f)
				[

					SNew(SExpanderArrow, SharedThis(this))
					.IndentAmount(2.0f)
				]
				+ SHorizontalBox::Slot()
				  .FillWidth(1.f)
				  .Padding(1, 0)
				  .VAlign(VAlign_Center)
				[
					AssetButton
				]
				+ SHorizontalBox::Slot()
				  .AutoWidth()
				  .Padding(1, 0)
				  .VAlign(VAlign_Center)
				[
					SNew(SBorder)
					.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						  .AutoWidth()
						  .VAlign(VAlign_Center)
						[
							LockButton
						]
						+ SHorizontalBox::Slot()
						  .AutoWidth()
						  .VAlign(VAlign_Center)
						[
							SoloButton
						]
						+ SHorizontalBox::Slot()
						  .AutoWidth()
						  .VAlign(VAlign_Center)
						[
							BakeButton
						]
						+ SHorizontalBox::Slot()
						  .AutoWidth()
						  .VAlign(VAlign_Center)
						[
							DeleteButton
						]
					]
				]
			]
		];
	}
};

//////////////////////////////////////////////////////////////
/// SAnimBakerSettingsWindow 
///////////////////////////////////////////////////////////

class SAnimBakerSettingsWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SAnimBakerSettingsWindow)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UAnimBakeTarget* InBakerTarget);
	virtual bool SupportsKeyboardFocus() const override { return true; }

private:
	UAnimBakeTarget* TargetPtr;
	TSharedPtr<class IDetailsView> DetailsView;
};

void SAnimBakerSettingsWindow::Construct(const FArguments& InArgs, UAnimBakeTarget* InBakerTarget)
{
	using namespace UE::Sequencer;
	TargetPtr = InBakerTarget;

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(
		"PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bAllowSearch = false;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(TargetPtr->ExportOptionsPtr.Get());

	TSharedRef<SBox> InspectorBox = SNew(SBox);
	InspectorBox->SetContent(DetailsView->AsShared());


	TSharedRef<SDlgPickPath> PickTargetPathDlg =
		SNew(SDlgPickPath)
			.DefaultPath(FText::FromString(TargetPtr->AssetPath))
			.Title(LOCTEXT("ChooseBakeTargetOutputPathTitle", "Choose Path where the baked asset will be saved to"));


	TSharedRef<SBorder> PathGroup =
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("ToolPanel.DarkGroupBorder"))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Fill)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(STextBlock)
							.Font(FAppStyle::GetFontStyle("CurveEd.LabelFont"))
							.Text(NSLOCTEXT("BakeAssetName", "BakedAssetPath", "Asset Name: "))
				]
				+ SHorizontalBox::Slot()
				  .Padding(5, 0, 0, 0)
				  .FillWidth(1.f)
				  .VAlign(VAlign_Fill)
				[
					SNew(SEditableTextBox)
							.Font(FAppStyle::GetFontStyle(TEXT("PropertyWindow.NormalFont")))
							.Text(FText::FromString(TargetPtr->AssetName))
							.OnTextChanged_Lambda([this](const FText& InExpressionText)
					                      {
						                      TargetPtr->AssetName = InExpressionText.ToString();
					                      })
				]
			]

			+ SVerticalBox::Slot()
			  .HAlign(HAlign_Fill)
			  .FillHeight(1.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				  .AutoWidth()
				  .VAlign(VAlign_Center)
				[
					SNew(STextBlock)
								.Font(FAppStyle::GetFontStyle("CurveEd.LabelFont"))
								.Text(NSLOCTEXT("BakeAssetPath", "BakedAssetPath", "Path: "))
				]
				+ SHorizontalBox::Slot()
				  .Padding(5, 0, 0, 0)
				  .FillWidth(2.0f)
				  .VAlign(VAlign_Bottom)
				[
					SNew(SEditableTextBox)
							.Font(FAppStyle::GetFontStyle(TEXT("PropertyWindow.NormalFont")))
							.Text_Lambda([this] { return FText::FromString(TargetPtr->AssetPath); })
							.OnTextChanged_Lambda([this](const FText& InExpressionText)
					                      {
						                      TargetPtr->AssetPath = InExpressionText.ToString();
					                      })
				]

				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
						.Text(FText::FromString(TEXT("...")))
						.OnClicked_Lambda([PickTargetPathDlg, this]
					             {
						             EAppReturnType::Type ReturnType = PickTargetPathDlg->ShowModal();

						             if (ReturnType == EAppReturnType::Ok)
						             {
							             TargetPtr->AssetPath = PickTargetPathDlg->GetPath().ToString();
						             }

						             if (ReturnType == EAppReturnType::Cancel)
						             {
							             return FReply::Handled();
						             }

						             return FReply::Handled();
					             })
				]
			]
		];

	TSharedRef<SVerticalBox> BakeTargetSettings =
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		  .AutoHeight()
		  .HAlign(HAlign_Fill)
		  .Padding(0, 5, 0, 1)
		[
			PathGroup
		]
		+ SVerticalBox::Slot()
		  .AutoHeight()
		  .HAlign(HAlign_Fill)
		  .Padding(0, 0, 0, 1)
		[
			InspectorBox
		];

	ChildSlot
	[
		SNew(SBox)
		.Padding(0.f)
		.MinDesiredWidth(3.f)
		[
			BakeTargetSettings
		]
	];
}


//////////////////////////////////////////////////////////////
/// SAnimBaker
///////////////////////////////////////////////////////////

void SAnimBaker::RefreshSourceData()
{
	BakerUIElements.Reset();

	if (TSharedPtr<ISequencer> SequencerPtr = UAnimBaker::GetSequencerFromAsset())
	{
		if (UAnimBaker* AnimBakerPtr = UAnimBaker::GetAnimBaker(SequencerPtr.Get()))
		{
			for (auto TargetPtr : AnimBakerPtr->AnimBakeTargets)
			{
				BakerUIElements.Add(MakeShared<FAnimBakerUIElement>(TargetPtr, AnimBakerPtr, true));
			}

			AnimBaker = AnimBakerPtr;
		}
	}

	BakeListView->RequestTreeRefresh();
}

FReply SAnimBaker::OnAddNewTargetClicked()
{
	if (ISequencer* SequencerPtr = GetSequencer())
	{
		if (UAnimBaker* AnimBakerPtr = UAnimBaker::GetAnimBaker(SequencerPtr))
		{
			int32 Index = AnimBakerPtr->CreateNewBakeTarget(SequencerPtr);
			if (Index != INDEX_NONE)
			{
				RefreshSourceData();
			}
		}
	}

	return FReply::Handled();
}

TSharedPtr<SWidget> SAnimBaker::ConstructBakeTargetItemContextMenu()
{
	if (TSharedPtr<ISequencer> SequencerPtr = UAnimBaker::GetSequencerFromAsset())
	{
		const bool bShouldCloseWindowAfterMenuSelection = true;
		FMenuBuilder MenuBuilder(bShouldCloseWindowAfterMenuSelection, nullptr);

		TArray<FAnimBakerElement> Selected;
		BakeListView->GetSelectedItems(Selected);


		if (!Selected.Num())
		{
			return nullptr;
		}

		MenuBuilder.BeginSection("AnimBakeContextMenuTarget", LOCTEXT("AnimBakeTargetContextMenu", "Bake Target"));
		{
			FUIAction Action = FUIAction(FExecuteAction::CreateRaw((this), &SAnimBaker::DeleteSelectedElements));
			const FText Label = LOCTEXT("DeletaTarget", "Delete Target");
			const FText ToolTipText = LOCTEXT("DeleteTargettooltip", "Delete selected targets");
			MenuBuilder.AddMenuEntry(Label, ToolTipText,
			                         FSlateIcon(FAppStyle::GetAppStyleSetName(),
			                                    "ContentBrowser.AssetActions.Duplicate"),
			                         Action);
		}
		MenuBuilder.EndSection();

		if (UAnimBakeTarget* Target = Cast<UAnimBakeTarget>(Selected[0]->ObjectPtr))
		{
			TSharedPtr<UE::Sequencer::FSequencerSelection> Selection = SequencerPtr->GetViewModel()->GetSelection();
			if (Selection->Outliner.GetSelected().Num() > 0)
			{
				FUIAction Action = FUIAction(
					FExecuteAction::CreateRaw((this), &SAnimBaker::AddSelectedSectionsToTarget));
				const FText Label = LOCTEXT("AddSelectedTracks", "Add Selected Sections");
				const FText ToolTipText = LOCTEXT("RenameTargetTooltip", "Rename selected target");
				MenuBuilder.AddMenuEntry(Label, ToolTipText,
				                         FSlateIcon(FAppStyle::GetAppStyleSetName(),
				                                    "ContentBrowser.AssetActions.Rename"),
				                         Action);
			}
			TSharedRef<SAnimBakerSettingsWindow> BakerSettings =
				SNew(SAnimBakerSettingsWindow, Target);

			MenuBuilder.AddWidget(BakerSettings, LOCTEXT("AnimTargetContextMenuTarget", ""));
		}
		return MenuBuilder.MakeWidget();
	}

	return nullptr;
}

// SAnimBaker::~SAnimBaker()
// {
// 	if (TSharedPtr<ISequencer> SequencerPtr = UAnimBaker::GetSequencerFromAsset())
// 	{
// 		SequencerPtr->OnPostSave().Remove(SequencerSavedHandle);
// 	}
//
// 	if (OnSourceDataUpdated.IsBound())
// 	{
// 		OnSourceDataUpdated.Unbind();
// 	}
// }
//

void SAnimBaker::Construct(const FArguments& InArgs)
{
	if (TSharedPtr<ISequencer> SequencerPtr = UAnimBaker::GetSequencerFromAsset())
	{
		if (UAnimBaker* AnimBakerPtr = UAnimBaker::GetAnimBaker(SequencerPtr.Get()))
		{
			SequencerSavedHandle = SequencerPtr->OnPostSave().AddUObject(AnimBakerPtr, &UAnimBaker::OnSequencerSaved);

			for (auto TargetPtr : AnimBakerPtr->AnimBakeTargets)
			{
				BakerUIElements.Add(MakeShared<FAnimBakerUIElement>(TargetPtr, AnimBakerPtr, true));
			}

			AnimBaker = AnimBakerPtr;
		}
	}

	OnSourceDataUpdated.BindSP(this, &SAnimBaker::RefreshSourceData);

	TSharedRef<SButton> AddBakeTargetButton = SNew(SButton)
	.OnClicked(this, &SAnimBaker::OnAddNewTargetClicked)
	.Text(LOCTEXT("AnimBaker", "Add new Bake Item"))
	.ToolTipText(LOCTEXT("AnimBakerTooltip", "Add Skeletal AnimSequence Bake Item"))
	.ContentPadding(FMargin(.0f, 1.f, .0f, 1.f))
	.ButtonStyle(FAppStyle::Get(), "FlatButton.Success")
	.Content()
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		  .AutoWidth()
		  .VAlign(VAlign_Center)
		[
			SNew(SImage)
			.Image(FAppStyle::GetBrush("Persona.AssetActions.CreateAnimAsset"))
		]

		+ SHorizontalBox::Slot()
		  .FillWidth(1.0f)
		  .VAlign(VAlign_Center)
		[
			SNew(STextBlock)
						.Justification(ETextJustify::Center)
						.Text(NSLOCTEXT("AnimExportOptionsWindow_Bake", "BakeAnimSequence",
						                "New Target"))
						.TextStyle(FAppStyle::Get(), "FlatButton.DefaultTextStyle")
		]
	];

	TSharedRef<SButton> RegenerateAllItemsButton =
		SNew(SButton)
			.Text(LOCTEXT("BakeAllText", "Bake All"))
			.ToolTipText(LOCTEXT("RefreshButtonTooltip",
			                     "Regenerates all Linked BakeTargets and outputs the corresponding assets"))
			.OnClicked_Lambda([this]()
		             {
			             AnimBaker->RebakeAll();
			             return FReply::Handled();
		             })
		.Content()
		[
			SNew(SImage)
			.Image(FAnimBakerStyle::Get().GetBrush("AnimBaker.Icon"))
		];

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		  .Padding(FMargin(.0f, 0.f, 0.f, 0.f))
		  .AutoHeight()
		[
			SAssignNew(BakeListView, STreeView<FAnimBakerElement >)
				.OnGenerateRow(this, &SAnimBaker::HandleGenerateRow)
				.OnGetChildren(this, &SAnimBaker::HandleGetChildren)
				.OnContextMenuOpening(this, &SAnimBaker::ConstructBakeTargetItemContextMenu)
				.TreeViewStyle(&FAppStyle::Get().GetWidgetStyle<FTableViewStyle>("PropertyTable.InViewport.ListView"))
				.TreeItemsSource(&BakerUIElements)
				.SelectionMode(ESelectionMode::Multi)
				.HeaderRow
			                                                       (
				                                                       SNew(SHeaderRow)

				                                                       + SHeaderRow::Column("TargetAsset")
				                                                         .HAlignCell(HAlign_Fill)
				                                                         .FillWidth(50.f)
				                                                         .DefaultLabel(LOCTEXT("NewBakeTarget", ""))
				                                                       [
					                                                       AddBakeTargetButton
				                                                       ]
				                                                       + SHeaderRow::Column("TargetActions")
				                                                         .ManualWidth(100.f)
				                                                         .HAlignHeader(HAlign_Fill)
				                                                         .HAlignCell(HAlign_Fill)
				                                                         .DefaultLabel(LOCTEXT(
					                                                         "BakeOpenColumnName", "Target Asset"))
				                                                       [
					                                                       RegenerateAllItemsButton
				                                                       ]
			                                                       )
		]
	];
}

ISequencer* SAnimBaker::GetSequencer() const
{
	// if (FControlRigEditMode* EditMode = static_cast<FControlRigEditMode*>(ModeTools->GetActiveMode(
	// 	FControlRigEditMode::ModeName)))
	// {
	// 	TWeakPtr<ISequencer> Sequencer = EditMode->GetWeakSequencer();
	// 	return Sequencer.Pin().Get();
	// }
	return nullptr;
}

void SAnimBaker::DeleteElement(FAnimBakerElement Element)
{
	const FScopedTransaction Transaction(LOCTEXT("DeleteAnimTarget_Transaction", "Delete BakeTarget"), !GIsTransacting);
	Element->Remove();
	RefreshSourceData();
}

void SAnimBaker::DeleteSelectedElements()
{
	TArray<FAnimBakerElement> Selected;
	BakeListView->GetSelectedItems(Selected);

	if (Selected.Num() > 0)
	{
		if (ISequencer* SequencerPtr = GetSequencer())
		{
			if (UAnimBaker* AnimBakerPtr = UAnimBaker::GetAnimBaker(SequencerPtr))
			{
				const FScopedTransaction
					Transaction(
						LOCTEXT("DeleteAnimTargets_Transaction", "Delete Selected BakeTarget Elements"),
						!GIsTransacting);

				for (FAnimBakerElement Element : Selected)
				{
					Element->Remove();
				}
			}
		}
		RefreshSourceData();
	}
}


void SAnimBaker::AddSelectedSectionsToTarget()
{
	TArray<FAnimBakerElement> Selected;
	BakeListView->GetSelectedItems(Selected);

	if (Selected.Num() > 0)
	{
		if (ISequencer* SequencerPtr = GetSequencer())
		{
			if (UAnimBaker* AnimBakerPtr = UAnimBaker::GetAnimBaker(SequencerPtr))
			{
				const FScopedTransaction Transaction(
					LOCTEXT("AddSectionsToTarget_Transaction", "Add Sections to BakeTarget"), !GIsTransacting);
				FAnimBakerElement Ptr = Selected[0];
				if (UAnimBakeTarget* Target = Cast<UAnimBakeTarget>(Selected[0]->ObjectPtr))
				{
					AnimBakerPtr->AddSelectedSectionsToTarget(Target);
				}
			}
		}
		RefreshSourceData();
	}
}

TSharedRef<ITableRow> SAnimBaker::HandleGenerateRow(FAnimBakerElement Item,
                                                    const TSharedRef<STableViewBase>& OwnerTable)
{
	if (Item->bIsTarget)
		return SNew(SAnimBakeTargetItemRow, OwnerTable, Item);
	else
		return SNew(SAnimBakeSectionRow, OwnerTable, Item);
}

void SAnimBaker::HandleGetChildren(FAnimBakerElement InItem, TArray<FAnimBakerElement>& OutChildren)
{
	if (auto BakeTarget = Cast<UAnimBakeTarget>(InItem->ObjectPtr))
	{
		for (int i = 0; i < BakeTarget->ActiveSections.Num(); i++)
		{
			UMovieSceneSection* Section = BakeTarget->ActiveSections[i];
			if (Section)
			{
				OutChildren.Add(MakeShared<FAnimBakerUIElement>(Section, BakeTarget, false));
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
