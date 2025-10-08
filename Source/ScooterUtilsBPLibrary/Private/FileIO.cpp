// Copyright Epic Games, Inc. All Rights Reserved.

#include "FileIO.h"
#include "ScooterUtilsBPLibraryModule.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

bool UFileIO::SaveStringToFile(FString FileName, FString String, FString &OutFilePath)
{
    OutFilePath = FPaths::ProjectSavedDir() + FileName;
    return FFileHelper::SaveStringToFile(String, *OutFilePath);
}

bool UFileIO::SaveStringToDocuments(FString String, FString FileName, FString &OutFilePath)
{
    // Android Documents directory path
    // Try common Android Documents locations
    TArray<FString> PossiblePaths = {
        TEXT("/sdcard/Documents/"),
        TEXT("/storage/emulated/0/Documents/"),
        FPaths::ProjectSavedDir() + TEXT("../../../Documents/")};

    // Try each path until one works
    for (const FString &BasePath : PossiblePaths)
    {
        OutFilePath = BasePath + FileName;
        if (FFileHelper::SaveStringToFile(String, *OutFilePath))
        {
            return true;
        }
    }

    // If all fail, fall back to saved directory
    OutFilePath = FPaths::ProjectSavedDir() + FileName;
    return FFileHelper::SaveStringToFile(String, *OutFilePath);
}

bool UFileIO::LoadFileToString(FString FileName, FString &OutString, FString &OutFilePath)
{
    OutFilePath = FPaths::ProjectSavedDir() + FileName;
    return FFileHelper::LoadFileToString(OutString, *OutFilePath);
}