// JSONBlueprintLibrary.cpp
#include "JSONBlueprintLibrary.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonReader.h"
#include "DebugPrint.h"

// ========== Helper Functions (not class members) ==========

TSharedPtr<FJsonObject> ParseToJSONObject(const FString &JSONString)
{
    TSharedPtr<FJsonObject> JSONObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JSONString);

    if (FJsonSerializer::Deserialize(Reader, JSONObject) && JSONObject.IsValid())
    {
        return JSONObject;
    }

    return nullptr;
}

FString JSONObjectToString(const TSharedPtr<FJsonObject> &JSONObject)
{
    if (!JSONObject.IsValid())
    {
        return TEXT("{}");
    }

    FString OutputString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);

    if (FJsonSerializer::Serialize(JSONObject.ToSharedRef(), Writer))
    {
        return OutputString;
    }

    return TEXT("{}");
}

TSharedPtr<FJsonObject> ParseJSONString(const FString &JSONString)
{
    return ParseToJSONObject(JSONString);
}

// ========== JSON Creation Functions ==========

FString UJSONBlueprintLibrary::AddField(EJSONFieldType FieldType, const FString &JSONString, const FString &FieldName, const FString &Value)
{
    TSharedPtr<FJsonObject> JSONObject = ParseJSONString(JSONString);

    if (!JSONObject.IsValid())
    {
        JSONObject = MakeShareable(new FJsonObject());
    }

    switch (FieldType)
    {
    case EJSONFieldType::String:
        JSONObject->SetStringField(FieldName, Value);
        break;

    case EJSONFieldType::Number:
    {
        float NumValue = FCString::Atof(*Value);
        JSONObject->SetNumberField(FieldName, NumValue);
    }
    break;

    case EJSONFieldType::Boolean:
    {
        bool BoolValue = Value.ToBool();
        JSONObject->SetBoolField(FieldName, BoolValue);
    }
    break;
    }

    return ::JSONObjectToString(JSONObject);
}

FString UJSONBlueprintLibrary::AddArrayField(EJSONArrayType ArrayType, const FString &JSONString, const FString &FieldName, const TArray<FString> &Values)
{
    TSharedPtr<FJsonObject> JSONObject = ::ParseJSONString(JSONString);

    if (!JSONObject.IsValid())
    {
        JSONObject = MakeShareable(new FJsonObject());
    }

    TArray<TSharedPtr<FJsonValue>> JSONArray;

    switch (ArrayType)
    {
    case EJSONArrayType::String:
        for (const FString &Value : Values)
        {
            JSONArray.Add(MakeShareable(new FJsonValueString(Value)));
        }
        break;

    case EJSONArrayType::Number:
        for (const FString &Value : Values)
        {
            float NumValue = FCString::Atof(*Value);
            JSONArray.Add(MakeShareable(new FJsonValueNumber(NumValue)));
        }
        break;

    case EJSONArrayType::Object:
        for (const FString &Value : Values)
        {
            TSharedPtr<FJsonObject> NestedObject = ::ParseJSONString(Value);
            if (NestedObject.IsValid())
            {
                JSONArray.Add(MakeShareable(new FJsonValueObject(NestedObject)));
            }
        }
        break;
    }

    JSONObject->SetArrayField(FieldName, JSONArray);
    return ::JSONObjectToString(JSONObject);
}

FString UJSONBlueprintLibrary::AddObjectField(const FString &JSONString, const FString &FieldName, const FString &NestedJSON)
{
    TSharedPtr<FJsonObject> JSONObject = ::ParseJSONString(JSONString);
    TSharedPtr<FJsonObject> NestedObject = ::ParseJSONString(NestedJSON);

    if (!JSONObject.IsValid())
    {
        JSONObject = MakeShareable(new FJsonObject());
    }

    if (!NestedObject.IsValid())
    {
        NestedObject = MakeShareable(new FJsonObject());
    }

    JSONObject->SetObjectField(FieldName, NestedObject);
    return ::JSONObjectToString(JSONObject);
}

