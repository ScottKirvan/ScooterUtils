# Scooter Utilities Menus and Toolbar

The menu items and toolbar button Scooter Utilities adds to the Unreal Editor.

Scooter Utilities adds two items to the **File** menu and a dropdown button to the Level Editor's Play toolbar.

> [!NOTE]
> Make sure you've [enabled the plugin](./installing#enabling-the-plugin) via **Edit** > **Plugins** before looking for these menu items.

## Menu and Toolbar Reference

| Name                         | Location                        | Description                                                                                 |
| ---------------------------- | ------------------------------- | ------------------------------------------------------------------------------------------- |
| **Restart Editor...**        | **File** menu, toolbar dropdown | Shuts down and restarts the editor, re-opening the current project.                         |
| **Show Project in Explorer** | **File** menu, toolbar dropdown | Opens your project folder (where the `.uproject` file lives) in your system's file browser. |
| **Plugin Settings...**       | Toolbar dropdown                | Opens the Scooter Utilities page in **Editor Preferences**.                                 |
| **About ScooterUtils...**    | Toolbar dropdown, **Editor Preferences** | Opens the [About dialog](#about-scooterutils).                                     |

## Toolbar Dropdown

The **Scooter Utils** dropdown button appears in the Level Editor's Play toolbar. It groups the plugin's actions in one place:

* **Actions**
  * **Restart Editor...**
  * **Show Project in Explorer**
* **Settings**
  * **Plugin Settings...**
  * **About ScooterUtils...**

The toolbar button is shown by default. To hide it, go to **Edit** > **Editor Preferences** > **Plugins** > **Scooter Utilities** and disable **Show Toolbar Button** in the **UI** section.

## Restart Editor

**File** > **Restart Editor...** shuts down and restarts Unreal Engine, prompting you to save any unsaved changes before reloading your project. This is the same behavior you see when enabling or disabling a plugin.

**Hotkey:** **Ctrl + Shift + Alt + R**. You can change or disable the hotkey in the [Editor Preferences](./editor-preferences#hotkeys).

Restarting is handy when you're frequently testing code changes, clearing the undo stack, or refreshing the editor. It's also great when the editor starts feeling sluggish: hit **Restart Editor...** and you're back in action without going through the launcher or hunting for your `.uproject` file.

## Show Project in Explorer

**File** > **Show Project in Explorer** opens your system's file browser (File Explorer on Windows, Finder on macOS) focused on your main project folder, the one that contains your `.uproject` file.

This is handy when you've opened a project from the Epic Games Launcher and need to know where it actually lives on disk. While you can **Right-click** assets in the **Content Browser** to open the content folder, this menu item takes you directly to the project root.

## About ScooterUtils

**About ScooterUtils...** opens a dialog with the plugin's version and build information, plus buttons that open the documentation, the Discord community, the GitHub repository, and the author's support page in your browser. Press **Escape** or click **Close** to dismiss it.

You can open it from the **Scooter Utils** toolbar dropdown, or from the **About ScooterUtils...** button in **Edit** > **Editor Preferences** > **Plugins** > **Scooter Utilities** > **About Scooter Utilities**.

The second line under the version shows the build date and time (UTC). For builds made from the `main` branch, or from a copy that isn't a git checkout, it also shows the version. For any other branch, it shows the branch name instead, so you can tell a development build from a release.
