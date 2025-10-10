// FileIO.h
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPReflection.generated.h"

UCLASS()
class UBPReflection : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Blueprint Reflection", meta = (WorldContext = "WorldContextObject"))
    static FString GetCallingBlueprintName(const UObject *WorldContextObject)
    {
        if (!WorldContextObject)
            return TEXT("Unknown");

        // Get the Blueprint class
        UClass *CallerClass = WorldContextObject->GetClass();
        if (CallerClass)
        {
            return CallerClass->GetName();
        }

        return TEXT("Unknown");
    };

    // @todo: this doesn't work in shipping/packaged builds
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Blueprint Reflection", meta = (WorldContext = "WorldContextObject"))
    static FString GetCallingBlueprintPath(const UObject *WorldContextObject)
    {
        if (!WorldContextObject)
            return TEXT("");

        UClass *CallerClass = WorldContextObject->GetClass();
        if (CallerClass)
        {
#if WITH_EDITOR
            UBlueprint *Blueprint = Cast<UBlueprint>(CallerClass->ClassGeneratedBy); // Editor only?
            if (Blueprint)
            {
                // Get the package path
                FString PackageName = Blueprint->GetOutermost()->GetName();
                return PackageName; // e.g., "/Game/Blueprints/MyBlueprint"
            }
            else
#endif // WITH_EDITOR
            {
                FString OutFullReferencePath = CallerClass->GetPathName();
                return OutFullReferencePath;
            }
        }

        return TEXT("");
    };

    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Blueprint Reflection", meta = (WorldContext = "WorldContextObject"))
    static void GetCallingBlueprintInfo(
        const UObject *WorldContextObject,
        FString &OutBlueprintName,
        FString &OutContentPath,
        FString &OutFullPath,
        FString &OutFullReferencePath)
    {
        OutBlueprintName = TEXT("Unknown");
        OutContentPath = TEXT("");
        OutFullPath = TEXT("");
        OutFullReferencePath = TEXT("");

        if (!WorldContextObject)
            return;

        UClass *CallerClass = WorldContextObject->GetClass();
        if (CallerClass)
        {
#if WITH_EDITOR
            UBlueprint *Blueprint = Cast<UBlueprint>(CallerClass->ClassGeneratedBy);
            if (Blueprint)
            {
                // Blueprint name
                OutBlueprintName = Blueprint->GetName();

                // Full package path
                FString PackageName = Blueprint->GetOutermost()->GetName();
                OutFullPath = PackageName;

                // Content folder relative path
                OutContentPath = PackageName.Replace(TEXT("/Game/"), TEXT("Content/"));

                // Full reference path (e.g., /Script/Engine.Blueprint'/Game/MyBlueprint.MyBlueprint')
                OutFullReferencePath = Blueprint->GetPathName();
            }
            else
#endif // WITH_EDITOR
            {
                // Fallback: Get class path even if not a Blueprint
                OutFullReferencePath = CallerClass->GetPathName();
                OutBlueprintName = CallerClass->GetName();
            }
        }
    };
};