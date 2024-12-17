
<div align="center">

  <img src="https://raw.githubusercontent.com/ScottKirvan/ScooterUtils/refs/heads/master/assets/media/logo2.png" alt="logo" width="200" height="auto" />
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
    <a href="https://tinyurl.com/3vf7whyd">View Demo</a>
  <span> · </span>
    <a href="https://www.scottkirvan.com/ScooterUtils/notes/USER_README">User Documentation</a>
  <span> · </span>
    <a href="https://github.com/ScottKirvan/ScooterUtils/issues/new?labels=bug&title=%5BBUG%5D%20">Report Bug</a>
  <span> · </span>
    <a href="https://github.com/ScottKirvan/ScooterUtils/issues/new?labels=enhancement&title=%5BFEATURE+REQUEST%5D%20">Request Feature</a>
  </h4>
</div>

 **ScooterUtils** is an Unreal Engine editor plugin (**Scooter Utilities**) which contains miscellaneous artist/developer utilities, allowing you to quickly navigate to disk files, restart the system, and to keep some settings persistent between restarts in the editor.

Think of **ScooterUtils** as a Swiss Army Knife of tools that make Unreal Engine a bit quicker to use, especially if you're creating and maintaining several projects. If you've got something you're repeatedly turning on or resetting every time you open your projects, that might be a good candidate for an addition to **Scooter Utilities**, so feel free to [make a suggestion](https://github.com/ScottKirvan/ScooterUtils/issues/new?labels=enhancement&title=%5BFEATURE+REQUEST%5D).

If you're looking for information on how to *use* the plugin inside Unreal, please check out the [User Documentation](notes/USER_README.md). This document is for people using the source code in the [GitHub repository](https://github.com/ScottKirvan/ScooterUtils).

Branches
--------

```
master
└─── main development branch - supports the latest version of Unreal
All-Versions-Prior-to-5.1
└─── These are the UE4.x versions. Tested back to 4.25, may work in earlier versions.
UE-5.1-to-5.2
└─── tested and working in UE-5.1-to-5.2
UE-5.3-to-5.4
└─── tested and working in UE-5.3-to-5.4
release-please--branches--master
└─── used by Please-Release GitHub action.
```
New features are added to the `master` branch.  Older branches may not have the same feature support.

