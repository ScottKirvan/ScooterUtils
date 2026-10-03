# JSON C++ Reference

Build and parse JSON strings from C++ with `UJSONBlueprintLibrary`.

**Header:** `JSONBlueprintLibrary.h` · **Class:** `UJSONBlueprintLibrary`

Every function works on JSON objects stored as plain `FString` values. Creation functions return an updated copy of the string, and parsing functions return `bool` with the value in an output parameter. All functions are `static`. For detailed behavior and examples, see the [JSON nodes](../blueprint-nodes/json/).

> [!NOTE]
> Only JSON objects (`{...}`) are treated as valid at the top level. When the input string isn't a valid object, the add functions start over with a new, empty object.

## Enums

```cpp
enum class EJSONFieldType : uint8 { String, Number, Boolean };
enum class EJSONArrayType : uint8 { String, Number, Object };
```

| Value | Description |
| ----- | ----------- |
| `EJSONFieldType::String` | Stores the value as a JSON string. |
| `EJSONFieldType::Number` | Converts the value with `FCString::Atof` (single precision). Non-numeric text becomes `0`. |
| `EJSONFieldType::Boolean` | Converts the value with `FString::ToBool`. |
| `EJSONArrayType::String` | Each element is a JSON string. |
| `EJSONArrayType::Number` | Each element is converted to a number, as with `EJSONFieldType::Number`. |
| `EJSONArrayType::Object` | Each element is a JSON object string. Elements that aren't valid objects are skipped. |

## Creation Functions

| Name | Returns | Description |
| ---- | ------- | ----------- |
| `AddField(EJSONFieldType FieldType, const FString& JSONString, const FString& FieldName, const FString& Value)` | `FString` | Adds or replaces a field, converting `Value` based on `FieldType`. See [Add Field](../blueprint-nodes/json/creation#add-field). |
| `AddArrayField(EJSONArrayType ArrayType, const FString& JSONString, const FString& FieldName, const TArray<FString>& Values)` | `FString` | Adds an array field, converting each element based on `ArrayType`. See [Add Array Field](../blueprint-nodes/json/creation#add-array-field). |
| `AddObjectField(const FString& JSONString, const FString& FieldName, const FString& NestedJSON)` | `FString` | Nests a JSON object. An invalid `NestedJSON` nests `{}`. See [Add Object Field](../blueprint-nodes/json/creation#add-object-field). |
| `AddNullField(const FString& JSONString, const FString& FieldName)` | `FString` | Adds a field with a `null` value. See [Add Null Field](../blueprint-nodes/json/creation#add-null-field). |
| `RemoveField(const FString& JSONString, const FString& FieldName, bool& bSuccess)` | `FString` | Removes a field. `bSuccess` is `true` if the field existed. Invalid input is returned unchanged. See [Remove Field](../blueprint-nodes/json/creation#remove-field). |
| `MergeJSON(const FString& JSONString1, const FString& JSONString2)` | `FString` | Copies the top-level fields of the second object into the first, overwriting duplicates. See [Merge JSON](../blueprint-nodes/json/creation#merge-json). |
| `PrettyPrintJSON(const FString& JSONString)` | `FString` | Formats the JSON with indentation and line breaks. Invalid input is returned unchanged. See [Pretty Print JSON](../blueprint-nodes/json/creation#pretty-print-json). |
| `MinifyJSON(const FString& JSONString)` | `FString` | Removes all formatting whitespace. Invalid input is returned unchanged. See [Minify JSON](../blueprint-nodes/json/creation#minify-json). |

## Parsing Functions

| Name | Returns | Description |
| ---- | ------- | ----------- |
| `IsValidJSON(const FString& JSONString)` | `bool` | `true` if the string is a valid JSON object. See [Is Valid JSON](../blueprint-nodes/json/parsing#is-valid-json). |
| `HasField(const FString& JSONString, const FString& FieldName)` | `bool` | `true` if the field exists, including `null` fields. See [Has Field](../blueprint-nodes/json/parsing#has-field). |
| `IsFieldNull(const FString& JSONString, const FString& FieldName)` | `bool` | `true` if the field exists and is `null`. See [Is Field Null](../blueprint-nodes/json/parsing#is-field-null). |
| `GetStringField(const FString& JSONString, const FString& FieldName, FString& OutValue)` | `bool` | Reads a field as a string. See [Get String Field](../blueprint-nodes/json/parsing#get-string-field). |
| `GetNumberField(const FString& JSONString, const FString& FieldName, float& OutValue)` | `bool` | Reads a field as a `float`. See [Get Number Field](../blueprint-nodes/json/parsing#get-number-field). |
| `GetBooleanField(const FString& JSONString, const FString& FieldName, bool& OutValue)` | `bool` | Reads a field as a `bool`. See [Get Boolean Field](../blueprint-nodes/json/parsing#get-boolean-field). |
| `GetArrayField(EJSONArrayType ArrayType, const FString& JSONString, const FString& FieldName, TArray<FString>& OutValues)` | `bool` | Reads an array field, with each element as a string. Returns `true` if the field exists and is an array. See [Get Array Field](../blueprint-nodes/json/parsing#get-array-field). |
| `GetObjectField(const FString& JSONString, const FString& FieldName, FString& OutJSON)` | `bool` | Reads a nested object as a JSON string. Returns `true` if the field exists and is an object. See [Get Object Field](../blueprint-nodes/json/parsing#get-object-field). |
| `GetAllFieldNames(const FString& JSONString, TArray<FString>& OutFieldNames)` | `bool` | Lists the top-level field names. Returns `true` if the JSON is valid. See [Get All Field Names](../blueprint-nodes/json/parsing#get-all-field-names). |

`GetStringField`, `GetNumberField`, and `GetBooleanField` return `true` whenever the field exists, without checking its type. The output parameter is only written when they return `true`, so initialize it first.

## Example

Build a save object, write it to disk with [File IO](./file-io), then read it back:

```cpp
#include "JSONBlueprintLibrary.h"
#include "FileIO.h"

void UMySaveSystem::Save(const FString& PlayerName, int32 Level, const TArray<FString>& Inventory)
{
    FString Json;
    Json = UJSONBlueprintLibrary::AddField(EJSONFieldType::String, Json, TEXT("playerName"), PlayerName);
    Json = UJSONBlueprintLibrary::AddField(EJSONFieldType::Number, Json, TEXT("level"), FString::FromInt(Level));
    Json = UJSONBlueprintLibrary::AddArrayField(EJSONArrayType::String, Json, TEXT("inventory"), Inventory);

    FString SavedPath;
    UFileIO::SaveTextToFile(EFileLocation::ProjectSaved, TEXT("SaveGames/slot1.json"), UJSONBlueprintLibrary::PrettyPrintJSON(Json), SavedPath);
}

bool UMySaveSystem::Load(FString& OutPlayerName, int32& OutLevel, TArray<FString>& OutInventory)
{
    FString Json;
    FString LoadedPath;
    if (!UFileIO::LoadFileToString(EFileLocation::ProjectSaved, TEXT("SaveGames/slot1.json"), Json, LoadedPath)
        || !UJSONBlueprintLibrary::IsValidJSON(Json))
    {
        return false;
    }

    float LevelValue = 0.0f;
    UJSONBlueprintLibrary::GetStringField(Json, TEXT("playerName"), OutPlayerName);
    UJSONBlueprintLibrary::GetNumberField(Json, TEXT("level"), LevelValue);
    UJSONBlueprintLibrary::GetArrayField(EJSONArrayType::String, Json, TEXT("inventory"), OutInventory);

    OutLevel = FMath::RoundToInt(LevelValue);
    return true;
}
```
