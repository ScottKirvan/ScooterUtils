
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

    /**
     * Saves text content to a file at the specified location.
     *
     * WARNING: Overwrites existing files without warning!
     * NOTE: Creates parent directories automatically if they don't exist
     *
     * @param SaveLocation - The base directory location (Project, Saved, etc.)
     * @param FileName - Name of the file including extension
     * @param Content - The text content to write to the file
     * @param bAppendNewLine - If true, appends CR/LF to the content
     * @param OutFullPath - Returns the complete file path where the file was saved
     * @return True if the file was saved successfully, false otherwise
     *
     * @warning Overwrites existing files without confirmation
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|File IO")
    static bool SaveTextToFile(
        EFileLocation SaveLocation,
        const FString &FileName,
        const FString &Content,
        FString &OutFullPath);

    /**
     * Appends text content to a file at the specified location.
     *
     * NOTE: Creates parent directories automatically if they don't exist
     *
     * @param SaveLocation - The base directory location (Project, Saved, etc.)
     * @param FileName - Name of the file including extension
     * @param Content - The text content to write to the file
     * @param bAppendNewLine - If true, appends CR/LF to the content
     * @param OutFullPath - Returns the complete file path where the file was saved
     * @param bAddLineBreak - If true, appends a line break to the content string
     * @return True if the file was saved successfully, false otherwise
     *
     * @note Creates parent directories automatically if they don't exist
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|File IO")
    static bool AppendTextToFile(
        EFileLocation SaveLocation,
        const FString &FileName,
        const FString &Content,
        FString &OutFullPath,
        const bool bAddLineBreak = true);

private:
    static bool SaveStringToFileFunction(
        EFileLocation Location,
        const FString &FileName,
        const FString &TextToSave,
        FString &OutFullPath,
        uint32 WriteFlags = 0);
};