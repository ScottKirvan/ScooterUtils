
<table border=0><tr><td valign=center>
<img src="https://raw.githubusercontent.com/ScottKirvan/ScooterUtils/refs/heads/master/assets/media/logo.png" alt="logo" width="20" height="auto" />
</td><td valign=top>
<a style="color:#ffffff" href="http://skvfx.com">skvfx.com</a> / <a style="color:#ffffff" href="http://skvfx.com/ScooterUtils">ScooterUtils</a>
</td></tr></table>

<div align="center">
  <h1><a href="https://www.fab.com/sellers/SKVFX">Scooter Utilities</a></h1>A collection of editor tools for Unreal Engine<br><br>
  <img src="https://raw.githubusercontent.com/ScottKirvan/ScooterUtils/refs/heads/master/assets/media/logo2.png" alt="logo" width="200" height="auto" />
<h4>
    <!--
    <a href="https://tinyurl.com/3vf7whyd">View Demo</a>
  <span> · </span>
  -->
    <a href="https://scottkirvan.com/ScooterUtils">User Documentation</a>
  <span> · </span>
    <a href="https://github.com/ScottKirvan/ScooterUtils/issues/new?labels=bug&title=%5BBUG%5D">Report Bug</a>
  <span> · </span>
    <a href="https://github.com/ScottKirvan/ScooterUtils/issues/new?labels=enhancement&title=%5BFEATURE+REQUEST%5D">Request Feature</a>
  </h4>
</div>

 **Scooter Utilities** is an Unreal Engine editor plugin which contains miscellaneous artist/developer utilities, allowing you to quickly navigate to disk files, restart/reload your projects, and to help keep some settings persistent between restarts in the editor.

## Table of Contents

