# Global Config C++ Reference

Read and write values in the engine's global configuration from C++ with `UScooterUtilsBPLibrary`.

**Header:** `ScooterUtilsBPLibrary.h` · **Class:** `UScooterUtilsBPLibrary`

These functions read and write the engine's `Engine` config through `GConfig` and `GEngineIni`. For where values are read from and written to, see the [Global Config nodes](../blueprint-nodes/global-config#where-values-are-read-and-written).

## Function Reference

| Name | Returns | Description |
| ---- | ------- | ----------- |
| `GetGlobalConfigFileString(const FString& Section, const FString& Key)` | `FString` | Reads a string value. Returns an empty string if not found. |
| `GetGlobalConfigFileFloat(const FString& Section, const FString& Key)` | `float` | Reads a decimal value. Returns `0.0f` if not found. |
| `GetGlobalConfigFileInt(const FString& Section, const FString& Key)` | `int32` | Reads a whole number value. Returns `0` if not found. |
| `GetGlobalConfigFileBool(const FString& Section, const FString& Key)` | `bool` | Reads a true/false value. Returns `false` if not found. |
| `SetGlobalConfigFileString(const FString& Section, const FString& Key, const FString& Value)` | `void` | Writes a string value, then calls `GConfig->Flush`. See the note below. |
| `SetGlobalConfigFileFloat(const FString& Section, const FString& Key, float Value)` | `void` | Writes a decimal value, then calls `GConfig->Flush`. See the note below. |
| `SetGlobalConfigFileInt(const FString& Section, const FString& Key, int32 Value)` | `void` | Writes a whole number value, then calls `GConfig->Flush`. See the note below. |
| `SetGlobalConfigFileBool(const FString& Section, const FString& Key, bool Value)` | `void` | Writes a true/false value, then calls `GConfig->Flush`. See the note below. |

All of them are `static`. The parameters are the same throughout:

| Name | Description |
| ---- | ----------- |
| `Section` | The INI section, exactly as it appears in the file, like `/Script/Engine.Engine`. |
| `Key` | The key name within the section. |
| `Value` | The value to write (setters only). |

> [!NOTE]
> A missing key returns the type's default (empty, `0`, or `false`), so you can't tell it apart from a key that's set to that value. Call `GConfig` directly if you need to know whether a key exists.

> [!WARNING]
> In testing on UE 5.8, values written by the setters weren't saved to any `.ini` file, despite the `Flush` call, so they may not survive a restart.

## Example

```cpp
#include "ScooterUtilsBPLibrary.h"

const FString ViewportClass = UScooterUtilsBPLibrary::GetGlobalConfigFileString(
    TEXT("/Script/Engine.Engine"), TEXT("GameViewportClientClassName"));

UScooterUtilsBPLibrary::SetGlobalConfigFileBool(
    TEXT("/Script/MyGame.MySettings"), TEXT("bShowIntro"), false);
```

In a default project, `ViewportClass` is `/Script/Engine.GameViewportClient`.
