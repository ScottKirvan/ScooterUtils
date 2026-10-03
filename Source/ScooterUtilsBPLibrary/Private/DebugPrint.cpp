// DebugPrint.cpp
#include "DebugPrint.h"

DEFINE_LOG_CATEGORY(LogDebugPrint);

// Example usage in your plugin/game code:
/*

// In your module or actor:
void UMyActor::SomeFunction()
{
    FString LogFile = TEXT("MyPlugin.log");

    DebugPrint(LogFile, EDebugLevel::Info, TEXT("System initialized"));

    int32 Health = 100;
    DebugPrint(LogFile, EDebugLevel::Warning, TEXT("Low health: %d"), Health);

    FString FileName = TEXT("data.uasset");
    DebugPrint(LogFile, EDebugLevel::Error, TEXT("Failed to load: %s"), *FileName);

    // Skip file logging (empty string)
    DebugPrint(TEXT(""), EDebugLevel::Info, TEXT("Only to UE Output Log"));
}

Output in UE Output Log:
SULogDebugPrint: [2025.283.143052] MyActor.cpp:45: INFO: System initialized
SULogDebugPrint: Warning: [2025.283.143053] MyActor.cpp:48: WARNING: Low health: 100
SULogDebugPrint: Error: [2025.283.143054] MyActor.cpp:51: ERROR: Failed to load: data.uasset

*/

// DEFINE_LOG_CATEGORY(SULogDebugPrint);

bool USUDebugPrint::LogMessage(const FString &LogFile, EDebugLevel Level, const FString &Content, const FString &Context)
{
    const FString Timestamp = GetFormattedTimestamp();
    const FString LevelStr = GetLevelString(Level);

    // Create the full log message with stardate timestamp and context
    FString FullMessage = FString::Printf(TEXT("[%s] %s%s%s: %s"),
                                          *Timestamp,
                                          *Context,
                                          Context.IsEmpty() ? TEXT("") : TEXT(": "),
                                          *LevelStr,
                                          *Content);

    // Critical maps to Error rather than Fatal: a Fatal log terminates the process.
    switch (Level)
    {
    case EDebugLevel::Warning:
        UE_LOG(LogDebugPrint, Warning, TEXT("%s"), *FullMessage);
        break;
    case EDebugLevel::Error:
    case EDebugLevel::Critical:
        UE_LOG(LogDebugPrint, Error, TEXT("%s"), *FullMessage);
        break;
    default:
        UE_LOG(LogDebugPrint, Log, TEXT("%s"), *FullMessage);
        break;
    }

    // Append to log file if specified
    if (!LogFile.IsEmpty())
    {
        const FString OutputPath = FPaths::ProjectLogDir() / LogFile;
        const FString FileMessage = FullMessage + LINE_TERMINATOR;

        return FFileHelper::SaveStringToFile(
            FileMessage,
            *OutputPath,
            FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM,
            &IFileManager::Get(),
            FILEWRITE_Append);
    }

    return true;
}

FString USUDebugPrint::GetLevelString(EDebugLevel Level)
{
    switch (Level)
    {
    case EDebugLevel::Info:
        return TEXT("INFO");
    case EDebugLevel::Warning:
        return TEXT("WARNING");
    case EDebugLevel::Error:
        return TEXT("ERROR");
    case EDebugLevel::Critical:
        return TEXT("CRITICAL");
    default:
        return TEXT("UNKNOWN");
    }
}

FString USUDebugPrint::GetFormattedTimestamp()
{
    const FDateTime Now = FDateTime::Now();
    return FString::Printf(TEXT("%04d.%03d.%02d%02d%02d"),
                           Now.GetYear(),
                           Now.GetDayOfYear(),
                           Now.GetHour(),
                           Now.GetMinute(),
                           Now.GetSecond());
}