// Copyright (c) 2020-2025 Scott Kirvan. All Rights Reserved.

#pragma once

#include "ScooterUtils.h"

class ScooterUtilsMenu : public IScooterUtilsModuleListenerInterface, public TSharedFromThis<ScooterUtilsMenu>
{
public:
	virtual ~ScooterUtilsMenu() {};

	virtual void OnStartupModule() override;
	virtual void OnShutdownModule() override;

	void MakeMenuEntry(FMenuBuilder &menuBuilder);

protected:
	TSharedPtr<FUICommandList> CommandList;

	void MapCommands();

	//************************
	// UI Command functions
	void MenuRestartEditor(); // restart editor
	void MenuShowExplorer();  // open project folder
};
