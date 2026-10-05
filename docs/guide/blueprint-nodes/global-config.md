# Global Config Nodes

Read and write values in the engine's global configuration from Blueprints.

**Category:** **Scooter Utilities** > **Global Config**

The Global Config nodes read and write values in the engine's config, the same `Engine` configuration that `DefaultEngine.ini` feeds into. Pass the INI section (for example, `/Script/Engine.GameEngine`) and the key name to read or write.

## Node Reference

| Node | Inputs | Output | Description |
| ---- | ------ | ------ | ----------- |
| **Get Global Config File String** | Section, Key | String | Reads a string value. Returns an empty string if not found. |
| **Get Global Config File Float** | Section, Key | Float | Reads a decimal value. Returns **0.0** if not found. |
| **Get Global Config File Int** | Section, Key | Integer | Reads a whole number value. Returns **0** if not found. |
| **Get Global Config File Bool** | Section, Key | Boolean | Reads a true/false value. Returns **false** if not found. |
| **Set Global Config File String** | Section, Key, Value | | Writes a string value. |
| **Set Global Config File Float** | Section, Key, Value | | Writes a decimal value. |
| **Set Global Config File Int** | Section, Key, Value | | Writes a whole number value. |
| **Set Global Config File Bool** | Section, Key, Value | | Writes a true/false value. |

The **Get** nodes are pure nodes (no execution pins). The **Set** nodes update the value immediately, and a **Get** with the same section and key returns the new value for the rest of the session.

## Where Values Are Read and Written

* **Get** nodes read from the engine's merged config, which combines the engine's base settings, your project's `Config/DefaultEngine.ini`, and any saved user overrides.
* **Set** nodes don't modify `Config/DefaultEngine.ini`.

> [!WARNING]
> In testing on UE 5.8, values written by the **Set** nodes weren't saved to any `.ini` file, so they may not survive an editor restart.

> [!NOTE]
> Because a "not found" key returns a default (empty, 0, or false), you can't tell a missing key from one set to that default value.

## Example

1. Call **Get Global Config File String** with **Section** set to `/Script/Engine.Engine` and **Key** set to `GameViewportClientClassName`.

2. Inspect the returned string, or call **Set Global Config File String** with the same section and key to update it.

## Tips

* Section strings must match exactly as they appear in the INI file, for example `/Script/AndroidRuntimeSettings.AndroidRuntimeSettings`.
* Use the **Set** nodes carefully. Changing engine config values can affect editor and game behavior.
