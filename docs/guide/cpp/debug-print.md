# Debug Print C++ Reference

Write timestamped debug messages from C++ with `SCOOTER_DEBUG_PRINT`, `DebugPrint`, and `LogMessage`.

**Header:** `DebugPrint.h` · **Class:** `USUDebugPrint`

All three entry points produce the same message format and can append to a log file in your project's `Saved/Logs` folder. For the message format and an example of the output, see the [Debug Print node](../blueprint-nodes/debug-print).

| Name | Description |
| ---- | ----------- |
| [`SCOOTER_DEBUG_PRINT`](#scooter-debug-print) | printf-style macro that fills in the source file and line number as the context. |
| [`USUDebugPrint::DebugPrint`](#debugprint) | printf-style function with no context. |
| [`USUDebugPrint::LogMessage`](#logmessage) | `FString` version with an optional context. Also the Blueprint node. |
| [`EDebugLevel`](#edebuglevel) | The severity: sets the label in the message and the **Output Log** verbosity. |

## EDebugLevel

```cpp
enum class EDebugLevel : uint8 { Info, Warning, Error, Critical };
```

| Value | Label in the message | Output Log verbosity |
| ----- | -------------------- | -------------------- |
| `EDebugLevel::Info` | `INFO` | `Log` |
| `EDebugLevel::Warning` | `WARNING` | `Warning` |
| `EDebugLevel::Error` | `ERROR` | `Error` |
| `EDebugLevel::Critical` | `CRITICAL` | `Error` (never `Fatal`, so it doesn't stop the process) |

## SCOOTER_DEBUG_PRINT

```cpp
SCOOTER_DEBUG_PRINT(LogFile, Level, Format, ...)
```

Formats a printf-style message and logs it, using `<file>:<line>` of the call site as the context. The file part is the compiler's `__FILE__` value, which may be a full path depending on your compiler and build settings.

| Name | Description |
| ---- | ----------- |
| `LogFile` | `const TCHAR*`. The log file to append to, relative to `Saved/Logs`. Pass `TEXT("")` to write only to the **Output Log**. |
| `Level` | `EDebugLevel`. The severity. See [`EDebugLevel`](#edebuglevel). |
| `Format` | `const TCHAR*`. A printf-style format string, such as `TEXT("Health: %d")`. |
| `...` | The values for `Format`. |

**Returns:** `bool`, the same as [`LogMessage`](#logmessage).

```cpp
#include "DebugPrint.h"

void AMyCharacter::TakeHit(int32 Damage)
{
    Health -= Damage;
    SCOOTER_DEBUG_PRINT(TEXT("Combat.log"), EDebugLevel::Warning, TEXT("%s took %d damage, %d left"), *GetName(), Damage, Health);
}
```

## DebugPrint

```cpp
static bool USUDebugPrint::DebugPrint(const TCHAR* LogFile, EDebugLevel Level, const TCHAR* Format, ...);
```

Formats a printf-style message and logs it with no context. Takes the same parameters as [`SCOOTER_DEBUG_PRINT`](#scooter-debug-print).

**Returns:** `bool`, the same as [`LogMessage`](#logmessage).

```cpp
USUDebugPrint::DebugPrint(TEXT(""), EDebugLevel::Info, TEXT("Loaded %d items"), Items.Num());
```

## LogMessage

```cpp
static bool USUDebugPrint::LogMessage(const FString& LogFile, EDebugLevel Level, const FString& Content, const FString& Context = TEXT(""));
```

Logs a message that's already been built. This is the function behind the **Log Message** Blueprint node, and the one the other two call after formatting.

| Name | Description |
| ---- | ----------- |
| `LogFile` | The log file to append to, relative to `Saved/Logs`. Example: `MyGame.log` or `Debug/Testing.log`. Pass an empty string to write only to the **Output Log**. |
| `Level` | The severity. See [`EDebugLevel`](#edebuglevel). |
| `Content` | The message text. It isn't treated as a format string. |
| `Context` | Optional text that says where the message came from. When empty, it's left out along with its colon. |

**Returns:** `true` if the message was logged. When `LogFile` is set, `false` means the file couldn't be written.

```cpp
USUDebugPrint::LogMessage(TEXT("Multiplayer.log"), EDebugLevel::Info, TEXT("Player joined: ") + PlayerName, TEXT("Multiplayer"));
```

## Formatting Tips

* Pass `FString` values to the printf-style versions with `*`, like `*GetName()`. Passing an `FString` directly to `...` is undefined behavior.
* The printf-style versions also take `LogFile` as a `const TCHAR*`, so use `TEXT("MyGame.log")` or `*MyLogFileString`.
* To log text that might contain a `%`, use `TEXT("%s"), *Text` rather than passing the text as `Format`, or call [`LogMessage`](#logmessage).
* The printf-style versions handle messages of any practical length. Messages over about a million characters are truncated.

> [!NOTE]
> `SCOOTER_DEBUG_PRINT` expands to a call to `USUDebugPrint::DebugPrintInternal`, which is public only so the macro can reach it. Use the macro instead of calling it directly.
