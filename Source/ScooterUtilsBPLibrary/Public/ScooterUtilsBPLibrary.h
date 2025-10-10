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

	/**
     * Reads a string value from the engine's global config file (DefaultEngine.ini)
     * 
     * @param Section    The section in the INI file (e.g., "/Script/Engine.Engine")
     * @param Key        The key name to read (e.g., "GameViewportClientClassName")
     * @return          The string value from the config file, or empty string if not found
     * 
     * Example Usage:
     * - Section: "/Script/Engine.GameEngine"
     * - Key: "NetDriverDefinitions"
     * Returns the configuration value as a string
     */
	UFUNCTION(BlueprintPure, Category = "Scooter Utilities|Global Config",
              meta = (ToolTip = "Reads a string value from DefaultEngine.ini config file",
                     Keywords = "config,ini,engine,settings,read,string"))
	static FString GetGlobalConfigFileString(const FString &Section, const FString &Key)
	{
		FString Value;
		GConfig->GetString(*Section, *Key, Value, GEngineIni);
		return Value;
	}

	/**
     * Reads a float value from the engine's global config file (DefaultEngine.ini)
     * 
     * @param Section    The section in the INI file (e.g., "/Script/Engine.Engine")
     * @param Key        The key name to read (e.g., "MaximumLoopIterationCount")
     * @return          The float value from the config, or 0.0 if not found
     * 
     * Example: Use this to read numeric settings like timers, speeds, or distances
     */
	UFUNCTION(BlueprintPure, Category = "Scooter Utilities|Global Config",
              meta = (ToolTip = "Reads a float (decimal) value from DefaultEngine.ini",
                     Keywords = "config,ini,engine,settings,read,float,number,decimal"))
	static float GetGlobalConfigFileFloat(const FString &Section, const FString &Key)
	{
		float Value = 0.0f;
		GConfig->GetFloat(*Section, *Key, Value, GEngineIni);
		return Value;
	}

	/**
     * Reads a boolean value from the engine's global config file (DefaultEngine.ini)
     * 
     * @param Section    The section in the INI file (e.g., "/Script/Engine.Engine")
     * @param Key        The key name to read (e.g., "bUseFixedFrameRate")
     * @return          The boolean value from the config, or false if not found
     * 
     * Example: Use this to read true/false settings like feature flags or toggles
     */
	UFUNCTION(BlueprintPure, Category = "Scooter Utilities|Global Config",
              meta = (ToolTip = "Reads a boolean (true/false) value from DefaultEngine.ini",
                     Keywords = "config,ini,engine,settings,read,bool,boolean,true,false"))
	static bool GetGlobalConfigFileBool(const FString &Section, const FString &Key)
	{
		bool Value = false;
		GConfig->GetBool(*Section, *Key, Value, GEngineIni);
		return Value;
	}

	/**
     * Reads an integer value from the engine's global config file (DefaultEngine.ini)
     * 
     * @param Section    The section in the INI file (e.g., "/Script/Engine.Engine")
     * @param Key        The key name to read (e.g., "MaximumLoopIterationCount")
     * @return          The integer value from the config, or 0 if not found
     * 
     * Example: Use this to read whole number settings like counts, levels, or indices
     */
	UFUNCTION(BlueprintPure, Category = "Scooter Utilities|Global Config",
              meta = (ToolTip = "Reads an integer (whole number) value from DefaultEngine.ini",
                     Keywords = "config,ini,engine,settings,read,int,integer,number"))
	static int32 GetGlobalConfigFileInt(const FString &Section, const FString &Key)
	{
		int32 Value = 0;
		GConfig->GetInt(*Section, *Key, Value, GEngineIni);
		return Value;
	}

	/**
     * Writes a string value to the engine's global config file (DefaultEngine.ini)
     * 
     * @param Section    The section in the INI file (e.g., "/Script/Engine.Engine")
     * @param Key        The key name to write to (e.g., "GameViewportClientClassName")
     * @param Value      The string value to save
     * 
     * Example: Use this to save text settings like class names, paths, or text preferences
     * Note: Changes are saved immediately to the config file
     */
	UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Global Config",
              meta = (ToolTip = "Writes a string value to DefaultEngine.ini",
                     Keywords = "config,ini,engine,settings,write,save,string,text"))
	static void SetGlobalConfigFileString(const FString &Section, const FString &Key, const FString &Value)
	{
		GConfig->SetString(*Section, *Key, *Value, GEngineIni);
		GConfig->Flush(false, GEngineIni);
	}

	/**
     * Writes a float value to the engine's global config file (DefaultEngine.ini)
     * 
     * @param Section    The section in the INI file (e.g., "/Script/Engine.Engine")
     * @param Key        The key name to write to (e.g., "DefaultTimeDilation")
     * @param Value      The float value to save
     * 
     * Example: Use this to save decimal numbers like speeds, timers, or distances
     * Note: Changes are saved immediately to the config file
     */
	UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Global Config",
              meta = (ToolTip = "Writes a float (decimal) value to DefaultEngine.ini",
                     Keywords = "config,ini,engine,settings,write,save,float,decimal,number"))
	static void SetGlobalConfigFileFloat(const FString &Section, const FString &Key, float Value)
	{
		GConfig->SetFloat(*Section, *Key, Value, GEngineIni);
		GConfig->Flush(false, GEngineIni);
	}

	/**
     * Writes a boolean value to the engine's global config file (DefaultEngine.ini)
     * 
     * @param Section    The section in the INI file (e.g., "/Script/Engine.Engine")
     * @param Key        The key name to write to (e.g., "bUseFixedFrameRate")
     * @param Value      The boolean value to save
     * 
     * Example: Use this to save true/false settings like feature toggles or debug flags
     * Note: Changes are saved immediately to the config file
     */
	UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Global Config",
              meta = (ToolTip = "Writes a boolean (true/false) value to DefaultEngine.ini",
                     Keywords = "config,ini,engine,settings,write,save,bool,boolean,true,false"))
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