FString UJSONBlueprintLibrary::AddNullField(const FString &JSONString, const FString &FieldName)
{
    TSharedPtr<FJsonObject> JSONObject = ::ParseJSONString(JSONString);

    if (!JSONObject.IsValid())
    {
        JSONObject = MakeShareable(new FJsonObject());
    }

    JSONObject->SetField(FieldName, MakeShareable(new FJsonValueNull()));
    return ::JSONObjectToString(JSONObject);
}

FString UJSONBlueprintLibrary::RemoveField(const FString &JSONString, const FString &FieldName, bool &bSuccess)
{
    TSharedPtr<FJsonObject> JSONObject = ::ParseJSONString(JSONString);

    if (!JSONObject.IsValid())
    {
        bSuccess = false;
        return JSONString;
    }

    bSuccess = JSONObject->HasField(FieldName);
    if (bSuccess)
    {
        JSONObject->RemoveField(FieldName);
    }

    return ::JSONObjectToString(JSONObject);
}

FString UJSONBlueprintLibrary::MergeJSON(const FString &JSONString1, const FString &JSONString2)
{
    TSharedPtr<FJsonObject> JSONObject1 = ::ParseJSONString(JSONString1);
    TSharedPtr<FJsonObject> JSONObject2 = ::ParseJSONString(JSONString2);

    if (!JSONObject1.IsValid())
    {
        JSONObject1 = MakeShareable(new FJsonObject());
    }

    if (!JSONObject2.IsValid())
    {
        return ::JSONObjectToString(JSONObject1);
    }

    // Copy all fields from JSONObject2 into JSONObject1
    for (const auto &Field : JSONObject2->Values)
    {
        JSONObject1->SetField(Field.Key, Field.Value);
    }

    return ::JSONObjectToString(JSONObject1);
}

FString UJSONBlueprintLibrary::PrettyPrintJSON(const FString &JSONString)
{
    TSharedPtr<FJsonObject> JSONObject = ::ParseJSONString(JSONString);

    if (!JSONObject.IsValid())
    {
        return JSONString;
    }

    SCOOTER_DEBUG_PRINT(TEXT(""), EDebugLevel::Info, TEXT(""));
    FString OutputString;
    TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> Writer =
        TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&OutputString);

    SCOOTER_DEBUG_PRINT(TEXT(""), EDebugLevel::Info, TEXT(""));
    if (FJsonSerializer::Serialize(JSONObject.ToSharedRef(), Writer))
    {
        SCOOTER_DEBUG_PRINT(TEXT(""), EDebugLevel::Info, TEXT("pass"));
        return OutputString;
    }

    SCOOTER_DEBUG_PRINT(TEXT(""), EDebugLevel::Info, TEXT("fail"));
    return JSONString;
}

// ========== JSON Parsing Functions ==========

bool UJSONBlueprintLibrary::IsValidJSON(const FString &JSONString)
{
    TSharedPtr<FJsonObject> JSONObject = ::ParseJSONString(JSONString);
    return JSONObject.IsValid();
}

bool UJSONBlueprintLibrary::HasField(const FString &JSONString, const FString &FieldName)
{
    TSharedPtr<FJsonObject> JSONObject = ::ParseJSONString(JSONString);

    if (!JSONObject.IsValid())
    {
        return false;
    }

    return JSONObject->HasField(FieldName);
}

bool UJSONBlueprintLibrary::IsFieldNull(const FString &JSONString, const FString &FieldName)
{
    TSharedPtr<FJsonObject> JSONObject = ::ParseJSONString(JSONString);

    if (!JSONObject.IsValid())
    {
        return false;
    }

    if (!JSONObject->HasField(FieldName))
    {
        return false;
    }

    const TSharedPtr<FJsonValue> *FieldValue = JSONObject->Values.Find(FieldName);
    if (FieldValue && FieldValue->IsValid())
    {
        return (*FieldValue)->IsNull();
    }

    return false;
}

bool UJSONBlueprintLibrary::GetStringField(const FString &JSONString, const FString &FieldName, FString &OutValue)
{
    TSharedPtr<FJsonObject> JSONObject = ::ParseJSONString(JSONString);

    if (!JSONObject.IsValid())
    {
        return false;
    }

    if (JSONObject->HasField(FieldName))
    {
        OutValue = JSONObject->GetStringField(FieldName);
        return true;
    }

    return false;
}

