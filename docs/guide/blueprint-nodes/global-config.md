# Global Config Nodes

Read and write values in project config or the current user's Unreal Editor settings.

**Category:** **Scooter Utilities** > **Global Config**

Choose a scope on each node. **User Global** is the default and shares values across projects for the current Unreal Engine installation and user. **Project** stores values with the current project. These nodes are intended for editor use; packaged builds do not provide a writable `DefaultEditor.ini` or an editor settings file.

## Node Reference

| Node | Inputs | Outputs | Description |
| ---- | ------ | ------- | ----------- |
| **Get Global Config File String** | Section, Key, Scope | Value, Section, Key, Scope, Result, Reason | Reads a string value. |
| **Get Global Config File Float** | Section, Key, Scope | Value, Section, Key, Scope, Result, Reason | Reads a decimal value. |
| **Get Global Config File Int** | Section, Key, Scope | Value, Section, Key, Scope, Result, Reason | Reads a whole number. |
| **Get Global Config File Bool** | Section, Key, Scope | Value, Section, Key, Scope, Result, Reason | Reads a true/false value. |
| **Set Global Config File String** | Section, Key, Value, Scope | Result, Section, Key, Value, Scope, Reason | Writes and verifies a string value. |
| **Set Global Config File Float** | Section, Key, Value, Scope | Result, Section, Key, Value, Scope, Reason | Writes and verifies a decimal value. |
| **Set Global Config File Int** | Section, Key, Value, Scope | Result, Section, Key, Value, Scope, Reason | Writes and verifies a whole number. |
| **Set Global Config File Bool** | Section, Key, Value, Scope | Result, Section, Key, Value, Scope, Reason | Writes and verifies a true/false value. |

The Set nodes pass through their input values so they can be wired into later nodes. Their **Result** is **Success** only after the value is found in the saved file. **Reason** explains a failure.

The Get nodes return the type's default value when a key is missing (**empty**, **0**, or **false**); check **Result** to distinguish a missing key from a value set to that default.

## Scope

| Scope | Reads from | Writes to | Persistence |
| ----- | ---------- | --------- | ----------- |
| **User Global** | The current user's `EditorSettings.ini` | The current user's `EditorSettings.ini` | Shared by projects using the same Unreal Engine installation and user. Available when the editor settings config is initialized; unavailable in packaged builds. |
| **Project** | The current project's merged `Editor` config | The current project's `Config/DefaultEditor.ini` | Shared with the project and normally checked into source control. The file must be writable. |

The Get and Set nodes use the same scope to find values. **Project** reads the merged Editor config, which includes project defaults and saved overrides. **User Global** reads only `EditorSettings.ini`; it is not a fallback layer in the project's Editor config.

## Result Values

| Result | Meaning |
| ------ | ------- |
| **Success** | A Get found the key, or a Set verified the value in the saved file. |
| **Key Not Found** | A Get could not find the key in the selected scope. |
| **Invalid Input** | The section or key is blank, or the scope value is invalid. |
| **Config Unavailable** | Unreal has not initialized the selected config. User Global is unavailable outside an initialized editor session. |
| **Save Failed** | Unreal could not flush the config, or the written value was not present in the saved file afterward. |

## Example

To persist an editor preference across projects:

1. Call **Set Global Config File Bool** with **Section** `/Script/MyGame.MySettings`, **Key** `bShowIntro`, **Value** `false`, and **Scope** **User Global**.
2. Check that **Result** is **Success** before continuing. Use **Reason** to diagnose a failure.
3. Call **Get Global Config File Bool** with the same section, key, and scope to read the stored value.

## Tips

* Section strings must match the section name exactly, for example `/Script/Engine.Engine`.
* Use **Project** for settings that should travel with a project and **User Global** for preferences shared across projects.
* Changes to engine config can affect editor and game behavior. Use the scope intentionally.
