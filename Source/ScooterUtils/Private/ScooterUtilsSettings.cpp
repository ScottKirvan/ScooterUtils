// Copyright (c) 2020-2025 Scott Kirvan. All Rights Reserved.

#include "ScooterUtilsSettings.h"
#include "Editor/UnrealEdEngine.h"
#include "UnrealEdGlobals.h"
#include "ScooterUtilsVersion.h"
#include "InputCoreTypes.h"
#include "Interfaces/IPluginManager.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Misc/MessageDialog.h"
#include "Misc/Paths.h"

// @TODO - at initialisation, our checkbox for enableing the plugin by default is not being set correctly.  I think it's taking what it says in the ini file and ignoring any initialization or reading of the uplugin file.

UScooterUtilsSettings::UScooterUtilsSettings(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	bOverrideUEApplicationScale = false;
	ApplicationScale = 1.0f;
	MaxFPS = 0;
	ShowViewportFPS = false;
	ScooterUtilsVersion = FString::Printf(TEXT("v%d.%d.%d"), SCOOTER_UTILS_VERSION_MAJOR, SCOOTER_UTILS_VERSION_MINOR, SCOOTER_UTILS_VERSION_PATCH);

	// Initialize hotkey settings
	bEnableRestartEditorHotkey = true;
	RestartEditorHotkey = FInputChord(EModifierKey::Control | EModifierKey::Shift | EModifierKey::Alt, EKeys::R);

	// Initialize plugin settings - read current state from .uplugin file
	// bPluginEnabledByDefault = ReadPluginEnabledByDefaultFromFile();
}

void UScooterUtilsSettings::PostInitProperties()
{
	Super::PostInitProperties();

	// After config is loaded, sync the checkbox with the actual .uplugin file state
	bool bActualState = ReadPluginEnabledByDefaultFromFile();
	if (bPluginEnabledByDefault != bActualState)
	{
		UE_LOG(LogTemp, Log, TEXT("ScooterUtils: Syncing bPluginEnabledByDefault from .uplugin file: %s"),
			   bActualState ? TEXT("true") : TEXT("false"));
		bPluginEnabledByDefault = bActualState;
		SaveConfig(); // Save the corrected value to ini
	}
}

void UScooterUtilsSettings::Init()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogTemp, Warning, TEXT("We're unexpectedly in UScooterUtilsSettings::Init()"));
	// I don't think this method ever executes - this may be more for things that are instantiated like actors - hopefully this UObject is safe to use this way - it appears to get constructed early on
}

#if WITH_EDITOR

void UScooterUtilsSettings::PostEditChangeProperty(struct FPropertyChangedEvent &PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UScooterUtilsSettings, ApplicationScale))
	{
		if (bOverrideUEApplicationScale)
		{
			FSlateApplication::Get().SetApplicationScale(ApplicationScale);
		}
		else
		{
			FSlateApplication::Get().SetApplicationScale(1.0f);
		}
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UScooterUtilsSettings, MaxFPS))
	{
		GEngine->SetMaxFPS(MaxFPS);
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UScooterUtilsSettings, ShowViewportFPS))
	{
		SetShowViewportFPS(ShowViewportFPS);
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UScooterUtilsSettings, bEnableRestartEditorHotkey) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(UScooterUtilsSettings, RestartEditorHotkey))
	{
		// Notify user that editor restart is required for hotkey changes
		UE_LOG(LogTemp, Warning, TEXT("ScooterUtils: Hotkey settings changed. Please restart the editor for changes to take effect."));
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UScooterUtilsSettings, bPluginEnabledByDefault))
	{
		UpdatePluginEnabledByDefault(bPluginEnabledByDefault);
	}

	SaveConfig();

	SettingChangedEvent.Broadcast(PropertyName);
}

#endif // WITH_EDITOR

void UScooterUtilsSettings::SetApplicationScale(float f)
{
	ApplicationScale = f;
	UpdateApplicationScale();
}

void UScooterUtilsSettings::SetMaxFPS(int fps)
{
	MaxFPS = fps;
	UpdateMaxFPS();
}

