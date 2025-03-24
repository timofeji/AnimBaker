// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "AnimBaker.h"
#include "ControlRigEditor/Private/EditMode/ControlRigBaseDockableView.h"
#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"
#include "Misc/Guid.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class UControlRig;
class FControlRigEditMode;
struct FRigControlElement;

class UAnimBakeTarget;

struct FAnimBakerUIElement : public TSharedFromThis<FAnimBakerUIElement>
{
	FAnimBakerUIElement(UObject* InPtr, UObject* InParentPtr = nullptr, bool InIsTarget = false)
	{
		ObjectPtr = InPtr;
		ParentPtr = InParentPtr;
		bIsTarget = InIsTarget;
	}

	UObject* ObjectPtr;
	UObject* ParentPtr;
	bool bIsTarget = false;

	void Remove()
	{
		if (UAnimBakeTarget* TargetPtr = Cast<UAnimBakeTarget>(ObjectPtr))
		{
			if (UAnimBaker* ParentBakerPtr = Cast<UAnimBaker>(ParentPtr))
			{
				ParentBakerPtr->AnimBakeTargets.Remove(TargetPtr);
			}
		}

		if (UMovieSceneSection* SectionPtr = Cast<UMovieSceneSection>(ObjectPtr))
		{
			if (UAnimBakeTarget* ParentTargetPtr = Cast<UAnimBakeTarget>(ParentPtr))
			{
				ParentTargetPtr->ActiveSections.Remove(SectionPtr);
			}
		}
	};
};

typedef TSharedRef<FAnimBakerUIElement> FAnimBakerElement;


class SAnimBaker : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SAnimBaker)
		{
		}
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);

	ISequencer* GetSequencer() const;
	
	void RefreshSourceData();
	
	void DeleteSelectedElements();

	void DeleteElement(FAnimBakerElement Element);

	void AddSelectedSectionsToTarget();
	
	FReply OnAddNewTargetClicked();
	
	TSharedPtr<SWidget> ConstructBakeTargetItemContextMenu();

	TSharedPtr<STreeView<TSharedRef<FAnimBakerUIElement> >> BakeListView;

	TSharedRef<ITableRow> HandleGenerateRow(TSharedRef<FAnimBakerUIElement> Item, const TSharedRef<STableViewBase>& OwnerTable);

	void HandleGetChildren(TSharedRef<FAnimBakerUIElement> InItem, TArray<TSharedRef<FAnimBakerUIElement> >& OutChildren);
	
	static FSimpleDelegate OnSourceDataUpdated;

private:
	TWeakObjectPtr<UAnimBaker> AnimBaker;
	TArray<TSharedRef<FAnimBakerUIElement>> BakerUIElements;
	
	FDelegateHandle BakerOutlinerColumnHandle;
	FDelegateHandle SequencerSavedHandle;
	
};
