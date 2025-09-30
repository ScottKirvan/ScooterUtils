// Copyright (c) 2020-2025 Scott Kirvan. All Rights Reserved.

#include "ScooterUtilsMenu.h"
#include "ScooterUtils.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "ScooterUtilsMenu"

class ScooterUtilsMenuCommands : public TCommands<ScooterUtilsMenuCommands>
{
public:
	ScooterUtilsMenuCommands()
		: TCommands<ScooterUtilsMenuCommands>(
			  TEXT("ScooterUtilsMenu"),				  // Context name for fast lookup
			  FText::FromString("Example Menu tool"), // Context name for displaying
			  NAME_None,							  // No parent context
			  FAppStyle::GetAppStyleSetName()		  // Icon Style Set
		  )
	{
	}

	virtual void RegisterCommands() override
	{
		UI_COMMAND(MenuRestartEditor, "Restart Editor...", "Restart the editor, re-opening the current project. - ScooterUtils", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(MenuShowExplorer, "Show Project in Explorer", "Find this project on disk. - ScooterUtils", EUserInterfaceActionType::Button, FInputChord());
		// UI_COMMAND(DecreaseBrushFalloff, "Decrease Brush Falloff", "Press this key to decrease brush falloff by a fixed increment.", EUserInterfaceActionType::RadioButton, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::LeftBracket));
	}

public:
	TSharedPtr<FUICommandInfo> MenuRestartEditor;
	TSharedPtr<FUICommandInfo> MenuShowExplorer;
};

void ScooterUtilsMenu::MapCommands()
{
	const auto &Commands = ScooterUtilsMenuCommands::Get();

	CommandList->MapAction(Commands.MenuRestartEditor, FExecuteAction::CreateSP(this, &ScooterUtilsMenu::MenuRestartEditor), FCanExecuteAction());
	CommandList->MapAction(Commands.MenuShowExplorer, FExecuteAction::CreateSP(this, &ScooterUtilsMenu::MenuShowExplorer), FCanExecuteAction());
}

void ScooterUtilsMenu::OnStartupModule()
{
	CommandList = MakeShareable(new FUICommandList);
	ScooterUtilsMenuCommands::Register();
	MapCommands();
	FScooterUtilsModule::Get().AddMenuExtension(
		FMenuExtensionDelegate::CreateRaw(this, &ScooterUtilsMenu::MakeMenuEntry),
		FName("FileProject"), // trying to place this at the end of the main File/Project menu section
		CommandList);
}

void ScooterUtilsMenu::OnShutdownModule()
{
	ScooterUtilsMenuCommands::Unregister();
}

void ScooterUtilsMenu::MakeMenuEntry(FMenuBuilder &menuBuilder)
{
	menuBuilder.AddMenuEntry(ScooterUtilsMenuCommands::Get().MenuRestartEditor);
	menuBuilder.AddMenuEntry(ScooterUtilsMenuCommands::Get().MenuShowExplorer);
}

// Restarts the editor, re-opening the current project
void ScooterUtilsMenu::MenuRestartEditor()
{
	FUnrealEdMisc::Get().RestartEditor(false);
}

// Shows the project folder in explorer/finder
void ScooterUtilsMenu::MenuShowExplorer()
{
	FString ProjectFolder = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	FPlatformProcess::ExploreFolder(*ProjectFolder);
}

#undef LOCTEXT_NAMESPACE
