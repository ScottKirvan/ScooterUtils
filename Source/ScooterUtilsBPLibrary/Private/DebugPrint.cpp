
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
LogDebugPrint: [2025.283.143052] MyActor.cpp:45: INFO: System initialized
LogDebugPrint: Warning: [2025.283.143053] MyActor.cpp:48: WARNING: Low health: 100
LogDebugPrint: Error: [2025.283.143054] MyActor.cpp:51: ERROR: Failed to load: data.uasset

*/