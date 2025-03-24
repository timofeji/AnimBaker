#pragma once
#include "ISequencer.h"
#include "LevelSequence.h"
#include "MVVM/ViewModelPtr.h"
#include "AnimBaker.generated.h"

class UAnimSeqExportOption;

UCLASS(BlueprintType, MinimalAPI)
class UAnimBakeTarget : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = BakerTarget)
	FGuid Guid;
	UPROPERTY(BlueprintReadWrite, Category = BakerTarget)
	FString AssetName;
	UPROPERTY(BlueprintReadWrite, Category = BakerTarget)
	FString AssetPath;
	UPROPERTY(BlueprintReadWrite, Category = BakerTarget)
	bool bLinkToAsset = true;
	UPROPERTY(BlueprintReadWrite, Category = BakerTarget)
	bool bIsLocked = false;
	UPROPERTY(BlueprintReadWrite, Category = BakerTarget)
	TObjectPtr<UAnimSeqExportOption> ExportOptionsPtr;
	UPROPERTY(BlueprintReadWrite, Category = BakerTarget)
	TArray<UMovieSceneSection* > ActiveSections;
};

USTRUCT()
struct FBakeResult
{
	GENERATED_BODY()
	bool bSucess = false;
	UObject* Asset;
};

/*
 * Holds different targets to bake from a level sequence
 */
UCLASS(BlueprintType, MinimalAPI)
class UAnimBaker : public UAssetUserData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = Baker)
	TArray<UObject*> AnimBakeTargets;


	void OnSequencerSaved(ISequencer&);

	bool AddSelectedSectionsInSequencer();
	int32 CreateNewBakeTarget(ISequencer* Sequencer);

	void RebakeAll();
	
	void AddSelectedSectionsToTarget(UAnimBakeTarget* Target);


	static void SoloTarget(const TObjectPtr<UAnimBakeTarget> BakeTarget);
	
	static void BakeTarget(const TObjectPtr<UAnimBakeTarget> Target);
	
	static bool RenderAnimSequenceForTarget(UObject* NewAssets, USkeletalMeshComponent* SkelMeshComp, UAnimBakeTarget* BakeTarget);
	
	static bool NotifyBakeComplete(TArray<FBakeResult> BakeResults);
	
	static TSharedPtr<ISequencer> GetSequencerFromAsset();
	static UAnimBaker* GetAnimBaker(ISequencer* SequencerPtr);
	static UAnimBaker* GetAnimBaker(ULevelSequence* LevelSequence);

	
	static UObject* SoloedTarget;
	static TArray<TTuple<UMovieSceneSection*, bool>> PreSoloSectionStates;
};
