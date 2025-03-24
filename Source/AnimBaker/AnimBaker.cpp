#include "AnimBaker.h"

#include "AnimationEditorUtils.h"
#include "ILevelSequenceEditorToolkit.h"
#include "ISequencer.h"
#include "LevelSequence.h"
#include "LevelSequenceEditorBlueprintLibrary.h"
#include "MovieScene.h"
#include "MovieSceneToolHelpers.h"
#include "PackageTools.h"
#include "Exporters/AnimSeqExportOption.h"
#include "Factories/AnimSequenceFactory.h"
#include "Framework/Notifications/NotificationManager.h"
#include "MVVM/ViewModelPtr.h"
#include "MVVM/Extensions/ITrackExtension.h"
#include "MVVM/Selection/Selection.h"
#include "MVVM/ViewModels/ObjectBindingModel.h"
#include "Sequencer/MovieSceneControlRigParameterSection.h"
#include "Sequencer/MovieSceneControlRigParameterTrack.h"
#include "Widgets/Notifications/SNotificationList.h"


#define LOCTEXT_NAMESPACE "AnimBaker"


int32 UAnimBaker::CreateNewBakeTarget(ISequencer* SequencerPtr)
{
	int32 NewIndex = INDEX_NONE;
	if (SequencerPtr == nullptr || SequencerPtr->GetViewModel() == nullptr)
	{
		return NewIndex;
	}

	ULevelSequence* LevelSequence = Cast<ULevelSequence>(SequencerPtr->GetFocusedMovieSceneSequence());
	if (LevelSequence == nullptr)
	{
		return NewIndex;
	}

	const FString LevelSequencePath = LevelSequence->GetPackage()->GetName();
	FString AssetPath = FPackageName::GetLongPackagePath(LevelSequencePath);

	using namespace UE::Sequencer;
	TSharedPtr<FSequencerSelection> Selection = SequencerPtr->GetViewModel()->GetSelection();


	FString ObjectBindingName;
	FGuid ObjectBindingGuid;
	TArray<FString> SelectionDisplayLabels;
	TArray<UMovieSceneSection*> Sections;
	for (TWeakViewModelPtr<IOutlinerExtension> OutlinerSelection : Selection->Outliner.GetSelected())
	{
		TViewModelPtr<IOutlinerExtension> OutlinerExtension = OutlinerSelection.Pin();
		if (!ObjectBindingGuid.IsValid())
		{
			TViewModelPtr<IObjectBindingExtension> ObjectBinding = OutlinerExtension.AsModel()->FindAncestorOfType<IObjectBindingExtension>();
			if (ObjectBinding)
			{
				ObjectBindingGuid = ObjectBinding->GetObjectGuid();
			}

			if (TViewModelPtr<IOutlinerExtension> ObjectLevelExtension = ObjectBinding.ImplicitCast())
			{
				ObjectBindingName = ObjectLevelExtension->GetLabel().ToString();
			}
		}

		FString Identifier = OutlinerExtension->GetLabel().ToString();
		SelectionDisplayLabels.Add(Identifier);

		if (TViewModelPtr<ITrackExtension> Track = OutlinerExtension.ImplicitCast())
		{
			if (auto ControlRigTrack = Cast<UMovieSceneControlRigParameterTrack>(Track->GetTrack()))
			{
				Sections.Append(Track->GetSections());
			}
		}
	}

	FText NewBakeTargetName = SelectionDisplayLabels.Num()
		                          ? FText::FromString(FString::Join(SelectionDisplayLabels, TEXT("_")))
		                          : FText::FromString("New BakeTarget");

	const FScopedTransaction Transaction(LOCTEXT("AddAnimBakeTarget", "Add AnimBake Target"), !GIsTransacting);
	Modify();
	UAnimBakeTarget* NewBakeTarget = NewObject<UAnimBakeTarget>(this, NAME_None, RF_Transactional);
	NewBakeTarget->AssetName.Append(ObjectBindingName + TEXT("_") + NewBakeTargetName.ToString() + TEXT("_Seq"));
	NewBakeTarget->AssetPath = AssetPath;
	NewBakeTarget->Guid = ObjectBindingGuid;
	NewBakeTarget->ActiveSections = Sections;
	NewBakeTarget->ExportOptionsPtr = NewObject<UAnimSeqExportOption>(NewBakeTarget, NAME_None, RF_Transactional);

	NewIndex = AnimBakeTargets.Add(NewBakeTarget);
	SequencerPtr->NotifyMovieSceneDataChanged(EMovieSceneDataChangeType::MovieSceneStructureItemAdded);

	return NewIndex;
}

