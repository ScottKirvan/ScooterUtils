# Scooter Utilities Menus and Toolbar

The menu items and toolbar button Scooter Utilities adds to the Unreal Editor.

Scooter Utilities adds two items to the **File** menu and a dropdown button to the Level Editor's Play toolbar.

> [!NOTE]
> Make sure you've [enabled the plugin](./installing#enabling-the-plugin) via **Edit** > **Plugins** before looking for these menu items.

## Menu and Toolbar Reference

| Name | Location | Description |
| ---- | -------- | ----------- |
| **Restart Editor...** | **File** menu, toolbar dropdown | Shuts down and restarts the editor, re-opening the current project. |
| **Show Project in Explorer** | **File** menu, toolbar dropdown | Opens your project folder (where the `.uproject` file lives) in your system's file browser. |
| **Plugin Settings...** | Toolbar dropdown | Opens the Scooter Utilities page in **Editor Preferences**. |

## Toolbar Dropdown

The **Scooter Utils** dropdown button appears in the Level Editor's Play toolbar. It groups the plugin's actions in one place:

* **Actions**
  * **Restart Editor...**
  * **Show Project in Explorer**
* **Settings**
  * **Plugin Settings...**

The toolbar button is shown by default. To hide it, go to **Edit** > **Editor Preferences** > **Plugins** > **Scooter Utilities** and disable **Show Toolbar Button** in the **UI** section.

> [!NOTE]
> Changes to **Show Toolbar Button** take effect after you restart the editor.

## Restart Editor

**File** > **Restart Editor...** shuts down and restarts Unreal Engine, prompting you to save any unsaved changes before reloading your project. This is the same behavior you see when enabling or disabling a plugin.

**Hotkey:** **Ctrl + Shift + Alt + R**. You can change or disable the hotkey in the [Editor Preferences](./editor-preferences#hotkeys).

Restarting is handy when you're frequently testing code changes, clearing the undo stack, or refreshing the editor. It's also great when the editor starts feeling sluggish: hit **Restart Editor...** and you're back in action without going through the launcher or hunting for your `.uproject` file.

## Show Project in Explorer

**File** > **Show Project in Explorer** opens your system's file browser (File Explorer on Windows, Finder on macOS) focused on your main project folder, the one that contains your `.uproject` file.

This is handy when you've opened a project from the Epic Games Launcher and need to know where it actually lives on disk. While you can **Right-click** assets in the **Content Browser** to open the content folder, this menu item takes you directly to the project root.
