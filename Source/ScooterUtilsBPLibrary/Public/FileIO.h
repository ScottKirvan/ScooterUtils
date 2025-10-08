
// FileIO.h
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FileIO.generated.h"

UCLASS()
class UFileIO : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    // Write a string to a file in the Saved folder
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|File IO")
    static bool SaveStringToFile(FString FileName, FString String, FString &OutFilePath);

    // Save a string to a file in the Documents folder (requires storage permissions)
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Save")
    static bool SaveStringToDocuments(FString String, FString FileName, FString &OutFilePath);

    // Read a string from a file in the Saved folder
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|File IO")
    static bool LoadFileToString(FString FileName, FString &OutString, FString &OutFilePath);
};