// Copyright (c) 2020-2024 Scott Kirvan. All Rights Reserved.

#include "ScooterUtils.h"
#include "ISettingsModule.h"
#include "ScooterUtilsSettings.h"
#include "ISettingsSection.h"
#include "ScooterUtilsMenu.h"
#include "LevelEditor.h"
#include "Editor/UnrealEdEngine.h"
#include "UnrealEdGlobals.h"

#define LOCTEXT_NAMESPACE "FScooterUtilsModule"

void FScooterUtilsModule::AddModuleListeners()
{
	ModuleListeners.Add(MakeShareable(new ScooterUtilsMenu));
}

void FScooterUtilsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	MyHandle = FCoreDelegates::OnEndFrame.AddRaw(this, &FScooterUtilsModule::EditorIsFullyLoaded);

	ISettingsModule *SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		TSharedPtr<ISettingsSection> SettingsSection =
			SettingsModule->RegisterSettings("Editor", "Plugins", "sk_UE_Utils", // Editor Preferences->Plugins->Scooter Utilities...
											 FText::FromString("Scooter Utilities"),
											 FText::FromString("Persistent settings for Unreal Editor"),
											 GetMutableDefault<UScooterUtilsSettings>());

		if (SettingsSection.IsValid())
		{
			GetMutableDefault<UScooterUtilsSettings>()->LoadConfig();
			GetMutableDefault<UScooterUtilsSettings>()->UpdateApplicationScale();
			GetMutableDefault<UScooterUtilsSettings>()->UpdateMaxFPS();
			// GetMutableDefault<UScooterUtilsSettings>()->UpdateShowFPS();

			SettingsSection->OnModified().BindLambda(
				[]()
				{
					GetMutableDefault<UScooterUtilsSettings>()->SaveConfig();
					return true;
				});
		}
	}

	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	if (!IsRunningCommandlet())
	{
		FLevelEditorModule &LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		LevelEditorMenuExtensibilityManager = LevelEditorModule.GetMenuExtensibilityManager();
		MenuExtender = MakeShareable(new FExtender);
		LevelEditorMenuExtensibilityManager->AddExtender(MenuExtender);
	}

	if (!IsRunningCommandlet())
	{
		AddModuleListeners();
		for (int32 i = 0; i < ModuleListeners.Num(); ++i)
		{
			ModuleListeners[i]->OnStartupModule();
		}
	}
	/* for future reference when I get to working on plugin management -
	   from: PluginBrowserModule.cpp

	// Find all the plugins that are installed
	for(const TSharedRef<IPlugin>& Plugin : IPluginManager::Get().GetDiscoveredPlugins())
	{
		if(Plugin->GetDescriptor().bInstalled)
		{
			InstalledPlugins.Add(Plugin->GetName());
		}
	}
	*/
}

void FScooterUtilsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	ISettingsModule *SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		SettingsModule->UnregisterSettings("Editor", "Plugins", "sk_UE4_Utils"); // what happens if this text doesn't match exactly?
	}
}

void FScooterUtilsModule::AddMenuExtension(const FMenuExtensionDelegate &extensionDelegate, FName extensionHook, const TSharedPtr<FUICommandList> &CommandList, EExtensionHook::Position position)
{
	MenuExtender->AddMenuExtension(extensionHook, position, CommandList, extensionDelegate);
}

void FScooterUtilsModule::EditorIsFullyLoaded() const
{
	if (GEngine && GUnrealEd)
	{
		FCoreDelegates::OnEndFrame.Remove(MyHandle);
		if (GetMutableDefault<UScooterUtilsSettings>()->GetShowViewportFPS())
		{
			ShowViewportFPS();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FPS in Viewport: GEngine or GUnrealEd is still do not exist for whatever reason..."));
	}
}
void FScooterUtilsModule::ShowViewportFPS()
{
	const FString FPS = "FPS";
	GEngine->ExecEngineStat(GUnrealEd->GetWorld(), GUnrealEd->GetWorld()->GetGameViewport(), *FPS);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FScooterUtilsModule, ScooterUtils)
