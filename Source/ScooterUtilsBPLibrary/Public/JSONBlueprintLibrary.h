// JSONBlueprintLibrary.h
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Dom/JsonObject.h"
#include "JSONBlueprintLibrary.generated.h"

/**
 * Blueprint function library for JSON creation and parsing
 */
UCLASS()
class UJSONBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // ========== JSON Creation Functions ==========

    /**
     * Create an empty JSON object string
     * @return Empty JSON object "{}"
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Creation")
    static FString CreateEmptyJSON();

    /**
     * Add a string field to a JSON string
     * @param JSONString The existing JSON string
     * @param FieldName The field name to add
     * @param Value The string value
     * @return Updated JSON string
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Creation")
    static FString AddStringField(const FString &JSONString, const FString &FieldName, const FString &Value);

    /**
     * Add an integer field to a JSON string
     * @param JSONString The existing JSON string
     * @param FieldName The field name to add
     * @param Value The integer value
     * @return Updated JSON string
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Creation")
    static FString AddIntegerField(const FString &JSONString, const FString &FieldName, int32 Value);

    /**
     * Add a float field to a JSON string
     * @param JSONString The existing JSON string
     * @param FieldName The field name to add
     * @param Value The float value
     * @return Updated JSON string
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Creation")
    static FString AddFloatField(const FString &JSONString, const FString &FieldName, float Value);

    /**
     * Add a boolean field to a JSON string
     * @param JSONString The existing JSON string
     * @param FieldName The field name to add
     * @param Value The boolean value
     * @return Updated JSON string
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Creation")
    static FString AddBooleanField(const FString &JSONString, const FString &FieldName, bool Value);

    /**
     * Add a Vector field to a JSON string (stored as object with X, Y, Z)
     * @param JSONString The existing JSON string
     * @param FieldName The field name to add
     * @param Value The vector value
     * @return Updated JSON string
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Creation")
    static FString AddVectorField(const FString &JSONString, const FString &FieldName, FVector Value);

    /**
     * Add a Rotator field to a JSON string (stored as object with Pitch, Yaw, Roll)
     * @param JSONString The existing JSON string
     * @param FieldName The field name to add
     * @param Value The rotator value
     * @return Updated JSON string
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Creation")
    static FString AddRotatorField(const FString &JSONString, const FString &FieldName, FRotator Value);

    /**
     * Add a string array field to a JSON string
     * @param JSONString The existing JSON string
     * @param FieldName The field name to add
     * @param Values The string array
     * @return Updated JSON string
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Creation")
    static FString AddStringArrayField(const FString &JSONString, const FString &FieldName, const TArray<FString> &Values);

    /**
     * Add a nested JSON object field
     * @param JSONString The existing JSON string
     * @param FieldName The field name to add
     * @param NestedJSON The nested JSON string to add
     * @return Updated JSON string
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Creation")
    static FString AddObjectField(const FString &JSONString, const FString &FieldName, const FString &NestedJSON);

    // ========== JSON Parsing Functions ==========

    /**
     * Check if a JSON string is valid
     * @param JSONString The JSON string to validate
     * @return True if valid, false otherwise
     */
    UFUNCTION(BlueprintPure, Category = "Scooter Utilities|JSON|Parsing")
    static bool IsValidJSON(const FString &JSONString);

    /**
     * Get a string field from a JSON string
     * @param JSONString The JSON string to parse
     * @param FieldName The field name to retrieve
     * @param OutValue The retrieved string value
     * @return True if field exists and is a string, false otherwise
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Parsing")
    static bool GetStringField(const FString &JSONString, const FString &FieldName, FString &OutValue);

    /**
     * Get an integer field from a JSON string
     * @param JSONString The JSON string to parse
     * @param FieldName The field name to retrieve
     * @param OutValue The retrieved integer value
     * @return True if field exists and is a number, false otherwise
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Parsing")
    static bool GetIntegerField(const FString &JSONString, const FString &FieldName, int32 &OutValue);

    /**
     * Get a float field from a JSON string
     * @param JSONString The JSON string to parse
     * @param FieldName The field name to retrieve
     * @param OutValue The retrieved float value
     * @return True if field exists and is a number, false otherwise
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Parsing")
    static bool GetFloatField(const FString &JSONString, const FString &FieldName, float &OutValue);

    /**
     * Get a boolean field from a JSON string
     * @param JSONString The JSON string to parse
     * @param FieldName The field name to retrieve
     * @param OutValue The retrieved boolean value
     * @return True if field exists and is a boolean, false otherwise
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Parsing")
    static bool GetBooleanField(const FString &JSONString, const FString &FieldName, bool &OutValue);

    /**
     * Get a Vector field from a JSON string (reads object with X, Y, Z)
     * @param JSONString The JSON string to parse
     * @param FieldName The field name to retrieve
     * @param OutValue The retrieved vector value
     * @return True if field exists and has X, Y, Z components, false otherwise
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Parsing")
    static bool GetVectorField(const FString &JSONString, const FString &FieldName, FVector &OutValue);

    /**
     * Get a Rotator field from a JSON string (reads object with Pitch, Yaw, Roll)
     * @param JSONString The JSON string to parse
     * @param FieldName The field name to retrieve
     * @param OutValue The retrieved rotator value
     * @return True if field exists and has Pitch, Yaw, Roll components, false otherwise
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Parsing")
    static bool GetRotatorField(const FString &JSONString, const FString &FieldName, FRotator &OutValue);

    /**
     * Get a string array field from a JSON string
     * @param JSONString The JSON string to parse
     * @param FieldName The field name to retrieve
     * @param OutValues The retrieved string array
     * @return True if field exists and is an array, false otherwise
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Parsing")
    static bool GetStringArrayField(const FString &JSONString, const FString &FieldName, TArray<FString> &OutValues);

    /**
     * Get a nested JSON object as a string
     * @param JSONString The JSON string to parse
     * @param FieldName The field name to retrieve
     * @param OutJSON The retrieved nested JSON string
     * @return True if field exists and is an object, false otherwise
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Parsing")
    static bool GetObjectField(const FString &JSONString, const FString &FieldName, FString &OutJSON);

    /**
     * Get all field names from a JSON string
     * @param JSONString The JSON string to parse
     * @param OutFieldNames Array of all field names in the JSON object
     * @return True if successful, false otherwise
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Parsing")
    static bool GetAllFieldNames(const FString &JSONString, TArray<FString> &OutFieldNames);

private:
    // Helper functions
    static TSharedPtr<FJsonObject> ParseJSONString(const FString &JSONString);
    static FString JSONObjectToString(const TSharedPtr<FJsonObject> &JsonObject);
};