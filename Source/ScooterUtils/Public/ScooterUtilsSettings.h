// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ScooterUtilsSettings.generated.h"

//UCLASS(config=EditorPerProjectUserSettings)
UCLASS(config=EditorSettings)
class UScooterUtilsSettings : public UObject
{
public:
	GENERATED_UCLASS_BODY()

	void Init();

	void SetApplicationScale(float f);
	float GetApplicationScale();
	void UpdateApplicationScale();

protected:

	// UObject overrides

#if WITH_EDITOR
	virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent ) override;
#endif // WITH_EDITOR

public:

	/**
	 * Controls the scale of text and widgets in the editor, allowing you to gain more contol
	 * over how much infomation you see and giving you the ability to work with what may be 
	 * more comfortable then the default size.  This setting persists system-wide between 
	 * editing sessions and all projects launched under the same version of Unreal.
	 * 
	 * C:\Users\<username>\AppData\Local\UnrealEngine\<EngineVersion>\Saved\Config\Windows\EditorSettings.ini
	 * 
	 * [/Script/ScooterUtils.ScooterUtilsSettings]
	 * ApplicationScale=0.800000
	 */
	UPROPERTY(EditAnywhere, config, Category = "Screen Real Estate", meta=(DisplayName="Persistant Editor Scale (Widget Reflector: Application Scale)", ClampMin=0.5, ClampMax=3.0))
	float ApplicationScale;  // TODO - any way to use constants for these two values so they don't get out of sync with the error checking in UpdateApplicationScale?
	// also, a reset to default would be nice, but I don't think the yellow reset arrow is supported in prefs.
	// the "Reset to Defaults" button does no appear to work - how do we implement that? (there is lots of spots this doesn't seem to work)

	/**
	 * Returns an event delegate that is executed when a setting has changed.
	 *
	 * @return The delegate.
	 */
	DECLARE_EVENT_OneParam(UEditorStyleSettings, FSettingChangedEvent, FName /*PropertyName*/);
	FSettingChangedEvent& OnSettingChanged( ) { return SettingChangedEvent; }

	// Holds an event delegate that is executed when a setting has changed.
	FSettingChangedEvent SettingChangedEvent;
};