// JSONBlueprintLibrary.cpp
#include "JSONBlueprintLibrary.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonReader.h"

// ========== Helper Functions ==========

TSharedPtr<FJsonObject> UJSONBlueprintLibrary::ParseJSONString(const FString &JSONString)
{
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JSONString);

    if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
    {
        return JsonObject;
    }

    return nullptr;
}

FString UJSONBlueprintLibrary::JSONObjectToString(const TSharedPtr<FJsonObject> &JsonObject)
{
    if (!JsonObject.IsValid())
    {
        return TEXT("{}");
    }

    FString OutputString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);

    if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer))
    {
        return OutputString;
    }

    return TEXT("{}");
}

// ========== JSON Creation Functions ==========

FString UJSONBlueprintLibrary::CreateEmptyJSON()
{
    return TEXT("{}");
}

FString UJSONBlueprintLibrary::AddStringField(const FString &JSONString, const FString &FieldName, const FString &Value)
{
    TSharedPtr<FJsonObject> JsonObject = ParseJSONString(JSONString);

    if (!JsonObject.IsValid())
    {
        JsonObject = MakeShareable(new FJsonObject());
    }

    JsonObject->SetStringField(FieldName, Value);
    return JSONObjectToString(JsonObject);
}

FString UJSONBlueprintLibrary::AddIntegerField(const FString &JSONString, const FString &FieldName, int32 Value)
{
    TSharedPtr<FJsonObject> JsonObject = ParseJSONString(JSONString);

    if (!JsonObject.IsValid())
    {
        JsonObject = MakeShareable(new FJsonObject());
    }

    JsonObject->SetNumberField(FieldName, Value);
    return JSONObjectToString(JsonObject);
}

FString UJSONBlueprintLibrary::AddFloatField(const FString &JSONString, const FString &FieldName, float Value)
{
    TSharedPtr<FJsonObject> JsonObject = ParseJSONString(JSONString);

    if (!JsonObject.IsValid())
    {
        JsonObject = MakeShareable(new FJsonObject());
    }

    JsonObject->SetNumberField(FieldName, Value);
    return JSONObjectToString(JsonObject);
}

FString UJSONBlueprintLibrary::AddBooleanField(const FString &JSONString, const FString &FieldName, bool Value)
{
    TSharedPtr<FJsonObject> JsonObject = ParseJSONString(JSONString);

    if (!JsonObject.IsValid())
    {
        JsonObject = MakeShareable(new FJsonObject());
    }

    JsonObject->SetBoolField(FieldName, Value);
    return JSONObjectToString(JsonObject);
}

FString UJSONBlueprintLibrary::AddVectorField(const FString &JSONString, const FString &FieldName, FVector Value)
{
    TSharedPtr<FJsonObject> JsonObject = ParseJSONString(JSONString);

    if (!JsonObject.IsValid())
    {
        JsonObject = MakeShareable(new FJsonObject());
    }

    TSharedPtr<FJsonObject> VectorObject = MakeShareable(new FJsonObject());
    VectorObject->SetNumberField(TEXT("X"), Value.X);
    VectorObject->SetNumberField(TEXT("Y"), Value.Y);
    VectorObject->SetNumberField(TEXT("Z"), Value.Z);

    JsonObject->SetObjectField(FieldName, VectorObject);
    return JSONObjectToString(JsonObject);
}

FString UJSONBlueprintLibrary::AddRotatorField(const FString &JSONString, const FString &FieldName, FRotator Value)
{
    TSharedPtr<FJsonObject> JsonObject = ParseJSONString(JSONString);

    if (!JsonObject.IsValid())
    {
        JsonObject = MakeShareable(new FJsonObject());
    }

    TSharedPtr<FJsonObject> RotatorObject = MakeShareable(new FJsonObject());
    RotatorObject->SetNumberField(TEXT("Pitch"), Value.Pitch);
    RotatorObject->SetNumberField(TEXT("Yaw"), Value.Yaw);
    RotatorObject->SetNumberField(TEXT("Roll"), Value.Roll);

    JsonObject->SetObjectField(FieldName, RotatorObject);
    return JSONObjectToString(JsonObject);
}

FString UJSONBlueprintLibrary::AddStringArrayField(const FString &JSONString, const FString &FieldName, const TArray<FString> &Values)
{
    TSharedPtr<FJsonObject> JsonObject = ParseJSONString(JSONString);

    if (!JsonObject.IsValid())
    {
        JsonObject = MakeShareable(new FJsonObject());
    }

    TArray<TSharedPtr<FJsonValue>> JsonArray;
    for (const FString &Value : Values)
    {
        JsonArray.Add(MakeShareable(new FJsonValueString(Value)));
    }

    JsonObject->SetArrayField(FieldName, JsonArray);
    return JSONObjectToString(JsonObject);
}

FString UJSONBlueprintLibrary::AddObjectField(const FString &JSONString, const FString &FieldName, const FString &NestedJSON)
{
    TSharedPtr<FJsonObject> JsonObject = ParseJSONString(JSONString);
    TSharedPtr<FJsonObject> NestedObject = ParseJSONString(NestedJSON);

    if (!JsonObject.IsValid())
    {
        JsonObject = MakeShareable(new FJsonObject());
    }

    if (!NestedObject.IsValid())
    {
        NestedObject = MakeShareable(new FJsonObject());
    }

    JsonObject->SetObjectField(FieldName, NestedObject);
    return JSONObjectToString(JsonObject);
}

// ========== JSON Parsing Functions ==========

bool UJSONBlueprintLibrary::IsValidJSON(const FString &JSONString)
{
    TSharedPtr<FJsonObject> JsonObject = ParseJSONString(JSONString);
    return JsonObject.IsValid();
}

