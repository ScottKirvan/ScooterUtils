// DebugPrint.h
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Misc/DateTime.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "ScooterUtilsBPLibrary.h"
#include "DebugPrint.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogDebugPrint, Log, All);

UENUM(BlueprintType)
enum class EDebugLevel : uint8
{
    Info UMETA(DisplayName = "Info"),
    Warning UMETA(DisplayName = "Warning"),
    Error UMETA(DisplayName = "Error"),
    Critical UMETA(DisplayName = "Critical")
};

UCLASS()
class USUDebugPrint : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /**
     * Writes a debug message to both the Output Log window and optionally to a file
     *
     * @param LogFile    Name of the log file to write to. Leave empty ("") to only write to Output Log.
     *                   File will be created in your Project's Saved/Logs directory.
     *                   Example: "MyGame.log" or "Debug/Testing.log"
     *
     * @param Level      Severity level of the message. Use:
     *                   - Info: General information and status updates
     *                   - Warning: Non-critical issues that should be reviewed
     *                   - Error: Problems that need immediate attention
     *                   - Critical: Severe issues that might crash the game
     *
     * @param Content    The actual message to log. Can be any text or value converted to string.
     *                   Examples: "Player spawned", "Health is low: 25", "Loading complete"
     *
     * @param Context    Optional. Add extra information about where the message came from.
     *                   Examples: "PlayerController", "SaveGame", "Level1_Blueprint"
     *
     * @return          True if the message was logged successfully (and written to file if specified)
     *                  False if there was an error writing to the log file
     *
     * Example: "LogMessage("Game.log", Info, "Player joined: " + PlayerName, "Multiplayer")"
     * Output:  "[2025.283.143052] Multiplayer: INFO: Player joined: Steve"
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Debug Print",
              meta = (AdvancedDisplay = "Context",
                      ToolTip = "Logs a debug message to the Output Log and optionally to a file with timestamp",
                      Keywords = "debug,log,print,output,file,console,message"))
    static bool LogMessage(const FString &LogFile,
                           EDebugLevel Level,
                           const FString &Content,
                           const FString &Context = TEXT(""));

#define SCOOTER_DEBUG_PRINT(LogFile, Level, Format, ...) \
    USUDebugPrint::DebugPrintInternal(LogFile, Level, TEXT(__FILE__), __LINE__, Format, ##__VA_ARGS__)

    /**
     * Internal implementation with file and line tracking
     */
    static bool FORCEINLINE DebugPrintInternal(const TCHAR *LogFile, EDebugLevel Level, const TCHAR *File, int32 Line, const TCHAR *Format, ...)
    {
        TCHAR TempStr[4096];
        va_list Args;
        va_start(Args, Format);
        FCString::GetVarArgs(TempStr, UE_ARRAY_COUNT(TempStr), Format, Args);
        va_end(Args);
        return LogMessage(LogFile, Level, TempStr, *FString::Printf(TEXT("%s:%d"), File, Line));
    }

    /**
     * C++ friendly varargs version for formatted debug messages (Legacy support)
     */
    static bool FORCEINLINE DebugPrint(const TCHAR *LogFile, EDebugLevel Level, const TCHAR *Format, ...)
    {
        TCHAR TempStr[4096];
        va_list Args;
        va_start(Args, Format);
        FCString::GetVarArgs(TempStr, UE_ARRAY_COUNT(TempStr), Format, Args);
        va_end(Args);
        return LogMessage(LogFile, Level, TempStr, TEXT(""));
    }

private:
    /** Gets the verbosity level based on debug level */
    static ELogVerbosity::Type GetVerbosityForLevel(EDebugLevel Level);

    /** Gets the string representation of the debug level */
    static FString GetLevelString(EDebugLevel Level);

    /** Formats the timestamp in YYYY.DDD.HHMMSS format */
    static FString GetFormattedTimestamp();
};