void UScooterUtilsSettings::SetShowViewportFPS(bool show)
{
	ShowViewportFPS = show;
	ToggleViewportFPS();
}

float UScooterUtilsSettings::GetApplicationScale()
{
	return ApplicationScale;
}

int UScooterUtilsSettings::GetMaxFPS()
{
	return MaxFPS;
}

bool UScooterUtilsSettings::GetShowViewportFPS()
{
	return ShowViewportFPS;
}

void UScooterUtilsSettings::UpdateApplicationScale()
{
	if (bOverrideUEApplicationScale && FSlateApplication::IsInitialized() && ApplicationScale >= 0.5f && ApplicationScale <= 3.0f)
	{
		FSlateApplication::Get().SetApplicationScale(ApplicationScale);
	}
	// TODO - maybe put in a .ini file only flag that would let a power user use a scale outside this range by editing the ini directly
}

void UScooterUtilsSettings::UpdateMaxFPS()
{
	// UE_LOG(LogTemp, Log, TEXT("UpdateMaxFPS1:  %d"), MaxFPS);
	GEngine->SetMaxFPS(MaxFPS);
	MaxFPS = GEngine->GetMaxFPS();
}

void UScooterUtilsSettings::ToggleViewportFPS()
{
	// UE_LOG(LogTemp, Log, TEXT("ToggleViewportFPS1:  %d"), ShowViewportFPS);
	const FString FPS = "FPS";
	GEngine->ExecEngineStat(GUnrealEd->GetWorld(), GUnrealEd->GetWorld()->GetGameViewport(), *FPS);
}

