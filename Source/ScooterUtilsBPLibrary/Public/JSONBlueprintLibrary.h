// JSONBlueprintLibrary.h
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Dom/JsonObject.h"
#include "JSONBlueprintLibrary.generated.h"

/**
 * Enum for JSON field types
 */
UENUM(BlueprintType)
enum class EJSONFieldType : uint8
{
    String UMETA(DisplayName = "String"),
    Number UMETA(DisplayName = "Number"),
    Boolean UMETA(DisplayName = "Boolean")
};

/**
 * Enum for JSON array types
 */
UENUM(BlueprintType)
enum class EJSONArrayType : uint8
{
    String UMETA(DisplayName = "String Array"),
    Number UMETA(DisplayName = "Number Array"),
    Object UMETA(DisplayName = "Object Array")
};

/**
 * Blueprint function library for JSON creation and parsing
 */
UCLASS()
class SCOOTERUTILSBPLIBRARYMODULE_API UJSONBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // ========== JSON Creation Functions ==========

    /**
     * Add a field to a JSON string (type selected via dropdown)
     * @param FieldType The type of field to add
     * @param JSONString The existing JSON string (can be empty)
     * @param FieldName The field name to add
     * @param Value The value as a string (will be converted based on FieldType)
     * @return Updated JSON string
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Creation", meta = (ReturnDisplayName = "JSON String Out"))
    static FString AddField(EJSONFieldType FieldType, const FString &JSONString, const FString &FieldName, const FString &Value);

    /**
     * Add an array field to a JSON string (type selected via dropdown)
     * @param ArrayType The type of array to add
     * @param JSONString The existing JSON string (can be empty)
     * @param FieldName The field name to add
     * @param Values The array values as strings (will be converted based on ArrayType)
     * @return Updated JSON string
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Creation", meta = (ReturnDisplayName = "JSON String Out"))
    static FString AddArrayField(EJSONArrayType ArrayType, const FString &JSONString, const FString &FieldName, const TArray<FString> &Values);

    /**
     * Add a nested JSON object field
     * @param JSONString The existing JSON string (can be empty)
     * @param FieldName The field name to add
     * @param NestedJSON The nested JSON string to add
     * @return Updated JSON string
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Creation", meta = (ReturnDisplayName = "JSON String Out"))
    static FString AddObjectField(const FString &JSONString, const FString &FieldName, const FString &NestedJSON);

    /**
     * Add a null field to a JSON string
     * @param JSONString The existing JSON string (can be empty)
     * @param FieldName The field name to add
     * @return Updated JSON string
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Creation", meta = (ReturnDisplayName = "JSON String Out"))
    static FString AddNullField(const FString &JSONString, const FString &FieldName);

    /**
     * Remove a field from a JSON string
     * @param JSONString The existing JSON string
     * @param FieldName The field name to remove
     * @param bSuccess Whether the field was successfully removed
     * @return Updated JSON string
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Creation", meta = (ReturnDisplayName = "JSON String Out"))
    static FString RemoveField(const FString &JSONString, const FString &FieldName, bool &bSuccess);

    /**
     * Merge two JSON objects (fields from JSON2 are added to JSON1, overwriting duplicates)
     * @param JSONString1 The first JSON string (base)
     * @param JSONString2 The second JSON string (to merge in)
     * @return Merged JSON string
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Creation", meta = (ReturnDisplayName = "JSON String Out"))
    static FString MergeJSON(const FString &JSONString1, const FString &JSONString2);

    /**
     * Pretty print a JSON string with indentation
     * @param JSONString The JSON string to format
     * @return Formatted JSON string
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Creation", meta = (ReturnDisplayName = "JSON String Out"))
    static FString PrettyPrintJSON(const FString &JSONString);

    // ========== JSON Parsing Functions ==========

    /**
     * Check if a JSON string is valid
     * @param JSONString The JSON string to validate
     * @return True if valid, false otherwise
     */
    UFUNCTION(BlueprintPure, Category = "Scooter Utilities|JSON|Parsing")
    static bool IsValidJSON(const FString &JSONString);

    /**
     * Check if a field exists in a JSON string
     * @param JSONString The JSON string to check
     * @param FieldName The field name to look for
     * @return True if field exists, false otherwise
     */
    UFUNCTION(BlueprintPure, Category = "Scooter Utilities|JSON|Parsing")
    static bool HasField(const FString &JSONString, const FString &FieldName);

    /**
     * Check if a field is null in a JSON string
     * @param JSONString The JSON string to check
     * @param FieldName The field name to check
     * @return True if field exists and is null, false otherwise
     */
    UFUNCTION(BlueprintPure, Category = "Scooter Utilities|JSON|Parsing")
    static bool IsFieldNull(const FString &JSONString, const FString &FieldName);

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
     * Get a number field from a JSON string
     * @param JSONString The JSON string to parse
     * @param FieldName The field name to retrieve
     * @param OutValue The retrieved numeric value
     * @return True if field exists and is a number, false otherwise
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Parsing")
    static bool GetNumberField(const FString &JSONString, const FString &FieldName, float &OutValue);

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
     * Get an array field from a JSON string (type selected via dropdown)
     * @param ArrayType The expected type of array
     * @param JSONString The JSON string to parse
     * @param FieldName The field name to retrieve
     * @param OutValues The retrieved array values as strings
     * @return True if field exists and is an array, false otherwise
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Parsing")
    static bool GetArrayField(EJSONArrayType ArrayType, const FString &JSONString, const FString &FieldName, TArray<FString> &OutValues);

    /**
     * Get a nested JSON object as a string
     * @param JSONString The JSON string to parse
     * @param FieldName The field name to retrieve
     * @param OutJSON The retrieved nested JSON string
     * @return True if field exists and is an object, false otherwise
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Parsing", meta = (DisplayName = "Get Object Field"))
    static bool GetObjectField(const FString &JSONString, const FString &FieldName, FString &OutJSON);

    /**
     * Get all field names from a JSON string
     * @param JSONString The JSON string to parse
     * @param OutFieldNames Array of all field names in the JSON object
     * @return True if successful, false otherwise
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|JSON|Parsing")
    static bool GetAllFieldNames(const FString &JSONString, TArray<FString> &OutFieldNames);
};