// Copyright Epic Games, Inc. All Rights Reserved.

#include "ScooterUtilsSettings.h"
#include "Editor/UnrealEdEngine.h"
#include "UnrealEdGlobals.h"

UScooterUtilsSettings::UScooterUtilsSettings(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	ApplicationScale = 1.0f;
	MaxFPS = 0;
	ShowViewportFPS = false;
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
		FSlateApplication::Get().SetApplicationScale(ApplicationScale);
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UScooterUtilsSettings, MaxFPS))
	{
		GEngine->SetMaxFPS(MaxFPS);
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UScooterUtilsSettings, ShowViewportFPS))
	{
		SetShowViewportFPS(ShowViewportFPS);
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
	if (FSlateApplication::IsInitialized() && ApplicationScale >= 0.5f && ApplicationScale <= 3.0f)
	{
		FSlateApplication::Get().SetApplicationScale(ApplicationScale);
	}
	// TODO - maybe put in a .ini file only flag that would let a power user use a scale outside this range by editing the ini directly
}

void UScooterUtilsSettings::UpdateMaxFPS()
{
	UE_LOG(LogTemp, Log, TEXT("UpdateMaxFPS1:  %d"), MaxFPS);
	GEngine->SetMaxFPS(MaxFPS);
	MaxFPS = GEngine->GetMaxFPS();
	// UE_LOG(LogTemp, Log, TEXT("UpdateMaxFPS2:  %d"), MaxFPS);  // I'm keeping there here as an example of formatted string printing to the log
}

void UScooterUtilsSettings::ToggleViewportFPS()
{
	// UE_LOG(LogTemp, Log, TEXT("ToggleViewportFPS1:  %d"), ShowViewportFPS);
	const FString FPS = "FPS";
	GEngine->ExecEngineStat(GUnrealEd->GetWorld(), GUnrealEd->GetWorld()->GetGameViewport(), *FPS);
	// UE_LOG(LogTemp, Log, TEXT("ToggleViewportFPS2:  %d"), ShowViewportFPS);
}