bool UJSONBlueprintLibrary::GetStringField(const FString &JSONString, const FString &FieldName, FString &OutValue)
{
    TSharedPtr<FJsonObject> JsonObject = ParseJSONString(JSONString);

    if (!JsonObject.IsValid())
    {
        return false;
    }

    if (JsonObject->HasField(FieldName))
    {
        OutValue = JsonObject->GetStringField(FieldName);
        return true;
    }

    return false;
}

bool UJSONBlueprintLibrary::GetIntegerField(const FString &JSONString, const FString &FieldName, int32 &OutValue)
{
    TSharedPtr<FJsonObject> JsonObject = ParseJSONString(JSONString);

    if (!JsonObject.IsValid())
    {
        return false;
    }

    if (JsonObject->HasField(FieldName))
    {
        OutValue = JsonObject->GetIntegerField(FieldName);
        return true;
    }

    return false;
}

bool UJSONBlueprintLibrary::GetFloatField(const FString &JSONString, const FString &FieldName, float &OutValue)
{
    TSharedPtr<FJsonObject> JsonObject = ParseJSONString(JSONString);

    if (!JsonObject.IsValid())
    {
        return false;
    }

    if (JsonObject->HasField(FieldName))
    {
        OutValue = JsonObject->GetNumberField(FieldName);
        return true;
    }

    return false;
}

bool UJSONBlueprintLibrary::GetBooleanField(const FString &JSONString, const FString &FieldName, bool &OutValue)
{
    TSharedPtr<FJsonObject> JsonObject = ParseJSONString(JSONString);

    if (!JsonObject.IsValid())
    {
        return false;
    }

    if (JsonObject->HasField(FieldName))
    {
        OutValue = JsonObject->GetBoolField(FieldName);
        return true;
    }

    return false;
}

bool UJSONBlueprintLibrary::GetVectorField(const FString &JSONString, const FString &FieldName, FVector &OutValue)
{
    TSharedPtr<FJsonObject> JsonObject = ParseJSONString(JSONString);

    if (!JsonObject.IsValid())
    {
        return false;
    }

    if (JsonObject->HasField(FieldName))
    {
        const TSharedPtr<FJsonObject> *VectorObject;
        if (JsonObject->TryGetObjectField(FieldName, VectorObject))
        {
            if ((*VectorObject)->HasField(TEXT("X")) &&
                (*VectorObject)->HasField(TEXT("Y")) &&
                (*VectorObject)->HasField(TEXT("Z")))
            {
                OutValue.X = (*VectorObject)->GetNumberField(TEXT("X"));
                OutValue.Y = (*VectorObject)->GetNumberField(TEXT("Y"));
                OutValue.Z = (*VectorObject)->GetNumberField(TEXT("Z"));
                return true;
            }
        }
    }

    return false;
}

bool UJSONBlueprintLibrary::GetRotatorField(const FString &JSONString, const FString &FieldName, FRotator &OutValue)
{
    TSharedPtr<FJsonObject> JsonObject = ParseJSONString(JSONString);

    if (!JsonObject.IsValid())
    {
        return false;
    }

    if (JsonObject->HasField(FieldName))
    {
        const TSharedPtr<FJsonObject> *RotatorObject;
        if (JsonObject->TryGetObjectField(FieldName, RotatorObject))
        {
            if ((*RotatorObject)->HasField(TEXT("Pitch")) &&
                (*RotatorObject)->HasField(TEXT("Yaw")) &&
                (*RotatorObject)->HasField(TEXT("Roll")))
            {
                OutValue.Pitch = (*RotatorObject)->GetNumberField(TEXT("Pitch"));
                OutValue.Yaw = (*RotatorObject)->GetNumberField(TEXT("Yaw"));
                OutValue.Roll = (*RotatorObject)->GetNumberField(TEXT("Roll"));
                return true;
            }
        }
    }

    return false;
}

bool UJSONBlueprintLibrary::GetStringArrayField(const FString &JSONString, const FString &FieldName, TArray<FString> &OutValues)
{
    TSharedPtr<FJsonObject> JsonObject = ParseJSONString(JSONString);

    if (!JsonObject.IsValid())
    {
        return false;
    }

    if (JsonObject->HasField(FieldName))
    {
        const TArray<TSharedPtr<FJsonValue>> *JsonArray;
        if (JsonObject->TryGetArrayField(FieldName, JsonArray))
        {
            OutValues.Empty();
            for (const TSharedPtr<FJsonValue> &Value : *JsonArray)
            {
                OutValues.Add(Value->AsString());
            }
            return true;
        }
    }

    return false;
}

bool UJSONBlueprintLibrary::GetObjectField(const FString &JSONString, const FString &FieldName, FString &OutJSON)
{
    TSharedPtr<FJsonObject> JsonObject = ParseJSONString(JSONString);

    if (!JsonObject.IsValid())
    {
        return false;
    }

    if (JsonObject->HasField(FieldName))
    {
        const TSharedPtr<FJsonObject> *NestedObject;
        if (JsonObject->TryGetObjectField(FieldName, NestedObject))
        {
            OutJSON = JSONObjectToString(*NestedObject);
            return true;
        }
    }

    return false;
}

bool UJSONBlueprintLibrary::GetAllFieldNames(const FString &JSONString, TArray<FString> &OutFieldNames)
{
    TSharedPtr<FJsonObject> JsonObject = ParseJSONString(JSONString);

    if (!JsonObject.IsValid())
    {
        return false;
    }

    OutFieldNames.Empty();
    for (const auto &Entry : JsonObject->Values)
    {
        OutFieldNames.Add(Entry.Key);
    }

    return true;
}