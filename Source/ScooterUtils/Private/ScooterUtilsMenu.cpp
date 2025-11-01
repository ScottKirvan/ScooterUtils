// Copyright (c) 2020-2025 Scott Kirvan. All Rights Reserved.

#include "ScooterUtilsMenu.h"
#include "ScooterUtils.h"
#include "ScooterUtilsSettings.h"
#include "EditorStyleSet.h"
#include "LevelEditor.h"
#include "ToolMenus.h"
#include "Widgets/Input/SComboButton.h"
#include "ISettingsModule.h"

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
		// Get the hotkey from settings
		const UScooterUtilsSettings* Settings = GetDefault<UScooterUtilsSettings>();
		FInputChord RestartHotkey = Settings && Settings->bEnableRestartEditorHotkey 
			? Settings->RestartEditorHotkey 
			: FInputChord();

		UI_COMMAND(MenuRestartEditor, "Restart Editor...", "Restart the editor, re-opening the current project. - ScooterUtils", EUserInterfaceActionType::Button, RestartHotkey);
		UI_COMMAND(MenuShowExplorer, "Show Project in Explorer", "Find this project on disk. - ScooterUtils", EUserInterfaceActionType::Button, FInputChord());
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

	// Register commands with the global editor command list for hotkey to work globally
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetGlobalLevelEditorActions()->Append(CommandList.ToSharedRef());

	// Add menu extension to File menu
	FScooterUtilsModule::Get().AddMenuExtension(
		FMenuExtensionDelegate::CreateRaw(this, &ScooterUtilsMenu::MakeMenuEntry),
		FName("FileProject"), // trying to place this at the end of the main File/Project menu section
		CommandList);

	// Add toolbar button using the modern ToolMenus system (if enabled in settings)
	const UScooterUtilsSettings* Settings = GetDefault<UScooterUtilsSettings>();
	if (Settings && Settings->bShowToolbarButton)
	{
		UToolMenus* ToolMenus = UToolMenus::Get();
		if (ToolMenus)
		{
			UToolMenu* ToolbarMenu = ToolMenus->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
			if (ToolbarMenu)
			{
				FToolMenuSection& Section = ToolbarMenu->AddSection("ScooterUtils", FText::FromString("Scooter Utils"));

				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitComboButton(
					"ScooterUtilsCombo",
					FUIAction(),
					FOnGetContent::CreateSP(this, &ScooterUtilsMenu::GenerateToolbarMenu),
					LOCTEXT("ScooterUtilsToolbarLabel", "Scooter Utils"),
					LOCTEXT("ScooterUtilsToolbarTooltip", "Scooter Utilities tools and settings"),
					FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.GameSettings")
				));
			}
		}
	}
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

// Create the toolbar button with dropdown menu (legacy method - no longer used)
void ScooterUtilsMenu::MakeToolbarEntry(FToolBarBuilder &toolbarBuilder)
{
	toolbarBuilder.AddComboButton(
		FUIAction(),
		FOnGetContent::CreateSP(this, &ScooterUtilsMenu::GenerateToolbarMenu),
		LOCTEXT("ScooterUtilsToolbarLabel", "Scooter Utils"),
		LOCTEXT("ScooterUtilsToolbarTooltip", "Scooter Utilities tools and settings"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.GameSettings")
	);
}

// Generate the dropdown menu content
TSharedRef<SWidget> ScooterUtilsMenu::GenerateToolbarMenu()
{
	const bool bShouldCloseWindowAfterMenuSelection = true;
	FMenuBuilder MenuBuilder(bShouldCloseWindowAfterMenuSelection, CommandList);

	MenuBuilder.BeginSection("ScooterUtilsActions", LOCTEXT("ActionsSection", "Actions"));
	{
		MenuBuilder.AddMenuEntry(ScooterUtilsMenuCommands::Get().MenuRestartEditor);
		MenuBuilder.AddMenuEntry(ScooterUtilsMenuCommands::Get().MenuShowExplorer);
	}
	MenuBuilder.EndSection();

	MenuBuilder.BeginSection("ScooterUtilsSettings", LOCTEXT("SettingsSection", "Settings"));
	{
		MenuBuilder.AddMenuEntry(
			LOCTEXT("OpenPluginSettings", "Plugin Settings..."),
			LOCTEXT("OpenPluginSettingsTooltip", "Open Scooter Utilities settings in Editor Preferences"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.GameSettings.Small"),
			FUIAction(FExecuteAction::CreateLambda([]()
			{
				FModuleManager::LoadModuleChecked<ISettingsModule>("Settings").ShowViewer("Editor", "Plugins", "sk_UE_Utils");
			}))
		);
	}
	MenuBuilder.EndSection();

	return MenuBuilder.MakeWidget();
}

#undef LOCTEXT_NAMESPACE