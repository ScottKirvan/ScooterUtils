// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ScooterUtilsSettings.generated.h"

UCLASS(config = EditorSettings)
class UScooterUtilsSettings : public UObject
{
public:
	GENERATED_UCLASS_BODY()

	void Init();

	void SetMaxFPS(int f);
	int GetMaxFPS();
	void UpdateMaxFPS();
	/*
	void SetShowFPS(bool f);
	bool GetShowFPS();
	void UpdateShowFPS();
	*/

protected:
	// UObject overrides

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent &PropertyChangedEvent) override;
#endif // WITH_EDITOR

public:
	/**
	 *
	 * Controls the Maximum FPS the system can run at.  By default, when you start up, this is
	 * set to 60 or 120 fps.  By running with this unclamped, you can spot performance impacts early on.
	 * In the system, you can set this in the console by typing "t.MaxFPS #".  By default, the value is
	 * set to 0, which leaves the decision up to the system.
	 *
	 * C:\Users\<username>\AppData\Local\UnrealEngine\<EngineVersion>\Saved\Config\Windows\EditorSettings.ini
	 *
	 * [/Script/ScooterUtils.ScooterUtilsSettings]
	 * MaxFPS=1000
	 */
	UPROPERTY(EditAnywhere, config, Category = "Max FPS", meta = (DisplayName = "Persistent Editor Max FPS setting.  Console default:  t.MaxFPS 0"))
	int MaxFPS;
	/*
	UPROPERTY(EditAnywhere, config, Category = "Show FPS Onscreen", meta=(DisplayName="Console toggle:  stat fps"))
		bool ShowFPS;
		*/

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