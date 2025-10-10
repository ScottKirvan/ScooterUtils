// Copyright Epic Games, Inc. All Rights Reserved.

#include "FileIO.h"
#include "ScooterUtilsBPLibraryModule.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"

bool UFileIO::LoadFileToString(FString FileName, FString &OutString, FString &OutFilePath)
{
    OutFilePath = FPaths::ProjectSavedDir() + FileName;
    return FFileHelper::LoadFileToString(OutString, *OutFilePath);
}

bool UFileIO::SaveTextToFile(EFileLocation SaveLocation, const FString &FileName, const FString &Content, FString &OutFullPath)
{
    return SaveStringToFileFunction(
        SaveLocation,
        FileName,
        Content,
        OutFullPath);
}

bool UFileIO::AppendTextToFile(EFileLocation SaveLocation, const FString &FileName, const FString &Content, FString &OutFullPath, const bool bAddLineBreak)
{
    FString TextToWrite = Content;
    if (bAddLineBreak)
    {
        TextToWrite.Append(TEXT("\n"));
    }
    return SaveStringToFileFunction(
        SaveLocation,
        FileName,
        TextToWrite,
        OutFullPath,
        FILEWRITE_Append);
}

bool UFileIO::SaveStringToFileFunction(
    EFileLocation Location,
    const FString &FileName,
    const FString &TextToSave,
    FString &OutFullPath,
    uint32 WriteFlags)
{
    // Determine base directory based on selected location
    FString BaseDirectory;

    switch (Location)
    {
    case EFileLocation::ProjectSaved:
        BaseDirectory = FPaths::ProjectSavedDir();
        break;

    case EFileLocation::UserDocuments:
#if PLATFORM_ANDROID
        BaseDirectory = TEXT("/storage/emulated/0/Documents/");
#else
        BaseDirectory = FPlatformProcess::UserDir();
#endif
        break;

    case EFileLocation::ProjectContent:
        BaseDirectory = FPaths::ProjectContentDir();
        break;

    default:
        BaseDirectory = FPaths::ProjectSavedDir();
        break;
    }

    // Combine base directory with filename
    OutFullPath = FPaths::Combine(BaseDirectory, FileName);

    // Save the file
    bool bSuccess = FFileHelper::SaveStringToFile(TextToSave, *OutFullPath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), WriteFlags);

    if (bSuccess)
    {
        UE_LOG(LogTemp, Log, TEXT("Successfully saved file to: %s"), *OutFullPath);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to save file to: %s"), *OutFullPath);
    }

    return bSuccess;
}