bool UAnimBaker::NotifyBakeComplete(TArray<FBakeResult> BakeResults)
{
	if (BakeResults.IsEmpty())
	{
		return true;
	}

	for (auto Result : BakeResults)
	{
		if (Result.Asset)
		{
			FText NotificationText = FText::Format(
				LOCTEXT("AnimSequenceAssetsCreated", "Anim Sequence asset baked: '{0}'."), FText::FromString(Result.Asset->GetName()));

			FNotificationInfo Info(NotificationText);
			Info.ExpireDuration = 8.0f;
			Info.bUseLargeFont = false;
			Info.Hyperlink = FSimpleDelegate::CreateLambda([Result]()
			{
				GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(Result.Asset);
			});
			Info.HyperlinkText = FText::Format(LOCTEXT("OpenNewPoseAssetHyperlink", "Open {0}"), FText::FromString(Result.Asset->GetName()));

			TSharedPtr<SNotificationItem> Notification = FSlateNotificationManager::Get().AddNotification(Info);
			if (Notification.IsValid())
			{
				Notification->SetCompletionState(SNotificationItem::CS_Success);
			}
		}
	}
	return false;
}

void UAnimBaker::AddSelectedSectionsToTarget(UAnimBakeTarget* Target)
{
	using namespace UE::Sequencer;

	if (TSharedPtr<ISequencer> SequencerPtr = UAnimBaker::GetSequencerFromAsset())
	{
		TSharedPtr<FSequencerSelection> Selection = SequencerPtr->GetViewModel()->GetSelection();
		for (auto OutlinerSelection : Selection->Outliner.GetSelected())
		{
			TViewModelPtr<IOutlinerExtension> OutlinerExtension = OutlinerSelection.Pin();

			if (TViewModelPtr<ITrackExtension> Track = OutlinerExtension.ImplicitCast())
			{
				if (auto ControlRigTrack = Cast<UMovieSceneControlRigParameterTrack>(Track->GetTrack()))
				{
					Target->ActiveSections.Append(Track->GetSections());
				}
			}
		}
	}
}

UObject* UAnimBaker::SoloedTarget = nullptr;
TArray<TTuple<UMovieSceneSection*, bool>> UAnimBaker::PreSoloSectionStates;

void UAnimBaker::SoloTarget(const TObjectPtr<UAnimBakeTarget> BakeTarget)
{
	SoloedTarget = BakeTarget;

	if (!SoloedTarget)
	{
		for (TTuple<UMovieSceneSection*, bool> OriginalSection : PreSoloSectionStates)
		{
			OriginalSection.Key->SetIsActive(OriginalSection.Value);
		}

		PreSoloSectionStates.Reset();
		return;
	}

	TSharedPtr<ISequencer> SequencerPtr = GetSequencerFromAsset();

	UMovieSceneSequence* MovieSceneSequence = SequencerPtr->GetFocusedMovieSceneSequence();
	TArray<UMovieSceneSection*> Sections = MovieSceneSequence->GetMovieScene()->GetAllSections();

	if (PreSoloSectionStates.IsEmpty())
	{
		for (auto Section : Sections)
		{
			if (auto ControlRigSection = Cast<UMovieSceneControlRigParameterSection>(Section))
			{
				PreSoloSectionStates.Emplace(ControlRigSection, ControlRigSection->IsActive());
				Section->SetIsActive(false);
			}
		}
	}

	for (auto TargetSection : BakeTarget->ActiveSections)
	{
		TargetSection->SetIsActive(true);
	}

	// MovieScene->SetViewRange(BakeTarget->ExportOptionsPtr->CustomStartFrame, BakeTarget->ExportOptionsPtr->CustomEndFrame);
}

