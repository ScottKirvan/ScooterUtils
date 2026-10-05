# File IO C++ Reference

Load, save, and append text files from C++ with `UFileIO`.

**Header:** `FileIO.h` · **Class:** `UFileIO`

Each function takes an `EFileLocation` that picks the base directory, and a file name relative to it. For more on how the files are written, see the [File IO nodes](../blueprint-nodes/file-io).

| Name | Description |
| ---- | ----------- |
| [`LoadFileToString`](#loadfiletostring) | Reads a text file into an `FString`. |
| [`SaveTextToFile`](#savetexttofile) | Writes text to a file, replacing any existing contents. |
| [`AppendTextToFile`](#appendtexttofile) | Adds text to the end of a file, creating it if needed. |
| [`EFileLocation`](#efilelocation) | The base directory for the file. |

## EFileLocation

```cpp
enum class EFileLocation : uint8 { ProjectSaved, UserDocuments, ProjectContent };
```

| Value | Base directory |
| ----- | -------------- |
| `EFileLocation::ProjectSaved` | `FPaths::ProjectSavedDir()`, your project's `Saved` folder. |
| `EFileLocation::UserDocuments` | `FPlatformProcess::UserDir()`, the user's Documents folder. On Android, this is `/storage/emulated/0/Documents/`. |
| `EFileLocation::ProjectContent` | `FPaths::ProjectContentDir()`, your project's `Content` folder. |

The full path is the base directory combined with the file name using `FPaths::Combine`, so the file name can include subfolders, like `Logs/DebugDump.txt`.

## LoadFileToString

```cpp
static bool UFileIO::LoadFileToString(EFileLocation LoadLocation, FString FileName, FString& OutString, FString& OutFilePath);
```

Reads a text file and returns its contents.

| Name | Description |
| ---- | ----------- |
| `LoadLocation` | The base directory to load from. |
| `FileName` | The file to read, including its extension. Taken by value. |
| `OutString` | Receives the contents of the file. |
| `OutFilePath` | Receives the full path the function tried to read, whether or not it succeeded. |

**Returns:** `true` if the file was read successfully.

```cpp
#include "FileIO.h"

FString Contents;
FString FilePath;
if (UFileIO::LoadFileToString(EFileLocation::ProjectSaved, TEXT("Config/Settings.txt"), Contents, FilePath))
{
    // Use Contents
}
```

## SaveTextToFile

```cpp
static bool UFileIO::SaveTextToFile(EFileLocation SaveLocation, const FString& FileName, const FString& Content, FString& OutFullPath);
```

Writes text to a file, replacing any existing contents.

| Name | Description |
| ---- | ----------- |
| `SaveLocation` | The base directory to save to. |
| `FileName` | The file to write, including its extension. |
| `Content` | The text to write. |
| `OutFullPath` | Receives the full path the file was written to. |

**Returns:** `true` if the file was saved successfully.

```cpp
FString SavedPath;
UFileIO::SaveTextToFile(EFileLocation::ProjectSaved, TEXT("Logs/DebugDump.txt"), DumpText, SavedPath);
```

`SavedPath` receives the full path, and the Output Log shows:

```
LogTemp: Successfully saved file to: D:/MyGame/Saved/Logs/DebugDump.txt
```

> [!WARNING]
> `SaveTextToFile` overwrites existing files without asking. Use `AppendTextToFile` to keep existing content.

## AppendTextToFile

```cpp
static bool UFileIO::AppendTextToFile(EFileLocation SaveLocation, const FString& FileName, const FString& Content, FString& OutFullPath, const bool bAddLineBreak = true);
```

Adds text to the end of a file, creating the file if it doesn't exist.

| Name | Description |
| ---- | ----------- |
| `SaveLocation` | The base directory to save to. |
| `FileName` | The file to append to, including its extension. |
| `Content` | The text to append. |
| `OutFullPath` | Receives the full path the file was written to. |
| `bAddLineBreak` | When `true` (the default), adds a line feed (`\n`) after `Content`. |

**Returns:** `true` if the text was written successfully.

```cpp
FString EventsPath;
UFileIO::AppendTextToFile(EFileLocation::ProjectSaved, TEXT("Logs/Events.txt"), TEXT("Level loaded"), EventsPath);
```

> [!NOTE]
> Every `UFileIO` function writes a success or failure message, including the full path, to the **Output Log** under `LogTemp`.
