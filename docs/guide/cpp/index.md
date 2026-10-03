# C++ Reference

Call the Scooter Utilities runtime library from your own C++ code.

Every Scooter Utilities Blueprint node is a static function on a Blueprint function library class in the `ScooterUtilsBPLibraryModule` runtime module. Add the module as a dependency and you can call those same functions from C++, plus a couple of C++-only extras for debug logging.

> [!NOTE]
> C++ access requires a plugin version that includes the fix for [issue #130](https://github.com/ScottKirvan/ScooterUtils/issues/130). Earlier versions don't export most of the library classes, so calls into them can fail to link.

## Setting Up Your Module

1. Make sure the plugin is installed and enabled in your project. See [Installing and Enabling](../installing).

2. In your module's `.Build.cs` file, add `ScooterUtilsBPLibraryModule` to your dependencies:

   ```csharp
   PrivateDependencyModuleNames.AddRange(new string[] { "ScooterUtilsBPLibraryModule" });
   ```

   Use `PublicDependencyModuleNames` instead if your module's public headers include Scooter Utilities headers.

3. If your code lives in another plugin, list Scooter Utilities as a dependency in that plugin's `.uplugin` file:

   ```json
   "Plugins": [
     { "Name": "ScooterUtils", "Enabled": true }
   ]
   ```

4. Include the header for the class you want to call, then call its static functions. You never need to create an instance.

> [!TIP]
> The module name is `ScooterUtilsBPLibraryModule`, not the `ScooterUtilsBPLibrary` folder name under `Source`.

## Headers and Classes

| Header | Class | Description |
| ------ | ----- | ----------- |
| `DebugPrint.h` | `USUDebugPrint` | Timestamped logging to the **Output Log** and log files, plus the `SCOOTER_DEBUG_PRINT` macro. See [Debug Print](./debug-print). |
| `FileIO.h` | `UFileIO` | Load, save, and append text files. See [File IO](./file-io). |
| `ScooterUtilsBPLibrary.h` | `UScooterUtilsBPLibrary` | Read and write engine config values. See [Global Config](./global-config). |
| `BPReflection.h` | `UBPReflection` | Name and path information for an object's Blueprint. See [Blueprint Reflection](./blueprint-reflection). |
| `LoremIpsumGenerator.h` | `ULoremIpsumGenerator` | Placeholder text. See [Lorem Ipsum](./lorem-ipsum). |
| `JSONBlueprintLibrary.h` | `UJSONBlueprintLibrary` | String-based JSON creation and parsing. See [JSON](./json). |

The runtime module is set up for Windows, macOS, Linux, and Android, and works in packaged games as well as in the editor.

## Quick Example

A small actor that logs a message, builds some JSON, and saves it to the project's `Saved` folder:

```cpp
// MyActor.cpp
#include "MyActor.h"
#include "DebugPrint.h"
#include "FileIO.h"
#include "JSONBlueprintLibrary.h"

void AMyActor::BeginPlay()
{
    Super::BeginPlay();

    SCOOTER_DEBUG_PRINT(TEXT("MyGame.log"), EDebugLevel::Info, TEXT("%s started"), *GetName());

    FString Json;
    Json = UJSONBlueprintLibrary::AddField(EJSONFieldType::String, Json, TEXT("actor"), GetName());
    Json = UJSONBlueprintLibrary::AddField(EJSONFieldType::Boolean, Json, TEXT("started"), TEXT("true"));

    FString SavedPath;
    UFileIO::SaveTextToFile(EFileLocation::ProjectSaved, TEXT("ActorState.json"), Json, SavedPath);
}
```

## C++ Reference Pages

<div class="card-grid">
  <a class="card" href="./debug-print.html">
    <strong>Debug Print</strong>
    <span>SCOOTER_DEBUG_PRINT, DebugPrint, LogMessage, and EDebugLevel.</span>
  </a>
  <a class="card" href="./file-io.html">
    <strong>File IO</strong>
    <span>UFileIO functions and EFileLocation.</span>
  </a>
  <a class="card" href="./global-config.html">
    <strong>Global Config</strong>
    <span>Engine config getters and setters.</span>
  </a>
  <a class="card" href="./blueprint-reflection.html">
    <strong>Blueprint Reflection</strong>
    <span>UBPReflection name and path functions.</span>
  </a>
  <a class="card" href="./lorem-ipsum.html">
    <strong>Lorem Ipsum</strong>
    <span>ULoremIpsumGenerator text functions.</span>
  </a>
  <a class="card" href="./json.html">
    <strong>JSON</strong>
    <span>UJSONBlueprintLibrary, EJSONFieldType, and EJSONArrayType.</span>
  </a>
</div>