- [Features](#features)
- [Usage](#usage)
  - [File Menu: Restart Editor...](#file-menu-restart-editor)
  - [File Menu: Show Project in Explorer](#file-menu-show-project-in-explorer)
  - [Prefs: Screen Real Estate: Persistent Editor Scale](#prefs-screen-real-estate-persistent-editor-scale)
  - [Prefs: Max FPS](#prefs-max-fps)
  - [Prefs: Show FPS](#prefs-show-fps)
- [Installation](#installation)
- [Supported Platforms](#supported-platforms)
- [Dependencies](#dependencies)
- [Contributions](#contributions)
- [References / Inspirations / Credits](#references--inspirations--credits)

## Features
- Restart the editor from the **File** menu.
- Open your project folder in File Explorer from the **File** menu.
- Adjust the size of the Unreal Editor interface fonts and widgets to what's comfortable or for doing presentations.
- Set the Maximum FPS value, and have that always set as you default inside Unreal Engine's Editor.
- Turn on the viewport fps display and have it stay on after restarting the engine.
## Download and Install from FAB
>[!WARNING] This plugin isn't yet available on fab.com as of this writing, but it is aniticpated that it will be soon.  The documentation written here assumes you've downloaded and installed the plugin from Fab.

If you've gotten **Scooter Utilities** through Fab Marketplace, downloading and installing is handled through fab.com and the unreal marketplace.

- From fab.com, after purchase, click the `Download` link on the [**Scooter Utilities**]() product listing.
- A web pop-up will appear, with a link to the `Epic Games Launcher` - click that link and open the **Epic Games Launcher**.
- In the Launcher, scroll down to your **Fab Library**, and find, "**Scooter Utilities**," and click `Install to Engine`.
- If prompted, select the engine version that you want the plugin installed to, and you should be good to go.

If you've gotten, or plan to get, a source-code version of **Scooter Utilities**, and need to install it manually, please follow the Installation Instructions in the [Developer Documentation](https://www.scottkirvan.com/ScooterUtils/).

## Usage
> [!NOTE] Make sure you enable the Scooter Utilities plugin.  You can do this by navigating to Edit > Plugins and searching for Scooter Utilities.

With the plugin enabled, you will have the following new tools in the Unreal Engine Editor:

### File > Restart Editor...
**Restart Editor** is found in the Main Menu bar, under
  **File > Restart Editor...**.

This will shutdown and restart unreal engine, prompting you to save any unsaved changes, and reload your project on restart.  This is the same behavior you see when, for example, you enable or disable a plugin.

This feature is for anyone that frequently restarts the engine to test code changes, clear undo stacks, refresh the system, etc.  It's also nice for those times you've been working in the editor for a while and things just start to feel... um...
off.  Just hit **Restart Editor...** and you're project will shutdown and 
restart -- no launcher popping up and prompting 
for a project to load, and no searching in file explorer to find the uproject file to open.

### File Menu: Show Project in Explorer
**Show Project in Explorer** is found in the Main Menu bar, under
  **File > Show Project in Explorer**.

This will open file explorer focused on  your main project folder -- i.e. the same 
folder as your project's `.uproject` file.

Being able to open the project in Explorer is nice for when you've opened a project from the Launcher and need to know where it's actually stored on disk.  You can also do this by right clicking on assets in the content browser, which will take you do your project's content folder, but this menu makes takes you directly to the project root.

### Prefs: Screen Real Estate: Persistent Editor Scale
Choose **Edit > Editor Preferences** from the Main Menu bar, scroll down and select **Plugins/Scooter Utilities** -- this setting is in the **Screen Real Estate** section.

The *Persistent Editor Scale* value is a percentage relative to the default 
screen size of elements like fonts, buttons, and other widgets in the Unreal 
Engine UI.  I like to work with all the fluff scaled down to about 80% of 
what's considered "normal," so I set the Persistent Editor Scale to *0.8*.

As of **Unreal Engine 5.4** there is an Application Scale setting under **Editor Preferences/Appearance**, 
which works great, but resets between different projects.  The setting in **Scooter Utilities** is persistent
and works globally across all projects. 

> [!NOTE] This setting overrides the setting in Editor Preferences > Appearance, but when you disable this setting, the editor will default back to the normal 1.0 setting as a scale value.  If your setting under Editor Preferences > Appearance is not 1.0, you may need to restart the editor to get the system to pick up the correct Application Scale.

### Prefs: Max FPS
Choose **Edit > Editor Preferences** from the Main Menu bar, scroll down and select **Plugins/Scooter Utilities** -- this setting is in the **Max FPS** section.

*Persistent Editor Max FPS Setting* overrides the console variable setting, ```t.MaxFPS```, which sets
the engine's maximum editor frame rate.
The *Max FPS* setting is persistent and will
stay set across all projects and restarts.
Set it to ```0``` to let the
system and it's console settings take over again.

To ensure the system is running as freewheeling as possible, turn off **Smooth Frame Rate** and **Used Fixed Frame Rate** under
**Edit > Project Preferences**, **General Settings/Framerate** (These
are typically  off by default).

### Prefs: Show FPS
Choose **Edit > Editor Preferences** from the Main Menu bar, scroll down and select **Plugins/Scooter Utilities** -- this setting is in the **Show FPS Onscreen** section.

*Viewport Toggle: Show FPS* turns on the FPS display in the editor viewport, and keeps it on between restarts.  

This is the same functionality as the viewport hamburger menu's **Show FPS** setting, but this will stay enabled
between engine/editor restarts.


Contributions
-----------------------
Do you know how to code up a cool tool or feature that would be good to include in this project? Interested in contributing with writing documentation or anything else? Did you find a bug?! Come up with a new idea?! Please help out!

- [report any issues](https://github.com/ScottKirvan/ScooterUtils/issues/new?labels=bug&title=%5BBUG%5D%20).
- [request new features](https://github.com/ScottKirvan/ScooterUtils/issues/new?labels=enhancement&title=%5BFEATURE+REQUEST%5D%20).
- To show your support for my work, Throw me a bone!  please TODO TODO - rate/review the plugin on [fab](http://fab.com), and/or [donate]() to my GitHub projects.


## Contributing
Do you know how to code up a cool tool or feature that would be good to include in this project? Interested in contributing with writing documentation or anything else? Did you find a bug?! Come up with a new idea?! Please help out!

If you lean into the technical side of things and are comfortable using GitHub, check the [issues](https://github.com/ScottKirvan/ScooterUtils/issues) link to find something that might be fun to tackle.  The best way to help would be to contribute directly to the code or documentation:  [Grab a fork](https://github.com/ScottKirvan/ScooterUtils/fork) and submit a [pull request](https://github.com/ScottKirvan/ScooterUtils/pulls) with you're changes.  For technical details regarding the ScooterUtils GitHub repo, check out our [developer documentation](notes/DEV_README.md).

If you really don't want to have to learn GitHub, but would still like to contribute, just follow these links to [report a bug](https://github.com/ScottKirvan/ScooterUtils/issues/new?labels=bug&title=%5BBUG%5D) or [request something new](https://github.com/ScottKirvan/ScooterUtils/issues/new?labels=enhancement&title=%5BFEATURE+REQUEST%5D) you'd like to see.

- To show your support for my work, Throw me a bone!  please TODO TODO - rate/review the plugin on [fab](http://fab.com), and/or [donate]() to my GitHub projects.

## Support/Contact
- Feel free to reach out to me on the [Unreal Slackers](https://discord.gg/unreal-slackers) discord. I'm @Fragmanget_. There is a ton of other Unreal programmers up there, so if I'm not around to help, someone else may be able to get you going.
- You can also reach me on my personal [Discord Server](https://discord.gg/TSKHvVFYxB) (@cptvideo), via [LinkedIn](https://www.linkedin.com/in/scottkirvan/), or [email](mailto:ScooterUtils@skvfx.com).

## Credits

**Copyright (c) (2020-2024):** [Scott Kirvan](https://github.com/ScottKirvan)  - All rights reserved   
*ScooterUtils is licensed under the [BSD 3-Clause License](LICENSE.md).*  

Project Link:  [ScottKirvan/ScooterUtils](https://github.com/ScottKirvan/ScooterUtils)  
[CHANGELOG](notes/CHANGELOG.md)  
[TODO](notes/TODO.md)




