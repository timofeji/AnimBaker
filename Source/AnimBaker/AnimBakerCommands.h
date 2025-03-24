// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "AnimBakerStyle.h"

class FAnimBakerCommands : public TCommands<FAnimBakerCommands>
{
public:
	FAnimBakerCommands()
		: TCommands<FAnimBakerCommands>(TEXT("AnimBaker"), NSLOCTEXT("Contexts", "AnimBaker", "AnimBaker Plugin"),
		                                NAME_None, FAnimBakerStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> ToggleBakerAction;
	TSharedPtr<FUICommandInfo> RebakeAllAction;
};
