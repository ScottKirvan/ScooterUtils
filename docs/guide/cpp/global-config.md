# Global Config C++ Reference

Read and write values in project config or the current user's Unreal Editor settings with `UScooterUtilsBPLibrary`.

**Header:** `ScooterUtilsBPLibrary.h` · **Class:** `UScooterUtilsBPLibrary` · **Module:** `ScooterUtilsBPLibraryModule`

For Blueprint-node behavior and scope details, see the [Global Config nodes](../blueprint-nodes/global-config.md).

## Scope

All functions take an `EGlobalConfigScope`:

| Scope | Read source | Write destination |
| ----- | ----------- | ----------------- |
| `EGlobalConfigScope::Project` | The current project's merged Editor config | The current project's `Config/DefaultEditor.ini` (must be writable) |
| `EGlobalConfigScope::UserGlobal` | The current user's `EditorSettings.ini` | The current user's `EditorSettings.ini` |

`UserGlobal` is the default on Blueprint nodes. C++ calls must pass the scope explicitly. User-global config is available when the editor settings file is initialized; Project and user-global config are intended for editor use; packaged builds do not provide a writable `DefaultEditor.ini` or an editor settings file.

## Functions

The class provides `GetGlobalConfigFileString`, `GetGlobalConfigFileFloat`, `GetGlobalConfigFileInt`, and `GetGlobalConfigFileBool`. Each takes the same arguments and returns the requested typed value:

```cpp
static FString GetGlobalConfigFileString(
    const FString& Section,
    const FString& Key,
    EGlobalConfigScope Scope,
    FString& OutSection,
    FString& OutKey,
    EGlobalConfigScope& OutScope,
    EGlobalConfigResult& OutResult,
    FString& OutReason);
```

The `Out...` arguments echo the inputs to support chaining. `OutResult` reports `Success`, `KeyNotFound`, `InvalidInput`, or `ConfigUnavailable`; `OutReason` is empty on success and explains non-success results. Missing keys return the type's default (empty string, `0`, or `false`), so check `OutResult` to distinguish a missing value from one explicitly set to its default.

The class also provides `SetGlobalConfigFileString`, `SetGlobalConfigFileFloat`, `SetGlobalConfigFileInt`, and `SetGlobalConfigFileBool`. Each takes `Section`, `Key`, a typed `Value`, `Scope`, and output references for `OutSection`, `OutKey`, `OutValue`, `OutScope`, and `OutReason`. Setters return an `EGlobalConfigResult`. `Success` means Unreal flushed the config and the value was found again in the saved file. A setter can also return `InvalidInput`, `ConfigUnavailable`, or `SaveFailed`; inspect `OutReason` for details.

## Example

```cpp
#include "ScooterUtilsBPLibrary.h"

FString Section = TEXT("/Script/MyGame.MySettings");
FString Key = TEXT("bShowIntro");
bool Value = false;
EGlobalConfigScope Scope = EGlobalConfigScope::UserGlobal;
FString OutSection;
FString OutKey;
bool OutValue;
EGlobalConfigScope OutScope;
FString Reason;

const EGlobalConfigResult Result = UScooterUtilsBPLibrary::SetGlobalConfigFileBool(
    Section, Key, Value, Scope, OutSection, OutKey, OutValue, OutScope, Reason);
if (Result != EGlobalConfigResult::Success)
{
    UE_LOG(LogTemp, Error, TEXT("Could not save config value: %s"), *Reason);
}
```
