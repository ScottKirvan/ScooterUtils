
<div align="center">

  <img src="https://raw.githubusercontent.com/ScottKirvan/ScooterUtils/refs/heads/master/assets/media/logo2.png" alt="logo" width="200" height="auto" />
    <h1><a href="https://www.scottkirvan.com/ScooterUtils/notes/TODO.html">Scooter Utilities</a></h1>
  <h3>A collection of editor tools for Unreal Engine</h3>
  
<!-- Badges -->
<p>
  <a href="https://github.com/ScottKirvan/ScooterUtils/graphs/contributors">
    <img src="https://img.shields.io/github/contributors/ScottKirvan/ScooterUtils" alt="contributors" />
  </a>
  <a href="">
    <img src="https://img.shields.io/github/last-commit/ScottKirvan/ScooterUtils" alt="last update" />
  </a>
  <a href="https://github.com/ScottKirvan/ScooterUtils/network/members">
    <img src="https://img.shields.io/github/forks/ScottKirvan/ScooterUtils" alt="forks" />
  </a>
  <a href="https://github.com/ScottKirvan/ScooterUtils/stargazers">
    <img src="https://img.shields.io/github/stars/ScottKirvan/ScooterUtils" alt="stars" />
  </a>
  <a href="https://github.com/ScottKirvan/ScooterUtils/issues/">
    <img src="https://img.shields.io/github/issues/ScottKirvan/ScooterUtils" alt="open issues" />
  </a>
  <a href="https://github.com/ScottKirvan/ScooterUtils/blob/master/LICENSE">
    <img src="https://img.shields.io/github/license/ScottKirvan/ScooterUtils.svg" alt="license" />
  </a>
  <a href="https://discord.gg/gQH4mXWQRT">
    <!--<img src="https://img.shields.io/discord/704680098577514527?style=flat-square&label=%F0%9F%92%AC%20discord&color=00ACD7">-->
    <img src="https://img.shields.io/discord/1052011377415438346?style=flat-square&label=discord&color=00ACD7">
  </a>
</p>
   
<h4>
    <!--
    <a href="https://tinyurl.com/3vf7whyd">View Demo</a>
  <span> · </span>
  -->
    <a href="https://scottkirvan.com/ScooterUtils">Documentation</a>
  <span> · </span>
    <a href="https://github.com/ScottKirvan/ScooterUtils/issues/new?labels=bug&title=%5BBUG%5D">Report Bug</a>
  <span> · </span>
    <a href="https://github.com/ScottKirvan/ScooterUtils/issues/new?labels=enhancement&title=%5BFEATURE+REQUEST%5D">Request Feature</a>
  </h4>
</div>

 **Scooter Utilities** is an Unreal Engine editor plugin which contains miscellaneous artist/developer utilities, allowing you to quickly navigate to disk files, restart the system, and to help keep some settings persistent between restarts in the editor.

Think of **Scooter Utilities** as a Swiss Army Knife of tools that includes things that make the Unreal editor a bit quicker to use, especially if you're creating and maintaining several projects. If you've got something you're repeatedly turning off or resetting every time you open your projects, that might be a good candidate for an addition to **Scooter Utilities**, so feel free to [make a suggestion](https://github.com/ScottKirvan/ScooterUtils/issues/new?labels=enhancement&title=%5BFEATURE+REQUEST%5D).

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
- Menus:
  - *Restart Editor* - From the Main Menu bar, choose **File > Restart Editor...**
  - *Show Project in Explorer* - From the Main Menu bar, choose **File > Show Project in Explorer**
