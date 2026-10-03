# Blueprint Reflection Nodes

Find out which Blueprint called a node, and where that Blueprint lives in your project.

**Category:** **Scooter Utilities** > **Blueprint Reflection**

These nodes identify the Blueprint that called them, which is handy for logging and debugging tools. Each node reads the object connected to its **World Context Object** pin. In most Blueprints, that pin is hidden and filled in automatically with **Self**, so the node simply describes the Blueprint it's placed in.

## Node Reference

| Node | Outputs | Description |
| ---- | ------- | ----------- |
| **Get Calling Blueprint Name** | String | The calling Blueprint's class name. Works in editor and packaged builds. |
| **Get Calling Blueprint Path** | String | The calling Blueprint's package path. Most useful in the editor. |
| **Get Calling Blueprint Info** | Blueprint Name, Content Path, Full Path, Full Reference Path | Detailed name and path information. Most useful in the editor. |

## Get Calling Blueprint Name

Returns the class name of the calling object. For a Blueprint, this is the generated class name, which ends in `_C`. For example, calling it from `BP_PlayerCharacter` returns `BP_PlayerCharacter_C`.

Returns `Unknown` if there's no valid World Context Object.

## Get Calling Blueprint Path

Returns the package path of the calling Blueprint, for example `/Game/MyGame/BP_Player`.

In packaged builds, where Blueprint assets aren't available, it returns the class path instead, for example `/Game/MyGame/BP_Player.BP_Player_C`.

## Get Calling Blueprint Info

Returns detailed information about the calling Blueprint. For a Blueprint at `Content/MyGame/Characters/BP_Player`, the outputs in the editor are:

| Output | Example | Description |
| ------ | ------- | ----------- |
| **Out Blueprint Name** | `BP_Player` | The Blueprint asset's name. |
| **Out Content Path** | `Content/MyGame/Characters/BP_Player` | The package path with `/Game/` replaced by `Content/`. |
| **Out Full Path** | `/Game/MyGame/Characters/BP_Player` | The full package path. |
| **Out Full Reference Path** | `/Game/MyGame/Characters/BP_Player.BP_Player` | The Blueprint asset's object path. |

In packaged builds, **Out Blueprint Name** is the class name (ending in `_C`), **Out Full Reference Path** is the class path, and the other two outputs are empty.

> [!NOTE]
> The editor-only details come from the Blueprint asset, which isn't included in packaged games. Use **Get Calling Blueprint Name** when you need the same result everywhere.
