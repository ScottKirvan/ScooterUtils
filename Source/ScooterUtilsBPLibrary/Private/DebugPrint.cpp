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
    // Get current time and format stardate style timestamp
    FDateTime Now = FDateTime::Now();
    const FString Timestamp = FString::Printf(TEXT("%04d.%03d.%02d%02d%02d"),
                                              Now.GetYear(),
                                              Now.GetDayOfYear(),
                                              Now.GetHour(),
                                              Now.GetMinute(),
                                              Now.GetSecond());

    const FString LevelStr = GetLevelString(Level);
    const ELogVerbosity::Type Verbosity = GetVerbosityForLevel(Level);

    // Create the full log message with stardate timestamp and context
    FString FullMessage = FString::Printf(TEXT("[%s] %s%s%s: %s"),
                                          *Timestamp,
                                          *Context,
                                          Context.IsEmpty() ? TEXT("") : TEXT(": "),
                                          *LevelStr,
                                          *Content);

    // Output to UE log
    UE_LOG(LogDebugPrint, Log, TEXT("%s"), *FullMessage);

    // Append to log file if specified
    if (!LogFile.IsEmpty())
    {
        const FString OutputPath = FPaths::ProjectLogDir() / LogFile;
        const FString FileMessage = FullMessage + LINE_TERMINATOR;

        return FFileHelper::SaveStringToFile(
            FileMessage,
            *OutputPath,
            FFileHelper::EEncodingOptions::AutoDetect,
            &IFileManager::Get(),
            FILEWRITE_Append);
    }

    return true;
}

ELogVerbosity::Type USUDebugPrint::GetVerbosityForLevel(EDebugLevel Level)
{
    switch (Level)
    {
    case EDebugLevel::Info:
        return ELogVerbosity::Log;
    case EDebugLevel::Warning:
        return ELogVerbosity::Warning;
    case EDebugLevel::Error:
        return ELogVerbosity::Error;
    case EDebugLevel::Critical:
        return ELogVerbosity::Fatal;
    default:
        return ELogVerbosity::Log;
    }
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