- Persistent Settings (settings that don't change between editor restarts/launches):
  - *Editor Scale (Application Scale)* - found in **Editor Preferences** under **Plugins/Scooter Utilities**
  - *Maximum FPS* - found in **Editor Preferences** under **Plugins/Scooter Utilities**
  - *Show FPS* - found in **Editor Preferences** under **Plugins/Scooter Utilities**
  
In Windows, the persistent editor Settings, are stored in this config file:  
```C:\Users\<username>\AppData\Local\UnrealEngine\<EngineVersion>\Saved\Config\Windows\EditorSettings.ini```
## Installation
>[!NOTE]
>This plugin isn't yet available on fab.com as of this writing, but it is aniticpated that it will be soon.

If you've gotten **Scooter Utilities** through fab, downloading and installing is handles through fab.com and the unreal marketplace.

- from fab.com, after purchase, click the `Download` link on the [**Scooter Utilities**]() product listing.
- A web pop-up will appear, with a link to the `Epic Games Launcher` - click that link and open the **Epic Games Launcher**.
- In the Launcher, scroll down to your **Fab Library**, and find, "**Scooter Utilities**," and click `Install to Engine`.
- If prompted, select the engine version that you wa:w
nt the plugin installed to, and you should be good to go.

If you've gotten, or plan to get, a source-code version of **Scooter Utilities**, 
and need to install it manually, please follow the Installation Instructions in the 
[Developer Documentation](https://www.scottkirvan.com/ScooterUtils/).

## Enable the Scooter Utilities Plugin
TODO:
- [ ] update this with images and wording for Scooter Utils, rather than Niagara

1. First open the Plugins menu by going to **Edit** > **Plugins**.
    
    [![](https://d1iv7db44yhgxn.cloudfront.net/documentation/images/f85a1c35-3a29-4f34-b90e-9243244b22f6/01-edit-plugins.png)](https://d1iv7db44yhgxn.cloudfront.net/documentation/images/f85a1c35-3a29-4f34-b90e-9243244b22f6/01-edit-plugins.png)
    
    Click image for full size.
    
2. In the Plugins menu, locate the **FX** section. You will see Niagara listed in this section. If the checkbox is checked, Niagara is already enabled. If the checkbox is unchecked, click on it to enable Niagara.
    
    [![](https://d1iv7db44yhgxn.cloudfront.net/documentation/images/f391cb7e-c521-4988-9ce9-c93d9c448c77/02-fx-plugins-niagara.png)](https://d1iv7db44yhgxn.cloudfront.net/documentation/images/f391cb7e-c521-4988-9ce9-c93d9c448c77/02-fx-plugins-niagara.png)
    
    Click image for full size.
    
3. If you had to enable Niagara, it will prompt you that a restart is required. Click **Restart Now** to relaunch the Unreal Editor with the Niagara plugin enabled.
    
    [![](https://d1iv7db44yhgxn.cloudfront.net/documentation/images/41cf6946-845d-4c8a-9579-613278e3326a/03-warning-restart.png)](https://d1iv7db44yhgxn.cloudfront.net/documentation/images/41cf6946-845d-4c8a-9579-613278e3326a/03-warning-restart.png)
    
    Click image for full size.

## End Result

Once the UE4 Editor has restarted, when you right-click in the **Content Browser** you will have a new **FX** section that will have all of the Niagara options.



This is kind of standard practice for GitHub Unreal plugins; it goes
like this:

1. Create a new Unreal project.
1. Create a ```Plugins``` folder in your project directory.
1. Clone the GitHub repository (or grab and unzip the project) into your
```Plugins``` folder.
1. Launch Unreal; You should be prompted to build the plugin.
2. Optional:  Use or convert your unreal project to a C++ project so
that you can edit and build the code outside of Unreal.

> [!NOTE]
> As of UE 5.5.0, the automatic building of plugins from source is no longer 
> working - You need to be using a C++ based Unreal project for the source 
> to build.  Once it's built, you can copy/paste the plugin to other projects 
> (or to your engine's plugin folder (**[UE_PATH]/Engine/Plugins/Marketplace**) to install it as an engine plugin).


## Usage

Navigate to the **Edit > Plugins** menu. Search for **Scooter Utilities**, and enable the plugin (restart required). 
With the plugin enabled, you'll be able to find the following new tools:

### File Menu: Restart Editor...
**Restart Editor** is found in the Main Menu bar, under
  **File > Restart Editor...**.

This will shutdown and restart unreal engine, prompting you to save any unsaved changes, and reload 
your project on restart.  This is the same behavior you see when, for example, you enable or disable a plugin.

This is for anyone that frequently restarts the engine to test code changes, clear 
undo stacks, refresh the system, etc.  It's also 
nice for those times you've been working in the editor for a while and things just start to feel... um...
off.  Just hit **Restart Editor...** and you're project will shutdown and 
restart -- no launcher popping up and prompting 
for a project to load, and no searching in file explorer to find the uproject file to open.

### File Menu: Show Project in Explorer
**Show Project in Explorer** is found in the Main Menu bar, under
  **File > Show Project in Explorer**.

This will open file explorer focused on  your main project folder -- i.e. the same 
folder as your project's `.uproject` file.

Being able to open the project in Explorer is nice for when you've opened a project from 
the Launcher and you need to know where it's actually stored on disk.  You can 
also do this by right clicking on assets in the content browser, which will 
take you do your project's content folder, but this menu makes it a bit quicker to get to.

### Prefs: Screen Real Estate: Persistent Editor Scale
Choose **Edit > Editor Preferences** from the Main Menu bar, scroll down and select **Plugins/Scooter Utilities** -- this setting is in the **Screen Real Estate** section.

The *Persistent Editor Scale* value is a percentage relative to the default 
screen size of elements like fonts, buttons, and other widgets in the Unreal 
Engine UI.  I like to work with all the fluff scaled down to about 80% of 
what's considered "normal," so I set the Persistent Editor Scale to *0.8*.

As of **Unreal Engine 5.4** there is an Application Scale setting under **Editor Preferences/Appearance**, 
which works great, but resets between different projects.  The setting in **Scooter Utilities** is persistent
and works globally across all projects. 

> [!NOTE]
> This setting overrides the setting in **Editor Preferences/Appearance**, but note, when you disable this setting,
> the editor will default back to the normal 1.0 setting as a scale value.  You may need to restart the editor
> to get the system to recognize that you'd rather use the **Editor Preferences/Appearance** setting.

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



## Supported Platforms

Supported Unreal Engine versions: **4.25-5.5**<sup>*</sup>

For the most part, it should work on other platforms, and be easily adaptable to any earlier or later versions.

<sup>*</sup> *If you are building this repo/plugin from source, with an engine version prior to UE 5.5, please make sure you clone/download the correct branch/version.*

## Dependencies

This plugin is source code only - I'm not currently providing binaries.
If you're looking for binaries for the Windows version, contact me
and I'll try get you a build.  If you need an older build or another
platform, I won't be able to build it for you, so you're going to have to get in touch with someone that can
help you (See the Support/Contacts section below).

The source requires Visual Studio (I've used the free 2019 & 2022 community version)
and either an Unreal C++ code (rather than blueprint) project or the full
Unreal Engine 4 source code from GitHub (just use the project-based
approach, it's so easy). 

Building it inside a project is dead simple.  Clone the repository
into the *Plugins* directory of your Unreal C++ based project. Go to
**File**, and select **Update Visual Studio Project**.  From there,
the plugin should be buildable, and once compiled, can be left in your
project directory for the project you're working on, or copied into
your Engine's main *Plugins* folder so it's available to all your future
editing sessions.  

If you are new to programming in UE,
please see the official [Programming Guide](https://docs.unrealengine.com/en-US/Programming/Plugins/index.html). 
The plugin development workflow is really very impressive, and if you've
ever developed plugins for other applications, you should check it out.  

## Contributions / Contact

- Please [file an issue](https://github.com/ScottKirvan/ScooterUtils/issues/new).
- Contact me at [linkedin.com/in/scottkirvan/](https://www.linkedin.com/in/scottkirvan/)
- You can also contact me at my [discord](https://discord.gg/TSKHvVFYxB) server, I'm cptvideo.
- If you're a developer, and want to contribute directly to this project, please check out the [developer documentation](notes/DEV_README.md), [grab a fork](https://github.com/ScottKirvan/ScooterUtils/fork), hack away, and submit a [pull request](https://github.com/ScottKirvan/ScooterUtils/pulls). 

## Contributing
Do you know how to code up a cool tool or feature that would be good to include in this project? Interested in contributing with writing documentation or anything else? Did you find a bug?! Come up with a new idea?! Please help out!

If you lean into the technical side of things and are comfortable using GitHub, check the [issues](https://github.com/ScottKirvan/ScooterUtils/issues) link to find something that might be fun to tackle.  The best way to help would be to contribute directly to the code or documentation:  [Grab a fork](https://github.com/ScottKirvan/ScooterUtils/fork) and submit a [pull request](https://github.com/ScottKirvan/ScooterUtils/pulls) with you're changes.  For technical details regarding the ScooterUtils GitHub repo, check out our [developer documentation](notes/DEV_README.md).

If you really don't want to have to learn GitHub, but would still like to contribute, just follow these links to [report a bug](https://github.com/ScottKirvan/ScooterUtils/issues/new?labels=bug&title=%5BBUG%5D) or [request something new](https://github.com/ScottKirvan/ScooterUtils/issues/new?labels=enhancement&title=%5BFEATURE+REQUEST%5D) you'd like to see.

## Support/Contact
- Feel free to reach out to me on the [Unreal Slackers](https://discord.gg/unreal-slackers) discord. I'm @Fragmanget_. There is a ton of other Unreal programmers up there, so if I'm not around to help, someone else may be able to get you going.
- You can also reach me on my personal [Discord Server](https://discord.gg/TSKHvVFYxB) (@cptvideo), via [LinkedIn](https://www.linkedin.com/in/scottkirvan/), or [email](mailto:ScooterUtils@skvfx.com).
## Credits

**Copyright (c) (2020-2024):** [Scott Kirvan](https://github.com/ScottKirvan)  - All rights reserved   
*ScooterUtils is licensed under the [BSD 3-Clause License](LICENSE.md).*  

Project Link:  [ScottKirvan/ScooterUtils](https://github.com/ScottKirvan/ScooterUtils)  
[CHANGELOG](notes/CHANGELOG.md)  
[TODO](notes/TODO.md)




