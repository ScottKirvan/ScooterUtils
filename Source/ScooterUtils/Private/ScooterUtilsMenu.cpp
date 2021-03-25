
#include "ScooterUtilsMenu.h"
#include "ScooterUtils.h"

#define LOCTEXT_NAMESPACE "ScooterUtilsMenu"

class ScooterUtilsMenuCommands : public TCommands<ScooterUtilsMenuCommands>
{
public:

	ScooterUtilsMenuCommands()
		: TCommands<ScooterUtilsMenuCommands>(
		TEXT("ScooterUtilsMenu"), // Context name for fast lookup
		FText::FromString("Example Menu tool"), // Context name for displaying
		NAME_None,	 // No parent context
		FEditorStyle::GetStyleSetName() // Icon Style Set
		)
	{
	}

	virtual void RegisterCommands() override
	{
		UI_COMMAND(MenuCommand1, "Restart Editor...", "Restart the editor, re-opening the current project. - ScooterUtils", EUserInterfaceActionType::Button, FInputChord());
	}

public:
	TSharedPtr<FUICommandInfo> MenuCommand1;
};

void ScooterUtilsMenu::MapCommands()
{
	const auto& Commands = ScooterUtilsMenuCommands::Get();

	CommandList->MapAction( Commands.MenuCommand1, FExecuteAction::CreateSP(this, &ScooterUtilsMenu::MenuCommand1), FCanExecuteAction());

}

void ScooterUtilsMenu::OnStartupModule()
{
	CommandList = MakeShareable(new FUICommandList);
	ScooterUtilsMenuCommands::Register();
	MapCommands();
	FScooterUtilsModule::Get().AddMenuExtension(
		FMenuExtensionDelegate::CreateRaw(this, &ScooterUtilsMenu::MakeMenuEntry),
		FName("DataValidation"),  // just before the DataValidation section, at the end of off the project build options
		CommandList);
}

void ScooterUtilsMenu::OnShutdownModule()
{
	ScooterUtilsMenuCommands::Unregister();
}

void ScooterUtilsMenu::MakeMenuEntry(FMenuBuilder &menuBuilder)
{
	menuBuilder.AddMenuEntry(ScooterUtilsMenuCommands::Get().MenuCommand1);
}

void ScooterUtilsMenu::MenuCommand1()
{
	FUnrealEdMisc::Get().RestartEditor(false);
}

#undef LOCTEXT_NAMESPACE