void UScooterUtilsSettings::UpdatePluginEnabledByDefault(bool bEnabled)
{
	// Find the plugin's .uplugin file path
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("ScooterUtils"));
	if (!Plugin.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("ScooterUtils: Could not find ScooterUtils plugin"));
		FMessageDialog::Open(EAppMsgType::Ok,
							 FText::FromString(TEXT("Could not locate the ScooterUtils plugin. Please verify the plugin is installed correctly.")));
		return;
	}

	FString PluginDescriptorPath = Plugin->GetDescriptorFileName();
	UE_LOG(LogTemp, Log, TEXT("ScooterUtils: Plugin descriptor path: %s"), *PluginDescriptorPath);

	// Check if file exists and is writable
	if (!FPaths::FileExists(PluginDescriptorPath))
	{
		UE_LOG(LogTemp, Error, TEXT("ScooterUtils: Plugin descriptor file does not exist at %s"), *PluginDescriptorPath);
		FMessageDialog::Open(EAppMsgType::Ok,
							 FText::FromString(FString::Printf(TEXT("Plugin descriptor file not found:\n%s"), *PluginDescriptorPath)));
		return;
	}

	if (IFileManager::Get().IsReadOnly(*PluginDescriptorPath))
	{
		UE_LOG(LogTemp, Error, TEXT("ScooterUtils: Plugin descriptor file is read-only at %s"), *PluginDescriptorPath);
		FMessageDialog::Open(EAppMsgType::Ok,
							 FText::FromString(FString::Printf(
								 TEXT("Cannot update plugin settings - the .uplugin file is read-only.\n\n")
									 TEXT("Location: %s\n\n")
										 TEXT("This may be due to:\n")
											 TEXT("• File permissions (try running editor as administrator)\n")
												 TEXT("• Plugin installed in a protected system directory\n")
													 TEXT("• File system restrictions\n\n")
														 TEXT("Please make the file writable or move the plugin to a user-writable location."),
								 *PluginDescriptorPath)));
		// Revert the setting change
		bPluginEnabledByDefault = !bEnabled;
		return;
	}

	// Read the .uplugin file
	FString JsonString;
	if (!FFileHelper::LoadFileToString(JsonString, *PluginDescriptorPath))
	{
		UE_LOG(LogTemp, Error, TEXT("ScooterUtils: Failed to read .uplugin file at %s"), *PluginDescriptorPath);
		FMessageDialog::Open(EAppMsgType::Ok,
							 FText::FromString(FString::Printf(
								 TEXT("Failed to read the plugin descriptor file.\n\nLocation: %s\n\n")
									 TEXT("Please check file permissions and try again."),
								 *PluginDescriptorPath)));
		bPluginEnabledByDefault = !bEnabled;
		return;
	}

	// Parse JSON
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("ScooterUtils: Failed to parse .uplugin JSON"));
		FMessageDialog::Open(EAppMsgType::Ok,
							 FText::FromString(TEXT("Failed to parse the plugin descriptor file. The file may be corrupted.")));
		bPluginEnabledByDefault = !bEnabled;
		return;
	}

	// Update the EnabledByDefault field
	JsonObject->SetBoolField(TEXT("EnabledByDefault"), bEnabled);

	// Write back to file with pretty formatting
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> Writer =
		TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&OutputString);

	if (!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer))
	{
		UE_LOG(LogTemp, Error, TEXT("ScooterUtils: Failed to serialize JSON"));
		FMessageDialog::Open(EAppMsgType::Ok,
							 FText::FromString(TEXT("Failed to serialize the plugin descriptor data.")));
		bPluginEnabledByDefault = !bEnabled;
		return;
	}

	// Attempt to write the file
	if (!FFileHelper::SaveStringToFile(OutputString, *PluginDescriptorPath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
	{
		UE_LOG(LogTemp, Error, TEXT("ScooterUtils: Failed to write .uplugin file at %s"), *PluginDescriptorPath);
		FMessageDialog::Open(EAppMsgType::Ok,
							 FText::FromString(FString::Printf(
								 TEXT("Failed to save changes to the plugin descriptor file.\n\n")
									 TEXT("Location: %s\n\n")
										 TEXT("Possible causes:\n")
											 TEXT("• Insufficient permissions (try running editor as administrator)\n")
												 TEXT("• Disk is full or write-protected\n")
													 TEXT("• File is locked by another process\n\n")
														 TEXT("The setting has been reverted."),
								 *PluginDescriptorPath)));
		bPluginEnabledByDefault = !bEnabled;
		return;
	}

	// Success!
	UE_LOG(LogTemp, Log, TEXT("ScooterUtils: Successfully updated EnabledByDefault to %s in .uplugin file"),
		   bEnabled ? TEXT("true") : TEXT("false"));

	/*
	// Show success notification
	FText NotificationText = FText::FromString(FString::Printf(
		TEXT("Plugin 'EnabledByDefault' setting updated to: %s\n\nThis will affect new projects going forward."),
		bEnabled ? TEXT("Enabled") : TEXT("Disabled")));
	FMessageDialog::Open(EAppMsgType::Ok, NotificationText);
	*/
}

bool UScooterUtilsSettings::ReadPluginEnabledByDefaultFromFile() const
{
	// Find the plugin
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("ScooterUtils"));
	if (!Plugin.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("ScooterUtils: Could not find plugin to read EnabledByDefault setting, defaulting to true"));
		return true;
	}

	FString PluginDescriptorPath = Plugin->GetDescriptorFileName();

	// Read the .uplugin file
	FString JsonString;
	if (!FFileHelper::LoadFileToString(JsonString, *PluginDescriptorPath))
	{
		UE_LOG(LogTemp, Warning, TEXT("ScooterUtils: Failed to read .uplugin file, defaulting EnabledByDefault to true"));
		return true;
	}

	// Parse JSON
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("ScooterUtils: Failed to parse .uplugin JSON, defaulting EnabledByDefault to true"));
		return true;
	}

	// Read the EnabledByDefault field (default to true if not present)
	bool bEnabledByDefault = true;
	if (JsonObject->HasField(TEXT("EnabledByDefault")))
	{
		bEnabledByDefault = JsonObject->GetBoolField(TEXT("EnabledByDefault"));
		UE_LOG(LogTemp, Log, TEXT("ScooterUtils: Read EnabledByDefault = %s from .uplugin file"),
			   bEnabledByDefault ? TEXT("true") : TEXT("false"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("ScooterUtils: EnabledByDefault field not found in .uplugin, defaulting to true"));
	}

	return bEnabledByDefault;
}