void UAnimBaker::BakeTarget(const TObjectPtr<UAnimBakeTarget> TargetToBake)
{
	TSharedPtr<ISequencer> SequencerPtr = GetSequencerFromAsset();
	if (!SequencerPtr.IsValid())
	{
		return;
	}

	if (!TargetToBake)
	{
		return;
	}

	AActor* BoundActor = Cast<AActor>(SequencerPtr->FindSpawnedObjectOrTemplate(TargetToBake->Guid));
	if (!BoundActor)
		return;

	USkeletalMeshComponent* SkelMeshComp = BoundActor->FindComponentByClass<USkeletalMeshComponent>();
	if (SkelMeshComp)
	{
		USkeleton* Skeleton = nullptr;
		USkeletalMesh* SkeletalMesh = SkelMeshComp->GetSkeletalMeshAsset();
		if (SkeletalMesh)
		{
			Skeleton = SkeletalMesh->GetSkeleton();
		}

		if (!Skeleton)
		{
			return;
		}

		const FString PackageName = UPackageTools::SanitizePackageName(TargetToBake->AssetPath + TEXT("/") + TargetToBake->AssetName);

		UPackage* Pkg = CreatePackage(*PackageName);
		UObject* AnimationAsset = StaticFindObject(UObject::StaticClass(), Pkg, *TargetToBake->AssetName);
		if (!AnimationAsset)
		{
			UPackage* Package = CreatePackage(*TargetToBake->AssetPath);
			if (!Package)
			{
				return;
			}

			UAnimSequenceFactory* Factory = NewObject<UAnimSequenceFactory>();
			Factory->TargetSkeleton = Skeleton;
			Factory->PreviewSkeletalMesh = SkeletalMesh;

			FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");
			AnimationAsset = AssetToolsModule.Get().CreateAsset(TargetToBake->AssetName, TargetToBake->AssetPath, UAnimSequence::StaticClass(),
			                                                    Factory);
		}

		FBakeResult NewBakeResult{
			RenderAnimSequenceForTarget(AnimationAsset, SkelMeshComp, TargetToBake),
			AnimationAsset
		};
		NotifyBakeComplete({NewBakeResult});
	}

	SequencerPtr->RequestEvaluate();
}

void UAnimBaker::RebakeAll()
{
	TSharedPtr<ISequencer> SequencerPtr = GetSequencerFromAsset();
	if (!SequencerPtr.IsValid())
	{
		return;
	}

	TArray<FBakeResult> BakeResults;
	for (UObject* TargetObject : AnimBakeTargets)
	{
		UAnimBakeTarget* TargetToBake = Cast<UAnimBakeTarget>(TargetObject);
		if (!TargetToBake)
		{
			continue;
		}

		if (TargetToBake->bIsLocked)
		{
			continue;
		}


		AActor* BoundActor = Cast<AActor>(SequencerPtr->FindSpawnedObjectOrTemplate(TargetToBake->Guid));
		if (!BoundActor)
			continue;

		USkeletalMeshComponent* SkelMeshComp = BoundActor->FindComponentByClass<USkeletalMeshComponent>();
		if (SkelMeshComp)
		{
			USkeleton* Skeleton = nullptr;
			USkeletalMesh* SkeletalMesh = SkelMeshComp->GetSkeletalMeshAsset();
			if (SkeletalMesh)
			{
				Skeleton = SkeletalMesh->GetSkeleton();
			}

			if (!Skeleton)
			{
				continue;
			}

			const FString PackageName = UPackageTools::SanitizePackageName(TargetToBake->AssetPath + TEXT("/") + TargetToBake->AssetName);

			UPackage* Pkg = CreatePackage(*PackageName);
			UObject* AnimationAsset = StaticFindObject(UObject::StaticClass(), Pkg, *TargetToBake->AssetName);
			if (!AnimationAsset)
			{
				UPackage* Package = CreatePackage(*TargetToBake->AssetPath);
				if (!Package)
				{
					continue;
				}

				UAnimSequenceFactory* Factory = NewObject<UAnimSequenceFactory>();
				Factory->TargetSkeleton = Skeleton;
				Factory->PreviewSkeletalMesh = SkeletalMesh;

				FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");
				AnimationAsset = AssetToolsModule.Get().CreateAsset(TargetToBake->AssetName, TargetToBake->AssetPath, UAnimSequence::StaticClass(),
				                                                    Factory);
			}

			FBakeResult NewBakeResult{
				RenderAnimSequenceForTarget(AnimationAsset, SkelMeshComp, TargetToBake),
				AnimationAsset
			};
			BakeResults.Add(NewBakeResult);
		}
	}

	SequencerPtr->RequestEvaluate();

	NotifyBakeComplete(BakeResults);
}

TSharedPtr<ISequencer> UAnimBaker::GetSequencerFromAsset()
{
	ULevelSequence* LevelSequence = ULevelSequenceEditorBlueprintLibrary::GetCurrentLevelSequence();
	IAssetEditorInstance* AssetEditor = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->FindEditorForAsset(LevelSequence, false);
	ILevelSequenceEditorToolkit* LevelSequenceEditor = static_cast<ILevelSequenceEditorToolkit*>(AssetEditor);
	TSharedPtr<ISequencer> SequencerPtr = LevelSequenceEditor ? LevelSequenceEditor->GetSequencer() : nullptr;
	return SequencerPtr;
}

