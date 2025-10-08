// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ScooterUtilsBPLibrary.generated.h"

/*
 *	Function library class.
 *	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
 *
 *	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
 *	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
 *	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
 *	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
 *				Its lets you name the node using characters not allowed in C++ function names.
 *	CompactNodeTitle - the word(s) that appear on the node.
 *	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu.
 *				Good example is "Print String" node which you can find also by using keyword "log".
 *	Category -	the category your node will be under in the Blueprint drop-down menu.
 *
 *	For more info on custom blueprint nodes visit documentation:
 *	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
 */

UCLASS()
class UScooterUtilsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	// Read a value from the global config file (e.g. DefaultEngine.ini).
	// String version
	UFUNCTION(BlueprintPure, Category = "Scooter Utilities|Global Config")
	static FString GetGlobalConfigFileString(const FString &Section, const FString &Key)
	{
		FString Value;
		GConfig->GetString(*Section, *Key, Value, GEngineIni);
		return Value;
	}

	// Read a value from the global config file (e.g. DefaultEngine.ini).
	// Float version
	UFUNCTION(BlueprintPure, Category = "Scooter Utilities|Global Config")
	static float GetGlobalConfigFileFloat(const FString &Section, const FString &Key)
	{
		float Value = 0.0f;
		GConfig->GetFloat(*Section, *Key, Value, GEngineIni);
		return Value;
	}

	// Read a value from the global config file (e.g. DefaultEngine.ini).
	// Bool version
	UFUNCTION(BlueprintPure, Category = "Scooter Utilities|Global Config")
	static bool GetGlobalConfigFileBool(const FString &Section, const FString &Key)
	{
		bool Value = false;
		GConfig->GetBool(*Section, *Key, Value, GEngineIni);
		return Value;
	}

	// Read a value from the global config file (e.g. DefaultEngine.ini).
	// Int version
	UFUNCTION(BlueprintPure, Category = "Scooter Utilities|Global Config")
	static int32 GetGlobalConfigFileInt(const FString &Section, const FString &Key)
	{
		int32 Value = 0;
		GConfig->GetInt(*Section, *Key, Value, GEngineIni);
		return Value;
	}

	// Set a value in the global config file (e.g. DefaultEngine.ini).
	// String version
	UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Global Config")
	static void SetGlobalConfigFileString(const FString &Section, const FString &Key, const FString &Value)
	{
		GConfig->SetString(*Section, *Key, *Value, GEngineIni);
		GConfig->Flush(false, GEngineIni);
	}

	// Set a value in the global config file (e.g. DefaultEngine.ini).
	// Float version
	UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Global Config")
	static void SetGlobalConfigFileFloat(const FString &Section, const FString &Key, float Value)
	{
		GConfig->SetFloat(*Section, *Key, Value, GEngineIni);
		GConfig->Flush(false, GEngineIni);
	}

	// Set a value in the global config file (e.g. DefaultEngine.ini).
	// Bool version
	UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Global Config")
	static void SetGlobalConfigFileBool(const FString &Section, const FString &Key, bool Value)
	{
		GConfig->SetBool(*Section, *Key, Value, GEngineIni);
		GConfig->Flush(false, GEngineIni);
	}

	// Set a value in the global config file (e.g. DefaultEngine.ini).
	// Int version
	UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Global Config")
	static void SetGlobalConfigFileInt(const FString &Section, const FString &Key, int32 Value)
	{
		GConfig->SetInt(*Section, *Key, Value, GEngineIni);
		GConfig->Flush(false, GEngineIni);
	}
};
