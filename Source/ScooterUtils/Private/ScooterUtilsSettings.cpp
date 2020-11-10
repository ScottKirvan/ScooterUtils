// Copyright Epic Games, Inc. All Rights Reserved.

#include "ScooterUtilsSettings.h"


UScooterUtilsSettings::UScooterUtilsSettings(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

		ApplicationScale = 1.0f;
}

void UScooterUtilsSettings::Init()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogTemp, Warning, TEXT("We're unexpectedly in UScooterUtilsSettins::Init()"));
	// I don't think this method ever executes - this may be more for things that are instantiated like actors - hopefully this UObject is safe to use this way - it appears to get constructed early on
}

#if WITH_EDITOR

void UScooterUtilsSettings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UScooterUtilsSettings, ApplicationScale))
	{
		FSlateApplication::Get().SetApplicationScale(ApplicationScale);
	}

	SaveConfig();

	SettingChangedEvent.Broadcast(PropertyName);
}

#endif // WITH_EDITOR

void UScooterUtilsSettings::SetApplicationScale(float f)
{ 
	ApplicationScale = f; UpdateApplicationScale(); 
}  

float UScooterUtilsSettings::GetApplicationScale()
{ 
	return ApplicationScale; 
} 

void UScooterUtilsSettings::UpdateApplicationScale() 
{ 
	if (ApplicationScale >= 0.5f && ApplicationScale <= 3.0f)  {
		FSlateApplication::Get().SetApplicationScale(ApplicationScale); 
	}
	// TODO - maybe put in a .ini file only flag that would let a power user use a scale outside this range by editing the ini directly
} 

