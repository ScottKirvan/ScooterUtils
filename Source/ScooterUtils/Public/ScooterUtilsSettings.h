// Copyright (c) 2020-2024 Scott Kirvan. All Rights Reserved.

#pragma once

#include "ScooterUtilsSettings.generated.h"

UCLASS(config = EditorSettings)
class UScooterUtilsSettings : public UObject
{
public:
	GENERATED_UCLASS_BODY()

	void Init();

	void SetApplicationScale(float f);
	float GetApplicationScale();
	void UpdateApplicationScale();
	void SetMaxFPS(int f);
	int GetMaxFPS();
	void UpdateMaxFPS();
	void SetShowViewportFPS(bool f);
	bool GetShowViewportFPS();
	void ToggleViewportFPS();

protected:
	// UObject overrides

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent &PropertyChangedEvent) override;
#endif // WITH_EDITOR

public:
	UPROPERTY(config)
	bool bOverrideUEApplicationScale;
	/**
	 * Controls the scale of text and widgets in the editor, giving you the ability
	 * to work with more comfortable default sizes.  This setting persists system-wide
	 * between editing sessions and all projects launched under the same version of Unreal.
	 *
	 * NOTE: Disabling this setting will default back to the system default scale, you may
	 * need to restart the editor to get the system to recognize the settings in Editor Preferences.
	 *
	 * C:\Users\<username>\AppData\Local\UnrealEngine\<EngineVersion>\Saved\Config\WindowsEditor\EditorSettings.ini
	 *
	 * [/Script/ScooterUtils.ScooterUtilsSettings]
	 * ApplicationScale=0.800000
	 */
	UPROPERTY(EditAnywhere, config, Category = "Screen Real Estate", meta = (EditCondition = "bOverrideUEApplicationScale", DisplayName = "Application Scale", ClampMin = 0.5, ClampMax = 3.0))
	float ApplicationScale;

	/**
	 * Controls whether or not, by default, the FPS is shown in the editor viewport.
	 *
	 * C:\Users\<username>\AppData\Local\UnrealEngine\<EngineVersion>\Saved\Config\WindowsEditor\EditorSettings.ini
	 *
	 * [/Script/ScooterUtils.ScooterUtilsSettings]
	 * ShowViewportFPS=True
	 */
	UPROPERTY(EditAnywhere, config, Category = "FPS", meta = (DisplayName = "Show Viewport FPS"))
	bool ShowViewportFPS;

	/**
	 * Controls the Maximum FPS the system can run at.  By default, when you start up, this is set
	 * to 60 or 120 fps.  By running with this unclamped, you can spot performance impacts early on.
	 *  In the system, you can set this in the console by typing "t.MaxFPS #".  By default, the value is
	 * set to 0, which leaves the decision up to the system.
	 *
	 * C:\Users\<username>\AppData\Local\UnrealEngine\<EngineVersion>\Saved\Config\WindowsEditor\EditorSettings.ini
	 *
	 * [/Script/ScooterUtils.ScooterUtilsSettings]
	 * MaxFPS=1000
	 */
	UPROPERTY(EditAnywhere, config, Category = "FPS", meta = (DisplayName = "Max FPS (Console default:  t.MaxFPS 0)"))
	int MaxFPS;

	UPROPERTY(VisibleAnywhere, config, Category = "About Scooter Utilities", meta = (DisplayName = "Version"))
	FString ScooterUtilsVersion = "v11.0.0";
	UPROPERTY(VisibleAnywhere, config, Category = "About Scooter Utilities", meta = (DisplayName = "Copyright"))
	FString ScooterUtilsCopyright = "Copyright (c) 2020-2024 Scott Kirvan. All Rights Reserved";

	UPROPERTY(VisibleAnywhere, config, Category = "About", meta = (DisplayName = "Scooter Utilities Version"))
	FString ScooterUtilsVersion = "1.0.0";

	/**
	 * Returns an event delegate that is executed when a setting has changed.
	 *
	 * @return The delegate.
	 */
	DECLARE_EVENT_OneParam(UEditorStyleSettings, FSettingChangedEvent, FName /*PropertyName*/);
	FSettingChangedEvent &OnSettingChanged() { return SettingChangedEvent; }

	// Holds an event delegate that is executed when a setting has changed.
	FSettingChangedEvent SettingChangedEvent;
};