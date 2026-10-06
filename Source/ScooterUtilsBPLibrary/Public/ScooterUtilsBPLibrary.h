// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Misc/ConfigCacheIni.h"
#include "ScooterUtilsBPLibrary.generated.h"

UENUM(BlueprintType)
enum class EGlobalConfigScope : uint8
{
	Project UMETA(DisplayName = "Project"),
	UserGlobal UMETA(DisplayName = "User Global")
};

UENUM(BlueprintType)
enum class EGlobalConfigResult : uint8
{
	Success UMETA(DisplayName = "Success"),
	KeyNotFound UMETA(DisplayName = "Key Not Found"),
	InvalidInput UMETA(DisplayName = "Invalid Input"),
	ConfigUnavailable UMETA(DisplayName = "Config Unavailable"),
	SaveFailed UMETA(DisplayName = "Save Failed")
};

UCLASS()
class SCOOTERUTILSBPLIBRARYMODULE_API UScooterUtilsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/**
	 * Reads a string value from the selected config scope.
	 *
	 * @param Section The INI section containing the value.
	 * @param Key The key to read.
	 * @param Scope The project or current-user editor settings config to read.
	 * @param OutSection Pass-through copy of Section.
	 * @param OutKey Pass-through copy of Key.
	 * @param OutScope Pass-through copy of Scope.
	 * @param OutResult Success when found; otherwise the failure category.
	 * @param OutReason Empty on success; otherwise explains why the read failed.
	 * @return The string value, or an empty string if the key was not found.
	 */
	UFUNCTION(BlueprintPure, Category = "Scooter Utilities|Global Config",
		meta = (CPP_Default_Scope = "UserGlobal", ToolTip = "Reads a string value from the selected config scope",
			Keywords = "config,ini,project,user,editor,settings,read,string"))
	static FString GetGlobalConfigFileString(
		const FString &Section,
		const FString &Key,
		EGlobalConfigScope Scope,
		FString &OutSection,
		FString &OutKey,
		EGlobalConfigScope &OutScope,
		EGlobalConfigResult &OutResult,
		FString &OutReason);

	/**
	 * Reads a float value from the selected config scope.
	 *
	 * @param Section The INI section containing the value.
	 * @param Key The key to read.
	 * @param Scope The project or current-user editor settings config to read.
	 * @param OutSection Pass-through copy of Section.
	 * @param OutKey Pass-through copy of Key.
	 * @param OutScope Pass-through copy of Scope.
	 * @param OutResult Success when found; otherwise the failure category.
	 * @param OutReason Empty on success; otherwise explains why the read failed.
	 * @return The float value, or 0.0 if the key was not found.
	 */
	UFUNCTION(BlueprintPure, Category = "Scooter Utilities|Global Config",
		meta = (CPP_Default_Scope = "UserGlobal", ToolTip = "Reads a float value from the selected config scope",
			Keywords = "config,ini,project,user,editor,settings,read,float,number,decimal"))
	static float GetGlobalConfigFileFloat(
		const FString &Section,
		const FString &Key,
		EGlobalConfigScope Scope,
		FString &OutSection,
		FString &OutKey,
		EGlobalConfigScope &OutScope,
		EGlobalConfigResult &OutResult,
		FString &OutReason);

	/**
	 * Reads a boolean value from the selected config scope.
	 *
	 * @param Section The INI section containing the value.
	 * @param Key The key to read.
	 * @param Scope The project or current-user editor settings config to read.
	 * @param OutSection Pass-through copy of Section.
	 * @param OutKey Pass-through copy of Key.
	 * @param OutScope Pass-through copy of Scope.
	 * @param OutResult Success when found; otherwise the failure category.
	 * @param OutReason Empty on success; otherwise explains why the read failed.
	 * @return The boolean value, or false if the key was not found.
	 */
	UFUNCTION(BlueprintPure, Category = "Scooter Utilities|Global Config",
		meta = (CPP_Default_Scope = "UserGlobal", ToolTip = "Reads a boolean value from the selected config scope",
			Keywords = "config,ini,project,user,editor,settings,read,bool,boolean,true,false"))
	static bool GetGlobalConfigFileBool(
		const FString &Section,
		const FString &Key,
		EGlobalConfigScope Scope,
		FString &OutSection,
		FString &OutKey,
		EGlobalConfigScope &OutScope,
		EGlobalConfigResult &OutResult,
		FString &OutReason);

	/**
	 * Reads an integer value from the selected config scope.
	 *
	 * @param Section The INI section containing the value.
	 * @param Key The key to read.
	 * @param Scope The project or current-user editor settings config to read.
	 * @param OutSection Pass-through copy of Section.
	 * @param OutKey Pass-through copy of Key.
	 * @param OutScope Pass-through copy of Scope.
	 * @param OutResult Success when found; otherwise the failure category.
	 * @param OutReason Empty on success; otherwise explains why the read failed.
	 * @return The integer value, or 0 if the key was not found.
	 */
	UFUNCTION(BlueprintPure, Category = "Scooter Utilities|Global Config",
		meta = (CPP_Default_Scope = "UserGlobal", ToolTip = "Reads an integer value from the selected config scope",
			Keywords = "config,ini,project,user,editor,settings,read,int,integer,number"))
	static int32 GetGlobalConfigFileInt(
		const FString &Section,
		const FString &Key,
		EGlobalConfigScope Scope,
		FString &OutSection,
		FString &OutKey,
		EGlobalConfigScope &OutScope,
		EGlobalConfigResult &OutResult,
		FString &OutReason);

	/**
	 * Writes a string value to the selected config scope and verifies it was saved.
	 *
	 * @param Section The INI section to write.
	 * @param Key The key to write.
	 * @param Value The string value to save.
	 * @param Scope The project or current-user editor settings config to write.
	 * @param OutSection Pass-through copy of Section.
	 * @param OutKey Pass-through copy of Key.
	 * @param OutValue Pass-through copy of Value.
	 * @param OutScope Pass-through copy of Scope.
	 * @param OutReason Empty on success; otherwise explains why the save failed.
	 * @return Success only if the value can be read back from the saved file.
	 */
	UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Global Config",
		meta = (CPP_Default_Scope = "UserGlobal", ReturnDisplayName = "Result",
			ToolTip = "Writes a string value to the selected config scope and verifies it was saved",
			Keywords = "config,ini,project,user,editor,settings,write,save,string,text"))
	static EGlobalConfigResult SetGlobalConfigFileString(
		const FString &Section,
		const FString &Key,
		const FString &Value,
		EGlobalConfigScope Scope,
		FString &OutSection,
		FString &OutKey,
		FString &OutValue,
		EGlobalConfigScope &OutScope,
		FString &OutReason);

	/**
	 * Writes a float value to the selected config scope and verifies it was saved.
	 *
	 * @param Section The INI section to write.
	 * @param Key The key to write.
	 * @param Value The float value to save.
	 * @param Scope The project or current-user editor settings config to write.
	 * @param OutSection Pass-through copy of Section.
	 * @param OutKey Pass-through copy of Key.
	 * @param OutValue Pass-through copy of Value.
	 * @param OutScope Pass-through copy of Scope.
	 * @param OutReason Empty on success; otherwise explains why the save failed.
	 * @return Success only if the value can be read back from the saved file.
	 */
	UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Global Config",
		meta = (CPP_Default_Scope = "UserGlobal", ReturnDisplayName = "Result",
			ToolTip = "Writes a float value to the selected config scope and verifies it was saved",
			Keywords = "config,ini,project,user,editor,settings,write,save,float,decimal,number"))
	static EGlobalConfigResult SetGlobalConfigFileFloat(
		const FString &Section,
		const FString &Key,
		float Value,
		EGlobalConfigScope Scope,
		FString &OutSection,
		FString &OutKey,
		float &OutValue,
		EGlobalConfigScope &OutScope,
		FString &OutReason);

	/**
	 * Writes a boolean value to the selected config scope and verifies it was saved.
	 *
	 * @param Section The INI section to write.
	 * @param Key The key to write.
	 * @param Value The boolean value to save.
	 * @param Scope The project or current-user editor settings config to write.
	 * @param OutSection Pass-through copy of Section.
	 * @param OutKey Pass-through copy of Key.
	 * @param OutValue Pass-through copy of Value.
	 * @param OutScope Pass-through copy of Scope.
	 * @param OutReason Empty on success; otherwise explains why the save failed.
	 * @return Success only if the value can be read back from the saved file.
	 */
	UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Global Config",
		meta = (CPP_Default_Scope = "UserGlobal", ReturnDisplayName = "Result",
			ToolTip = "Writes a boolean value to the selected config scope and verifies it was saved",
			Keywords = "config,ini,project,user,editor,settings,write,save,bool,boolean,true,false"))
	static EGlobalConfigResult SetGlobalConfigFileBool(
		const FString &Section,
		const FString &Key,
		bool Value,
		EGlobalConfigScope Scope,
		FString &OutSection,
		FString &OutKey,
		bool &OutValue,
		EGlobalConfigScope &OutScope,
		FString &OutReason);

	/**
	 * Writes an integer value to the selected config scope and verifies it was saved.
	 *
	 * @param Section The INI section to write.
	 * @param Key The key to write.
	 * @param Value The integer value to save.
	 * @param Scope The project or current-user editor settings config to write.
	 * @param OutSection Pass-through copy of Section.
	 * @param OutKey Pass-through copy of Key.
	 * @param OutValue Pass-through copy of Value.
	 * @param OutScope Pass-through copy of Scope.
	 * @param OutReason Empty on success; otherwise explains why the save failed.
	 * @return Success only if the value can be read back from the saved file.
	 */
	UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Global Config",
		meta = (CPP_Default_Scope = "UserGlobal", ReturnDisplayName = "Result",
			ToolTip = "Writes an integer value to the selected config scope and verifies it was saved",
			Keywords = "config,ini,project,user,editor,settings,write,save,int,integer,number"))
	static EGlobalConfigResult SetGlobalConfigFileInt(
		const FString &Section,
		const FString &Key,
		int32 Value,
		EGlobalConfigScope Scope,
		FString &OutSection,
		FString &OutKey,
		int32 &OutValue,
		EGlobalConfigScope &OutScope,
		FString &OutReason);

};
