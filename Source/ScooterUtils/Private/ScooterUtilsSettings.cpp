// Copyright Epic Games, Inc. All Rights Reserved.

#include "ScooterUtilsSettings.h"

UScooterUtilsSettings::UScooterUtilsSettings(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	MaxFPS = 0;
	// ShowFPS = false;
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

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UScooterUtilsSettings, MaxFPS))
	{
		GEngine->SetMaxFPS(MaxFPS);
	}

	/*
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UScooterUtilsSettings, ShowFPS))
	{
		if (ShowFPS)
		{
			//UE_LOG(LogTemp, Log, TEXT("ShowFPS"));
			//IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("stat fps"));
			//CVar->Set(ShowFPS);
			GEngine->Exec( GetWorld(), TEXT( "stat fps" ) );
		}
	}
	*/

	SaveConfig();

	SettingChangedEvent.Broadcast(PropertyName);
}

#endif // WITH_EDITOR

void UScooterUtilsSettings::SetMaxFPS(int fps)
{
	MaxFPS = fps;
	UpdateMaxFPS();
}

/*
void UScooterUtilsSettings::SetShowFPS(bool show)
{
	ShowFPS = show; UpdateShowFPS();
}
*/

int UScooterUtilsSettings::GetMaxFPS()
{
	return MaxFPS;
}

/*
bool UScooterUtilsSettings::GetShowFPS()
{
	return ShowFPS;
}
*/

void UScooterUtilsSettings::UpdateMaxFPS()
{
	UE_LOG(LogTemp, Log, TEXT("UpdateMaxFPS1:  %d"), MaxFPS);
	GEngine->SetMaxFPS(MaxFPS);
	MaxFPS = GEngine->GetMaxFPS();
	// UE_LOG(LogTemp, Log, TEXT("UpdateMaxFPS2:  %d"), MaxFPS);  // I'm keeping there here as an example of formatted string printing to the log
}

/*
void UScooterUtilsSettings::UpdateShowFPS()
{
	UE_LOG(LogTemp, Log, TEXT("UpdateShowFPS1:  %d"), ShowFPS);
	if (ShowFPS)
	{
		//IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("stat fps"));
		//CVar->Set(ShowFPS);
		//ShowFPS = CVar->GetBool();
		GEngine->Exec( GetWorld(), TEXT( "stat fps" ) );
	}
	UE_LOG(LogTemp, Log, TEXT("UpdateShowFPS2:  %d"), ShowFPS);
}
*/
