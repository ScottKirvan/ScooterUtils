// DebugPrint.h
#pragma once

#include "CoreMinimal.h"
#include "Misc/DateTime.h"
#include "HAL/PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

DECLARE_LOG_CATEGORY_EXTERN(LogDebugPrint, Log, All);

enum class EDebugLevel : uint8
{
    Info,
    Warning,
    Error,
    Critical
};

// Macro to automatically capture file and line
#define DebugPrint(LogFile, Level, Format, ...) \
    DebugPrintImpl(LogFile, Level, __FILE__, __LINE__, Format, ##__VA_ARGS__)

// Implementation function
inline void DebugPrintImpl(const FString &LogFile, EDebugLevel Level,
                           const char *File, int32 Line, const TCHAR *Format, ...)
{
    // Get timestamp in stardate style (YYYY.DDD.HHMMSS)
    FDateTime Now = FDateTime::Now();
    int32 DayOfYear = Now.GetDayOfYear();
    FString Timestamp = FString::Printf(TEXT("%04d.%03d.%02d%02d%02d"),
                                        Now.GetYear(),
                                        DayOfYear,
                                        Now.GetHour(),
                                        Now.GetMinute(),
                                        Now.GetSecond());

    // Get filename only (not full path)
    FString FileName = FPaths::GetCleanFilename(ANSI_TO_TCHAR(File));

    // Get level string
    FString LevelStr;
    ELogVerbosity::Type Verbosity;
    switch (Level)
    {
    case EDebugLevel::Info:
        LevelStr = TEXT("INFO");
        Verbosity = ELogVerbosity::Log;
        break;
    case EDebugLevel::Warning:
        LevelStr = TEXT("WARNING");
        Verbosity = ELogVerbosity::Warning;
        break;
    case EDebugLevel::Error:
        LevelStr = TEXT("ERROR");
        Verbosity = ELogVerbosity::Error;
        break;
    case EDebugLevel::Critical:
        LevelStr = TEXT("CRITICAL");
        Verbosity = ELogVerbosity::Fatal;
        break;
    default:
        LevelStr = TEXT("UNKNOWN");
        Verbosity = ELogVerbosity::Log;
        break;
    }

    // Format the user message
    TCHAR Message[2048];
    va_list Args;
    va_start(Args, Format);
    FCString::GetVarArgs(Message, UE_ARRAY_COUNT(Message), Format, Args);
    va_end(Args);

    // Create the full log message (compiler-style format)
    FString FullMessage = FString::Printf(TEXT("[%s] %s:%d: %s: %s"),
                                          *Timestamp,
                                          *FileName,
                                          Line,
                                          *LevelStr,
                                          Message);

    // Output to UE log (stdout equivalent)
#if WITH_EDITOR
    FMsg::Logf(__FILE__, __LINE__, LogDebugPrint.GetCategoryName(), Verbosity, TEXT("%s"), *FullMessage);
#endif // WITH_EDITOR

    // Append to log file if specified
    if (!LogFile.IsEmpty())
    {
        FString MyLogPath = FPaths::ProjectLogDir() / LogFile;

        // Append newline to message
        FString FileMessage = FullMessage + TEXT("\n");

        // Append to file (thread-safe)
        FFileHelper::SaveStringToFile(FileMessage, *MyLogPath,
                                      FFileHelper::EEncodingOptions::AutoDetect,
                                      &IFileManager::Get(),
                                      FILEWRITE_Append);
    }
}
