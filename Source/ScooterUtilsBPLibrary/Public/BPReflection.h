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
    /**
     * Gets the name of the Blueprint that called this function
     * 
     * @param WorldContextObject    The object whose Blueprint class we want to identify. Usually 'self' in Blueprints.
     * @return                      The name of the calling Blueprint, or "Unknown" if it cannot be determined
     * 
     * Example: If called from BP_PlayerCharacter, returns "BP_PlayerCharacter"
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Blueprint Reflection", 
              meta = (WorldContext = "WorldContextObject",
                     ToolTip = "Gets the name of the Blueprint that called this function. Useful for debugging and logging.",
                     Keywords = "blueprint,name,class,get,reflection"))
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

    /**
     * Gets the content path of the Blueprint that called this function (editor only)
     * 
     * @param WorldContextObject    The object whose Blueprint path we want to get. Usually 'self' in Blueprints.
     * @return                      The full path to the Blueprint in the content browser, or empty string if not found
     * 
     * Example: If called from a Blueprint in Content/MyGame/BP_Player.uasset returns "/Game/MyGame/BP_Player"
     * Note: This function only works in editor builds, not in packaged games
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Blueprint Reflection", 
              meta = (WorldContext = "WorldContextObject",
                     ToolTip = "Gets the content path of the calling Blueprint. Editor-only functionality.",
                     Keywords = "blueprint,path,content,browser,get,reflection"))
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

    /**
     * Gets comprehensive information about the calling Blueprint (editor only)
     * 
     * @param WorldContextObject     The object to get Blueprint info from. Usually 'self' in Blueprints.
     * @param OutBlueprintName      The name of the Blueprint without path (e.g., "BP_Player")
     * @param OutContentPath        The path relative to Content folder (e.g., "Content/MyGame/Characters")
     * @param OutFullPath          The full package path (e.g., "/Game/MyGame/Characters/BP_Player")
     * @param OutFullReferencePath The complete reference path for the Blueprint
     * 
     * Example Usage:
     * - Call from BP_Player in Content/MyGame/Characters/
     * - OutBlueprintName = "BP_Player"
     * - OutContentPath = "Content/MyGame/Characters"
     * - OutFullPath = "/Game/MyGame/Characters/BP_Player"
     * - OutFullReferencePath = "/Script/Engine.Blueprint'/Game/MyGame/Characters/BP_Player.BP_Player'"
     * 
     * Note: This function provides the most detailed information in editor builds
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Blueprint Reflection", 
              meta = (WorldContext = "WorldContextObject",
                     ToolTip = "Gets detailed information about the calling Blueprint, including paths and references",
                     Keywords = "blueprint,info,path,reference,name,content,folder,get,reflection"))
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