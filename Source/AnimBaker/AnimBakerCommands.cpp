// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnimBakerCommands.h"

#define LOCTEXT_NAMESPACE "FAnimBakerModule"

void FAnimBakerCommands::RegisterCommands()
{
	UI_COMMAND(ToggleBakerAction, "AnimBaker", "Toggle AnimBaker Window", EUserInterfaceActionType::ToggleButton, FInputChord());
	UI_COMMAND(RebakeAllAction, "RebakeAll", "Rebakes All Targets", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
