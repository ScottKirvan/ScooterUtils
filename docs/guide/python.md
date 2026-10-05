# Python Scripting

Call the Scooter Utilities runtime library from Unreal Editor Python scripts.

Every Scooter Utilities Blueprint node is also available in the editor's Python environment through the `unreal` module. You don't need to set anything up beyond enabling Python.

## Enabling Python

1. In the **Main Menu**, go to **Edit** > **Plugins**.

2. Enable **Python Editor Script Plugin**, then restart the editor.

3. Open the Python console: in the **Output Log**, switch the command box from **Cmd** to **Python**.

> [!NOTE]
> Editor Python runs only in the editor, not in packaged games.

## Name Mapping

Unreal converts the C++ names automatically:

* **Classes** drop their `U` prefix: `UJSONBlueprintLibrary` becomes `unreal.JSONBlueprintLibrary`.
* **Enums** drop their `E` prefix, and their values become upper snake case: `EFileLocation::ProjectSaved` becomes `unreal.FileLocation.PROJECT_SAVED`.
* **Functions and parameters** become snake case: `GetCallingBlueprintName` becomes `get_calling_blueprint_name`.
* **Output pins** come back as a tuple, after the return value if there is one.

| Blueprint category | Python class |
| ------------------ | ------------ |
| [JSON](./blueprint-nodes/json/) | `unreal.JSONBlueprintLibrary` |
| [File IO](./blueprint-nodes/file-io) | `unreal.FileIO` |
| [Global Config](./blueprint-nodes/global-config) | `unreal.ScooterUtilsBPLibrary` |
| [Debug Print](./blueprint-nodes/debug-print) | `unreal.SUDebugPrint` |
| [Blueprint Reflection](./blueprint-nodes/blueprint-reflection) | `unreal.BPReflection` |
| [Lorem Ipsum](./blueprint-nodes/lorem-ipsum) | `unreal.LoremIpsumGenerator` |

For what each function does, see the matching Blueprint node page.

> [!TIP]
> Run `help(unreal.JSONBlueprintLibrary)` in the Python console to list every function and its exact signature.

## Examples

Build some JSON and save it to the project's `Saved` folder:

```python
import unreal

json = unreal.JSONBlueprintLibrary.add_field(unreal.JSONFieldType.STRING, "", "name", "Bob")
json = unreal.JSONBlueprintLibrary.add_field(unreal.JSONFieldType.NUMBER, json, "health", "100")

ok, path = unreal.FileIO.save_text_to_file(unreal.FileLocation.PROJECT_SAVED, "Scripts/player.json", json)
unreal.log(f"Saved: {ok} -> {path}")
```

Read it back and pull out a value:

```python
ok, text, path = unreal.FileIO.load_file_to_string(unreal.FileLocation.PROJECT_SAVED, "Scripts/player.json")
found, name = unreal.JSONBlueprintLibrary.get_string_field(text, "name")
```

Write to a log file from a script:

```python
unreal.SUDebugPrint.log_message("Scripts.log", unreal.DebugLevel.WARNING, "Batch import finished", "ImportScript")
```
