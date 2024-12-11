
<div align="center">

  <img src="assets/media/logo2.png" alt="logo" width="200" height="auto" />
    <h1><a href="https://github.com/ScottKirvan/ScooterUtils">ScottKirvan/ScooterUtils</a></h1>
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
    <a href="https://github.com/ScottKirvan/ScooterUtils/">View Demo</a>
  <span> · </span>
  -->
    <a href="https://scottkirvan.com/ScooterUtils">Documentation</a>
  <span> · </span>
    <a href="https://github.com/ScottKirvan/ScooterUtils/issues/">Report Bug</a>
  <span> · </span>
    <a href="https://github.com/ScottKirvan/ScooterUtils/issues/">Request Feature</a>
  </h4>
</div>

 **ScooterUtils** is an Unreal Engine editor plugin which contains miscellaneous
 artist/developer utilities, allowing you to quickly navigate to disk files, restart the system, and 
 to help keep some settings persistent between restarts in the editor.

If common tasks can be automated or streamlined, they may end up in ScooterUtils. Generally, the 
plugin is a Swiss Army Knife of tools and includes things that make Unreal Engine a bit quicker to 
use, especially if you're 
creating and maintaining several projects. If you've
got something you're repeatedly turning off or resetting every time you open  your projects, that might be a 
good candidate for an addition to ScooterUtils, so feel free to [make a suggestion](https://github.com/ScottKirvan/ScooterUtils/issues/).

This plugin currently contains:
- Menus:
  - *Restart Editor* - From the Main Menu bar, choose **File > Restart Editor...**
  - *Show Project in Explorer* - From the Main Menu bar, choose **File > Show Project in Explorer**
- Persistent Settings:
  - *Editor Scale (Applicaiton Scale)* - found in **Editor Preferences** under **Plugins/Scooter Utilities**
  - *Maximum FPS* - found in **Editor Preferences** under **Plugins/Scooter Utilities**
  - *Show FPS* - found in **Editor Preferences** under **Plugins/Scooter Utilities**
  
In Windows, the persistent editor Settings, are stored in this config file:  
```C:\Users\<username>\AppData\Local\UnrealEngine\<EngineVersion>\Saved\Config\Windows\EditorSettings.ini```

## Getting up and running

Navigate to the **Edit > Plugins** menu. Search for **Scooter Utils**, and enable the plugin (restart required). 
With the plugin enabled, you'll be able to find the following new tools:

### Restart Editor...
**Restart Editor** is found in the Main Menu bar, under
  **File > Restart Editor...**.

This will shutdown and restart unreal engine, prompting you to save any unsaved changes, and reload 
your project on restart.  This is the same behavior you see when you enable or disable a plugin.

This is for developers that need to frequently restart the engine to test code changes, clear 
undo stacks, refresh the system, etc.  It's also 
nice for those times you've been working in the editor for a while and things just start to feel... um...
off.  Just hit **Restart Editor...** and you're project will shutdown and restart -- no 
launcher popping up and prompting 
for a project to load, and no searching in file explorer to find the uproject file to open.

### Show Project in Explorer
**Show Project in Explorer** is found in the Main Menu bar, under
  **File > Show Project in Explorer**.

This will open file explorer focused on  your main project folder -- i.e. the same 
folder as your project's `.uproject` file.

Being able to open the project in Explorer is nice for when you've opened a project from 
the Launcher and you need to know where it's actually stored on disk.  You can 
also do this by right clicking on assets in the content browser, which will 
take you do your project's content folder, but this menu makes it a bit quicker to get to.

### Screen Real Estate: Editor Scale
Choose **Edit > Editor Preferences** from the Main Menu bar, scroll down and select **Plugins/Scooter Utilities** to find this and the following persistent editor settings.

The *Persistent Editor Scale* value is a percentage relative to the default 
screen size of elements like fonts, buttons, and other widgets in the Unreal 
Engine UI.  I like to work with all the fluff scaled down to about 80% of 
what's considered "normal," so I set the Persistent Editor Scale to *0.8*.

As of **Unreal Engine 5.4** there is an **Application Scale** setting under **Editor Preferences/Appearance**, 
which works great, but resets between different projects.  The setting in **ScooterUtils** is persistent
and works globally across all projects. 

> [!NOTE]
> This setting overrides the setting in **Editor Preferences/Appearance**, but note, when you disable this setting,
> the editor will default back to the normal 1.0 setting as a scale value.  You may need to restart the editor
> to get the system to recognize that you'd rather use the **Editor Prefernces/Appearance** setting.

### Max FPS
Found in the Main Menu
The **Max FPS** (Maximum Frames Per Second)
setting is found in the Main Menu bar; **Edit > Editor Preferences**, 
then selecting **Plugins/Scooter Utilities**.

**Max FPS** overrides the console variable setting, ```t.MaxFPS```, which sets
the engine's maximum editor frame rate.
The **ScooterUtils Max FPS** setting is persistent and will
stay set across all projects and restarts.
Set it to ```0``` to let the
system and it's console settings take over again.

Turn off **Smooth Frame Rate** and **Used Fixed Frame Rate** under
**Edit > Project Preferences**, **General Settings/Framerate** if you need to 
unclamp the system and run it as freewheeling as possible (These
are off by default).

### Show FPS
**Viewport Toggle: Show FPS** turns on the FPS display in the editor viewport, and keeps it on between restarts.  

This is the same functionality as the viewport hamburger menu's **Show FPS** setting, but this will stay enabled
between engine/editor restarts.


## Installation

This is kind of standard practice for GitHub Unreal plugins; it goes
like this:

1. Create a new Unreal project.
1. Create a ```Plugins``` folder in your project directory.
1. Clone the GitHub repository (or grab and unzip the project) into your
```Plugins``` folder.
1. Launch Unreal; You should be prompted to build the plugin.
2. Optional:  Use or convert your unreal project to a C++ project so
that you can edit and build the code outside of Unreal.

> [!WARNING]
> As of UE 5.5.0, the automatic building of plugins from source is no longer 
> working - You need to be using a C++ based Unreal project for the source 
> to build.  Once it's built, you can copy/paste the plugin to other projects 
> (or to your engine's plugin folder (**[UE_PATH]/Engine/Plugins/Marketplace**) to install it as an engine plugin).

## Where did "Persistent Editor Scale" go?  

This was my first plugin in Unreal Engine.
It was inspired by a [declined Epic Games Github Pull
Request](https://github.com/EpicGames/UnrealEngine/pull/7436). 

I wanted that feature myself, so I took the opportunity to teach myself plugin 
programming and implemented it as a feature called 
*Persistent Editor Scale*. Since that time (as of UE 5.4)
Epic [implemented the feature!](https://github.com/EpicGames/UnrealEngine/pull/7436#issuecomment-2068361921), and it can be found by navigating to
**Edit > Editor Preferences...**, **General - Appearance / User Interface / Application Scale**. 
I've removed the functionality from ScooterUtils to avoid any conflicts or confusion.

## Supported Platforms

Supported Unreal Engine versions: **4.25-5.5**<sup>*</sup>

For the most part, it should work on other platforms, and be easily adaptable to any earlier or later versions.

<sup>*</sup> *If you are using this repo/plugin with an engine version prior to UE 5.5, please make sure you clone/download the correct branch/version.*

## Dependencies

This plugin is source code only - I'm not currently providing binaries.
If you're looking for binaries for the Windows version, contact me
and I'll try get you a build.  If you need an older build or another
platform, I won't be able to build it for you, so you're going to have to get in touch with someone that can
help you (See the Support/Contacts section below).

The source requires Visual Studio (I;ve used the free 2019 & 2022 community version)
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
please see the official [Programming
Guide](https://docs.unrealengine.com/en-US/Programming/Plugins/index.html)!
The plugin development workflow is really very impressive, and if you've
ever developed plugins for other applications, you should check it out.  

## Contributions

- Please [file an
issue](https://github.com/ScottKirvan/UE4-ScooterUtils/issues),
or grab a fork, hack away, and submit some [pull
requests](https://github.com/ScottKirvan/UE4-ScooterUtils/pulls?q=is%3Aopen+is%3Apr).
- Contact me at
[linkedin.com/in/scottkirvan/](https://www.linkedin.com/in/scottkirvan/)
- You can also contact me at my [discord](https://discord.gg/TSKHvVFYxB)
server, I'm cptvideo.

To locate other developers, I'd like to recommend the **# cpp**, **# plugin-dev** and **#
engine-source** channels on the **Unreal Slackers** Discord server, but recently
there's a lot more trolls than helpful people up there.  It used to be better, but give it a 
shot.  You may have better luck than me :-)

## References / Inspirations / Credits

- sign into the Unreal Engine [Learning &
Support](https://www.unrealengine.com/en-US/learn) area and take the
*Best Practices for Creating and Using Plugins* course - it's great!
- This blog post on [custom project
settings](http://www.mov-eax-rgb.net/blog/custom-settings-object/)
is short, but it saved me when I got stuck
- The Unreal Team!  I had only been learning Unreal for a little
over a month when I first wrote this.  I am so totally blown away.
Epic's training material is outstanding - The sheer amount of material
available, directly from Unreal, and being produced by end users, artists,
and programmers is unlike anything I've ever experienced in the industry.
- Again, thanks to [Caio Liberali](https://github.com/caioliberali) for
the original [Pull Request](https://github.com/EpicGames/UnrealEngine/p)
on Github.  I had been hacking around in the engine source trying to
accomplish the same thing when the Pull Request came in.  Had it not
been declined, I probably never would have said, "hey, why not make it
a plugin?"

## Credits

**Copyright (c) (2020):** [Scott Kirvan](https://github.com/ScottKirvan)  - All rights reserved   
*ScooterUtils is licensed under the [BSD 3-Clause License](LICENSE.md).*  

Project Link:  [ScottKirvan/ScooterUtils](https://github.com/ScottKirvan/ScooterUtils)  
[CHANGELOG](notes/CHANGELOG.md)  
[TODO](notes/TODO.md)