Repo Layout
-----------
```
ScooterUtils
├───.github
│   ├───release-please
│   └───workflows
├───Config
├───Resources
├───Source/ScooterUtils
│   ├───────Private
│   └───────Public
├───_layouts
├───assets
│   ├───css
│   └───media
└───notes
```
The `_layouts` and `assets/css` folders help support the look of the repo when rended to GitHub Pages (Deployment Workflow).  You can see an example of this repo processed using Jekyll and published at [ScottKirvan.com](https://www.scottkirvan.com/ScooterUtils/). 

The css file creates a page that is styled similar to GitHub's [Dark High Contrast](https://github.blog/changelog/2021-08-25-dark-high-contrast-theme-ga/) theme.

The files in the `.github` folder implement and customizes a github action that runs [Release-Please](https://github.com/googleapis/release-please), which helps with releases, version numbering, and updating the [CHANGELOG](notes/CHANGELOG.md).

Table of Contents
-----------------
- [Branches](#branches)
- [Repo Layout](#repo-layout)
- [Installation](#installation)
- [Features / Usage](#features--usage)
- [Contributions / Contact](#contributions--contact)
- [References / Inspirations / Credits](#references--inspirations--credits)

Installation
------------
This is kind of standard practice for GitHub Unreal plugins<sup>*</sup>; it goes
like this:

1. Create a new Unreal project.
1. Create a ```Plugins``` folder in your project directory.
1. Clone the GitHub repository (or grab and unzip the project) into your
```Plugins``` folder.
1. Launch Unreal; You should be prompted to build the plugin.
2. Optional:  Use or convert your unreal project to a C++ project so
that you can edit and build the code outside of Unreal.

> [!NOTE]
> As of UE 5.5.0, the automatic building of plugins within blueprint-only projects is no longer working - You need to be using a C++ based Unreal project for the source to build.  Once it's built, you can copy/paste the plugin to other projects (or to your engine's plugin folder (**[UE_PATH]/Engine/Plugins/Marketplace**) to install it as an engine plugin).
> 
> Working with c++ projects may involve additional dependencies, like installing and configuring an IDE, which may be more than some users are willing to do, and more than I'm willing to document and support, which is why I've made the plugin available on the [Fab Marketplace](http://fab.com).


Features / Usage
-----
For documentation on what the plugin does, installing from fab, enabling, and using it, see the [User Documentation](notes/USER_README.md).

Developer Notes
--------
ScooterUtils is implemented in a single module: "ScooterUtils." It's an editor-only plugin (no runtime functionality), and uses an OnEndFrame callback to execute certain functionality when we're confident the engine (and our module) is fully loaded (PostEngineInit).

FScooterUtilsModule is the main module implementation, and that's where all the functionality of ScooterUtilsMenu (for restart, and open explorer) happen, and ScooterUtilsSettings (for all the Editor Preferences settings) are handled.

ScooterUtils preferences (engine install) are written to disk at:
```
c:\Users\<username>\AppData\Local\UnrealEngine\<EngineVersion>\Saved\Config\WindowsEditor\EditorSettings.ini
```
The ScooterUtils section of EngineSettings.ini will look something like:
```ini
[/Script/ScooterUtils.ScooterUtilsSettings]
bOverrideUEApplicationScale=True
ApplicationScale=0.800000
MaxFPS=200
ShowViewportFPS=False
```
## Supported Platforms

Supported Unreal Engine versions: **4.25-5.5**<sup>*</sup>

For the most part, it should work on other platforms, and be easily adaptable to any earlier or later versions.

<sup>*</sup> *If you are building this repo/plugin from source, with an engine version prior to UE 5.5, please make sure you clone/download the correct branch/version.*

## Dependencies

The source requires Visual Studio (I've used the free 2019 & 2022 community version)
and either an Unreal C++ code (rather than blueprint) project or the full
Unreal Engine 4 source code from GitHub.
approach, it's so easy). 

Building it inside a project is dead simple.  Clone the repository
into the *Plugins* directory of your Unreal C++ based project. Go to
**File**, and select **Update Visual Studio Project**.  From there,
the plugin should be buildable, and once compiled, can be left in *Plugins* directory for the project you're working on, or copied into
your Engine's main *Plugins* folder so it's available to all your future
editing sessions.  

If you are new to programming in UE,
please see the official [Programming Guide](https://docs.unrealengine.com/en-US/Programming/Plugins/index.html). 
The plugin development workflow is really very impressive, and if you've
ever developed plugins for other applications, you should check it out.  

Contributions / Contact
-----------------------
- Please [report any issues](https://github.com/ScottKirvan/ScooterUtils/issues/new?labels=bug&title=%5BBUG%5D%20), request a [new feature](https://github.com/ScottKirvan/ScooterUtils/issues/new?labels=enhancement&title=%5BFEATURE+REQUEST%5D%20), or [grab a fork](https://github.com/ScottKirvan/ScooterUtils/fork), hack away, and submit a [pull request](https://github.com/ScottKirvan/ScooterUtils/pulls).
- Contact me at [linkedin.com/in/scottkirvan/](https://www.linkedin.com/in/scottkirvan/)
- You can also contact me at my [discord](https://discord.gg/TSKHvVFYxB) server, I'm cptvideo.

To locate other developers, I'd like to recommend the **# cpp**, **# plugin-dev** and **# engine-source** channels on the **Unreal Slackers** Discord server, but recently there's a lot more trolls than helpful people up there.  It used to be better, but give it a shot.  You may have better luck than me :-)

References / Inspirations / Credits
-----------------------------------
- <strike>To learn c++ coding plugins in Unreal, sign into the Unreal Engine [Learning & Support](https://www.unrealengine.com/en-US/learn) area and take the *Best Practices for Creating and Using Plugins* course - it's great!</strike> *Anyone know where this went?*
- Another resource for creating Editor (not runtime) specific tools is [this tutorial](https://lxjk.github.io/2019/10/01/How-to-Make-Tools-in-U-E.html) by Xun (Eric) Zhang.
- This blog post on [custom project settings](http://www.mov-eax-rgb.net/blog/custom-settings-object/) is short, but it saved me when I got stuck
- Huge thanks to the Unreal Team!  I had only been learning Unreal for a little over a month when I first wrote this.  I am so totally blown away.  Epic's training material is outstanding - The sheer amount of material available, directly from Unreal, and being produced by end users, artists, and programmers is unlike anything I've ever experienced in the industry.
- Thanks, also, to [Caio Liberali](https://github.com/caioliberali) for the original Unreal Engine [Pull Request](https://github.com/EpicGames/UnrealEngine/pull/7436) that inspired this project.  

---
**Copyright (c) (2020):** [Scott Kirvan](https://github.com/ScottKirvan)  - All rights reserved   
*ScooterUtils is licensed under the [BSD 3-Clause License](../LICENSE.md).*  

Project Link:  [ScooterUtils](https://github.com/ScottKirvan/ScooterUtils)  
[CHANGELOG](notes/CHANGELOG.md)  
[TODO](notes/TODO.md)
