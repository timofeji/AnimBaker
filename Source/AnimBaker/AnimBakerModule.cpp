// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnimBakerModule.h"
#include "AnimBakerStyle.h"
#include "AnimBakerCommands.h"
#include "ISequencerModule.h"
#include "SAnimBaker.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName AnimBakerTabName("AnimBaker");

#define LOCTEXT_NAMESPACE "FAnimBakerModule"

void FAnimBakerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FAnimBakerStyle::Initialize();
	FAnimBakerStyle::ReloadTextures();

	FAnimBakerCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction(FAnimBakerCommands::Get().ToggleBakerAction,
	                          FExecuteAction::CreateStatic(&FAnimBakerModule::ToggleBakerWindow),
	                          FCanExecuteAction::CreateStatic(&FAnimBakerModule::CanToggleBakerWindow)
	);
	//
	// OnSequencerCreatedHandle = SequencerModule.RegisterOnSequencerCreated(
	// 	FOnSequencerCreated::FDelegate::CreateSP(this, &FAnimBakerModule::OnSequencerCreated));
	// //
	TSharedPtr<FExtender> Extender = MakeShareable(new FExtender);
	Extender->AddToolBarExtension(
		"BaseCommands",
		EExtensionHook::Before,
		PluginCommands,
		FToolBarExtensionDelegate::CreateRaw(this, &FAnimBakerModule::ExtendSequencerToolbar)
	);

	ISequencerModule& SequencerModule = FModuleManager::LoadModuleChecked<ISequencerModule>("Sequencer");
	SequencerModule.GetToolBarExtensibilityManager()->AddExtender(Extender);
}

void FAnimBakerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAnimBakerStyle::Shutdown();

	FAnimBakerCommands::Unregister();
}

void FAnimBakerModule::OnSequencerCreated(TSharedRef<ISequencer, ESPMode::ThreadSafe> SharedSequencer)
{
}

void FAnimBakerModule::ExtendSequencerToolbar(FToolBarBuilder& ToolbarBuilder) const
{
	ToolbarBuilder.BeginSection("AnimBakerExtensions");
	ToolbarBuilder.AddToolBarButton(
		FAnimBakerCommands::Get().ToggleBakerAction,
		NAME_None,
		LOCTEXT("AnimBakerLabel", ""),
		LOCTEXT("AnimBakerTooltip", "Toggle AnimBaker Window"),
		FSlateIcon(FAnimBakerStyle::Get().GetStyleSetName(), "AnimBaker.Icon")
	);
	ToolbarBuilder.EndSection();
}


TWeakPtr<SWindow>  FAnimBakerModule::AnimBakerWindow;
void FAnimBakerModule::ToggleBakerWindow()
{
	// TSharedPtr<SWindow> ExistingWindow = AnimBakerWindow.Pin();
	// if (ExistingWindow.IsValid())
	// {
	// 	ExistingWindow->BringToFront();
	// }
	// else
	// {
	// 	ExistingWindow = SNew(SWindow)
	// 		.Title( LOCTEXT("AnimBakerTitle", "Sequencer Animation Baker") )
	// 		.HasCloseButton(true)
	// 		.SupportsMaximize(false)
	// 		.SupportsMinimize(false)
	// 		.ClientSize(FVector2D(500, 700));
	//
	// 	TSharedPtr<SDockTab> OwnerTab = AnimBaker->GetOwnerTab();
	// 	TSharedPtr<SWindow> RootWindow = OwnerTab.IsValid() ? OwnerTab->GetParentWindow() : TSharedPtr<SWindow>();
	// 	if(RootWindow.IsValid())
	// 	{
	// 		FSlateApplication::Get().AddWindowAsNativeChild(ExistingWindow.ToSharedRef(), RootWindow.ToSharedRef());
	// 	}
	// 	else
	// 	{
	// 		FSlateApplication::Get().AddWindow(ExistingWindow.ToSharedRef());
	// 	}
	// }
	//
	// ExistingWindow->SetContent(
	// 	SNew(SAnimBaker)
	// );
	// AnimBakerWindow = ExistingWindow;
}

bool FAnimBakerModule::CanToggleBakerWindow()
{
	return true;
}


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAnimBakerModule, AnimBaker)