UAnimBaker* UAnimBaker::GetAnimBaker(ISequencer* SequencerPtr)
{
	if (!SequencerPtr)
	{
		return nullptr;
	}

	ULevelSequence* LevelSequence = Cast<ULevelSequence>(SequencerPtr->GetFocusedMovieSceneSequence());
	return GetAnimBaker(LevelSequence);
}

UAnimBaker* UAnimBaker::GetAnimBaker(ULevelSequence* LevelSequence)
{
	if (!LevelSequence)
	{
		return nullptr;
	}
	if (LevelSequence && LevelSequence->GetClass()->ImplementsInterface(UInterface_AssetUserData::StaticClass()))
	{
		if (IInterface_AssetUserData* AssetUserDataInterface = Cast<IInterface_AssetUserData>(LevelSequence))
		{
			UAnimBaker* AnimBaker = AssetUserDataInterface->GetAssetUserData<UAnimBaker>();
			if (!AnimBaker)
			{
				AnimBaker = NewObject<UAnimBaker>(LevelSequence, NAME_None, RF_Public | RF_Transactional);
				AssetUserDataInterface->AddAssetUserData(AnimBaker);
			}
			return AnimBaker;
		}
	}
	return nullptr;
}

bool UAnimBaker::RenderAnimSequenceForTarget(UObject* AnimAsset, USkeletalMeshComponent* SkelMeshComp, UAnimBakeTarget* BakeTarget)
{
	if (BakeTarget->bIsLocked)
	{
		return false;
	}

	TSharedPtr<ISequencer> SequencerPtr = GetSequencerFromAsset();

	bool bResult = false;
	UAnimSequence* AnimSequence = Cast<UAnimSequence>(AnimAsset);
	if (AnimSequence)
	{
		UMovieSceneSequence* MovieSceneSequence = SequencerPtr->GetFocusedMovieSceneSequence();
		UMovieSceneSequence* RootMovieSceneSequence = SequencerPtr->GetRootMovieSceneSequence();

		TArray<TTuple<UMovieSceneSection*, bool>> OriginalSectionStates;
		if(BakeTarget->ActiveSections.Num() > 0)
		{
			TArray<UMovieSceneSection*> Sections = MovieSceneSequence->GetMovieScene()->GetAllSections();
			for (auto Section : Sections)
			{
				if (auto ControlRigSection = Cast<UMovieSceneControlRigParameterSection>(Section))
				{
					OriginalSectionStates.Emplace(ControlRigSection, ControlRigSection->IsActive());
					Section->SetIsActive(false);
				}
			}
	
			for (auto TargetSection : BakeTarget->ActiveSections)
			{
				TargetSection->SetIsActive(true);
			}
		}
		
		SequencerPtr->ForceEvaluate();
		{
			SkelMeshComp->TickAnimation(0.01f, false);

			SkelMeshComp->RefreshBoneTransforms();
			SkelMeshComp->RefreshFollowerComponents();
			SkelMeshComp->UpdateComponentToWorld();
			SkelMeshComp->FinalizeBoneTransform();
			SkelMeshComp->MarkRenderTransformDirty();
			SkelMeshComp->MarkRenderDynamicDataDirty();
		}


		FMovieSceneSequenceTransform RootToLocalTransform = SequencerPtr->GetFocusedMovieSceneSequenceTransform();
		FAnimExportSequenceParameters AESP;
		AESP.Player = SequencerPtr.Get();
		AESP.RootToLocalTransform = RootToLocalTransform;
		AESP.MovieSceneSequence = MovieSceneSequence;
		AESP.RootMovieSceneSequence = RootMovieSceneSequence;
		bResult = MovieSceneToolHelpers::ExportToAnimSequence(AnimSequence, BakeTarget->ExportOptionsPtr, AESP, SkelMeshComp);

		for (TTuple<UMovieSceneSection*, bool> OriginalSection : OriginalSectionStates)
		{
			OriginalSection.Key->SetIsActive(OriginalSection.Value);
		}
	}

	return bResult;
}

void UAnimBaker::OnSequencerSaved(ISequencer&)
{
	//RebakeAll();
}

#undef LOCTEXT_NAMESPACE
