# File IO Nodes

Load, save, and append text files from Blueprints.

**Category:** **Scooter Utilities** > **File IO**

The File IO nodes are simple text file helpers. Every node takes a location that picks the base directory, and a file name relative to that directory.

## File Locations

| Location | Directory |
| -------- | --------- |
| **Project Saved Directory** | Your project's `Saved` folder. |
| **User Documents Folder** | The user's Documents folder. On Android, this is `/storage/emulated/0/Documents/`. |
| **Project Content Directory** | Your project's `Content` folder. |

The **File Name** can include subfolders, for example `Logs/DebugDump.txt`.

## Load File To String

Reads a text file and returns its contents.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **Load Location** | Input | The base directory to load from. |
| **File Name** | Input | The file to read, including its extension. Example: `Config/Settings.txt`. |
| **Out String** | Output | The contents of the file. |
| **Out File Path** | Output | The full path the node tried to read. |
| **Return Value** | Output | **true** if the file was read successfully. |

## Save Text To File

Writes text to a file, replacing any existing contents.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **Save Location** | Input | The base directory to save to. |
| **File Name** | Input | The file to write, including its extension. |
| **Content** | Input | The text to write. |
| **Out Full Path** | Output | The full path the file was written to. |
| **Return Value** | Output | **true** if the file was saved successfully. |

> [!WARNING]
> **Save Text To File** overwrites existing files without asking. Use **Append Text To File** to keep existing content.

## Append Text To File

Adds text to the end of a file, creating the file if it doesn't exist.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **Save Location** | Input | The base directory to save to. |
| **File Name** | Input | The file to append to, including its extension. |
| **Content** | Input | The text to append. |
| **Add Line Break** | Input | When enabled (the default), adds a line break after **Content**. |
| **Out Full Path** | Output | The full path the file was written to. |
| **Return Value** | Output | **true** if the text was written successfully. |

The save and append nodes write UTF-8 text without a byte-order mark and create any missing parent folders. Every node writes a success or failure message, including the full path, to the **Output Log**.

## Examples

* **Load a file:** Call **Load File To String** with **Load Location** set to **Project Saved Directory** and **File Name** set to `Config/Settings.txt` to read from your project's `Saved` folder.
* **Save a debug dump:** Call **Save Text To File** with **Save Location** set to **Project Saved Directory**, **File Name** set to `Logs/DebugDump.txt`, and your text as **Content**. **Out Full Path** tells you exactly where it went.
* **Save to the user's Documents:** Set **Save Location** to **User Documents Folder** to write files that live outside your project.

> [!TIP]
> Pair these nodes with the [JSON nodes](./json/) to save and load structured data, like settings or save games.