bool UJSONBlueprintLibrary::GetNumberField(const FString &JSONString, const FString &FieldName, float &OutValue)
{
    TSharedPtr<FJsonObject> JSONObject = ::ParseJSONString(JSONString);

    if (!JSONObject.IsValid())
    {
        return false;
    }

    if (JSONObject->HasField(FieldName))
    {
        OutValue = JSONObject->GetNumberField(FieldName);
        return true;
    }

    return false;
}

bool UJSONBlueprintLibrary::GetBooleanField(const FString &JSONString, const FString &FieldName, bool &OutValue)
{
    TSharedPtr<FJsonObject> JSONObject = ::ParseJSONString(JSONString);

    if (!JSONObject.IsValid())
    {
        return false;
    }

    if (JSONObject->HasField(FieldName))
    {
        OutValue = JSONObject->GetBoolField(FieldName);
        return true;
    }

    return false;
}

bool UJSONBlueprintLibrary::GetArrayField(EJSONArrayType ArrayType, const FString &JSONString, const FString &FieldName, TArray<FString> &OutValues)
{
    TSharedPtr<FJsonObject> JSONObject = ::ParseJSONString(JSONString);

    if (!JSONObject.IsValid())
    {
        return false;
    }

    if (JSONObject->HasField(FieldName))
    {
        const TArray<TSharedPtr<FJsonValue>> *JSONArray;
        if (JSONObject->TryGetArrayField(FieldName, JSONArray))
        {
            OutValues.Empty();

            switch (ArrayType)
            {
            case EJSONArrayType::String:
                for (const TSharedPtr<FJsonValue> &Value : *JSONArray)
                {
                    OutValues.Add(Value->AsString());
                }
                break;

            case EJSONArrayType::Number:
                for (const TSharedPtr<FJsonValue> &Value : *JSONArray)
                {
                    OutValues.Add(FString::SanitizeFloat(Value->AsNumber()));
                }
                break;

            case EJSONArrayType::Object:
                for (const TSharedPtr<FJsonValue> &Value : *JSONArray)
                {
                    const TSharedPtr<FJsonObject> *ObjectValue;
                    if (Value->TryGetObject(ObjectValue))
                    {
                        OutValues.Add(::JSONObjectToString(*ObjectValue));
                    }
                }
                break;
            }

            return true;
        }
    }

    return false;
}

bool UJSONBlueprintLibrary::GetObjectField(const FString &JSONString, const FString &FieldName, FString &OutJSON)
{
    TSharedPtr<FJsonObject> JSONObject = ::ParseJSONString(JSONString);

    if (!JSONObject.IsValid())
    {
        return false;
    }

    if (JSONObject->HasField(FieldName))
    {
        const TSharedPtr<FJsonObject> *NestedObject;
        if (JSONObject->TryGetObjectField(FieldName, NestedObject))
        {
            OutJSON = ::JSONObjectToString(*NestedObject);
            return true;
        }
    }

    return false;
}

bool UJSONBlueprintLibrary::GetAllFieldNames(const FString &JSONString, TArray<FString> &OutFieldNames)
{
    TSharedPtr<FJsonObject> JSONObject = ::ParseJSONString(JSONString);

    if (!JSONObject.IsValid())
    {
        return false;
    }

    OutFieldNames.Empty();
    for (const auto &Entry : JSONObject->Values)
    {
        OutFieldNames.Add(Entry.Key);
    }

    return true;
}

FString UJSONBlueprintLibrary::MinifyJSON(const FString &JSONString)
{
    TSharedPtr<FJsonObject> JSONObject = ::ParseJSONString(JSONString);

    if (!JSONObject.IsValid())
    {
        return JSONString;
    }

    // Use default compact writer (no pretty print policy)
    FString OutputString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);

    if (FJsonSerializer::Serialize(JSONObject.ToSharedRef(), Writer))
    {
        return OutputString;
    }

    return JSONString;
}