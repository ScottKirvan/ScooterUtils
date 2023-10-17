
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
		UI_COMMAND(MenuCommand1, "Restart Editor...", "Restart the editor, re-opening the current project. - ScooterUtils", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(MenuCommand2, "Show Project in Explorer", "Find this project on disk. - ScooterUtils", EUserInterfaceActionType::Button, FInputChord());
	}

public:
	TSharedPtr<FUICommandInfo> MenuCommand1;
	TSharedPtr<FUICommandInfo> MenuCommand2;
};

void ScooterUtilsMenu::MapCommands()
{
	const auto &Commands = ScooterUtilsMenuCommands::Get();

	CommandList->MapAction(Commands.MenuCommand1, FExecuteAction::CreateSP(this, &ScooterUtilsMenu::MenuCommand1), FCanExecuteAction());
	CommandList->MapAction(Commands.MenuCommand2, FExecuteAction::CreateSP(this, &ScooterUtilsMenu::MenuCommand2), FCanExecuteAction());
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
	menuBuilder.AddMenuEntry(ScooterUtilsMenuCommands::Get().MenuCommand1);
	menuBuilder.AddMenuEntry(ScooterUtilsMenuCommands::Get().MenuCommand2);
}

// Restarts the editor, re-opening the current project
void ScooterUtilsMenu::MenuCommand1()
{
	FUnrealEdMisc::Get().RestartEditor(false);
}

// Shows the project folder in explorer/finder
void ScooterUtilsMenu::MenuCommand2()
{
	FString ProjectFolder = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	FPlatformProcess::ExploreFolder(*ProjectFolder);
}

#undef LOCTEXT_NAMESPACE
