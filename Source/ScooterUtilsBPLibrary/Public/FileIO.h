
// FileIO.h
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FileIO.generated.h"

UENUM(BlueprintType)
enum class EFileLocation : uint8
{
    ProjectSaved UMETA(DisplayName = "Project Saved Directory"),
    UserDocuments UMETA(DisplayName = "User Documents Folder"),
    ProjectContent UMETA(DisplayName = "Project Content Directory")
};

UCLASS()
class UFileIO : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    // Read a string from a file in the Saved folder
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|File IO")
    static bool LoadFileToString(FString FileName, FString &OutString, FString &OutFilePath);

    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|File IO")
    static bool SaveTextToFile(
        EFileLocation SaveLocation,
        const FString &FileName,
        const FString &Content,
        FString &OutFullPath)
    {
        return SaveStringToFileFunction(
            SaveLocation,
            FileName,
            Content,
            OutFullPath);
    }

    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|File IO")
    static bool AppendTextToFile(
        EFileLocation SaveLocation,
        const FString &FileName,
        const FString &Content,
        FString &OutFullPath,
        const bool bAddLineBreak = true)
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

private:
    static bool SaveStringToFileFunction(
        EFileLocation Location,
        const FString &FileName,
        const FString &TextToSave,
        FString &OutFullPath,
        uint32 WriteFlags = 0);
};