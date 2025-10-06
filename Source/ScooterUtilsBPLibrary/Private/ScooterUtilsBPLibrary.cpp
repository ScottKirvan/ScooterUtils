// Copyright Epic Games, Inc. All Rights Reserved.

#include "ScooterUtilsBPLibrary.h"
#include "ScooterUtilsBPLibraryModule.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

UScooterUtilsBPLibrary::UScooterUtilsBPLibrary(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

float UScooterUtilsBPLibrary::deletemeSampleFunction(float Param)
{
	return -1;
}

bool UScooterUtilsBPLibrary::SaveStringToFile(FString FileName, FString String, FString &OutFilePath)
{
	OutFilePath = FPaths::ProjectSavedDir() + FileName;
	return FFileHelper::SaveStringToFile(String, *OutFilePath);
}
bool UScooterUtilsBPLibrary::LoadFileToString(FString FileName, FString &OutString, FString &OutFilePath)
{
	OutFilePath = FPaths::ProjectSavedDir() + FileName;
	return FFileHelper::LoadFileToString(OutString, *OutFilePath);
}