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
	void MenuCommand1();
};
