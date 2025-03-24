// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ISequencerModule.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;
class ISequencer;

class FAnimBakerModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** Sequencer **/
	void OnSequencerCreated(TSharedRef<ISequencer, ESPMode::ThreadSafe> SharedSequencer);
	void ExtendSequencerToolbar(FToolBarBuilder& ToolbarBuilder) const;

	static void ToggleBakerWindow();
	static bool CanToggleBakerWindow();
private:
	TSharedPtr<class FUICommandList> PluginCommands;
	FDelegateHandle OnSequencerCreatedHandle;
	
	
	static TWeakPtr<SWindow> AnimBakerWindow;
};
