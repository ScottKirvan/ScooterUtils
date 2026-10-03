# Scooter Utilities [![starline](https://raw.githubusercontent.com/ScottKirvan/ScooterUtils/refs/heads/starlines/ScottKirvan/ScooterUtils/starline.svg)](https://github.com/qoomon/starlines)
<div align="center">

  <img src="assets/media/logo2.png" alt="logo" width="200" height="auto" />
    <h1><a href="https://github.com/ScottKirvan/ScooterUtils">ScottKirvan/ScooterUtils</a></h1>
  <h3>Your Swiss Army Knife of editor tools for Unreal Engine</h3>
  
  
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
  <a href="https://github.com/ScottKirvan/ScooterUtils/blob/main/LICENSE.md">
    <img src="https://img.shields.io/github/license/ScottKirvan/ScooterUtils.svg" alt="license" />
  </a>
  <a href="https://discord.gg/TN6XJSNK5Y">
    <!--<img src="https://img.shields.io/discord/704680098577514527?style=flat-square&label=%F0%9F%92%AC%20discord&color=00ACD7">-->
    <img src="https://img.shields.io/discord/1052011377415438346?style=flat-square&label=discord&color=00ACD7">
  </a>
</p>
   
<h4>
    <a href="https://tinyurl.com/3vf7whyd">View Demo</a>
  <span> · </span>
    <a href="https://www.scottkirvan.com/ScooterUtils/guide/">Documentation</a>
  <span> · </span>
    <a href="https://github.com/ScottKirvan/ScooterUtils/issues/new?template=bug_report.md">Report Bug</a>
  <span> · </span>
    <a href="https://github.com/ScottKirvan/ScooterUtils/issues/new?template=feature_request.md">Request Feature</a>
  </h4>
</div>

**Scooter Utilities** is an Unreal Engine editor plugin that bundles essential quality-of-life tools for artists and developers. Quickly navigate to disk files, restart/reload your projects with a single click, and keep important settings persistent between editor sessions. It also ships a runtime Blueprint library for JSON, file IO, config access, debug logging, Blueprint reflection, and placeholder text.

Think of **ScooterUtils** as a Swiss Army Knife of tools that make Unreal Engine a bit quicker to use, especially if you're creating and maintaining several projects. If you've got something you're repeatedly turning on or resetting every time you open your projects, that might be a good candidate for an addition to **Scooter Utilities**, so feel free to [make a suggestion](https://github.com/ScottKirvan/ScooterUtils/issues/new?template=feature_request.md).

If you're looking for information on how to *use* the plugin inside Unreal, please check out the [User Guide](https://www.scottkirvan.com/ScooterUtils/guide/). This document is for people working with the source code in this repository.

## Key Features

**Automated Release Management**: The `release.yml` workflow uses [Release-Please](https://github.com/googleapis/release-please) for automated versioning and CHANGELOG updates driven by [Conventional Commits](https://www.conventionalcommits.org/). Merging the Release-Please pull request back into `main` creates a new release and tags it in GitHub. AI-generated release notes and Discord notifications are wired in. See [CONTRIBUTING.md](CONTRIBUTING.md) for commit conventions.

**VitePress Documentation Site**: The `docs/` folder contains the [VitePress](https://vitepress.dev/) user guide, deployed to [scottkirvan.com/ScooterUtils](https://www.scottkirvan.com/ScooterUtils/) by the `docs.yml` workflow whenever `docs/` changes on `main`.

**Pre-release Staging**: The `pre-release-staging.yml` workflow lets you generate and review AI-drafted release notes on a staging branch before the release goes out.

**AI Agent Context (optional)**: The included `CLAUDE.md` gives AI coding agents (e.g. [Claude Code](https://claude.ai/code)) the project's engineering standards — branching conventions, commit discipline, test-driven development, verification discipline, and a no-shortcuts ethos.

## Repo Layout

```
ScooterUtils/
├── .github/
│   ├── release-please/         # Release-Please configuration and version manifest
│   └── workflows/              # GitHub Actions workflows (see Key Features above)
├── Config/                     # Plugin packaging filters
├── Resources/                  # Plugin icon
├── Source/
│   ├── ScooterUtils/           # Editor-only module: menus, toolbar, Editor Preferences
│   └── ScooterUtilsBPLibrary/  # Runtime module: Blueprint node library
├── _layouts/                   # Legacy Jekyll layout for GitHub Pages
├── assets/
│   ├── css/                    # Legacy Jekyll styles
│   └── media/                  # Images and logos
├── docs/                       # VitePress documentation site
├── notes/                      # CHANGELOG, VERSION, TODO
├── tools/                      # Packaging scripts
├── CLAUDE.md                   # AI agent context (optional)
├── CONTRIBUTING.md
├── LICENSE.md
├── README.md
└── ScooterUtils.uplugin        # Plugin descriptor
```

The plugin is made of *two* modules because one needs to be editor-only and the other needs to run in-game. `ScooterUtils` is the editor-only module; it loads at `PostEngineInit` and uses an `OnEndFrame` callback to apply settings once the engine is fully loaded. `FScooterUtilsModule` is the main module implementation, where `ScooterUtilsMenu` (restart editor, show project in explorer) and `ScooterUtilsSettings` (the persistent Editor Preferences) are wired up. `ScooterUtilsBPLibraryModule` is the runtime module and only contains Blueprint nodes.

> **Note:** Issue templates, PR templates, and funding config live in the org-level [`ScottKirvan/.github`](https://github.com/ScottKirvan/.github) repo and apply here automatically via GitHub's community health file fallback.

Features
--------
- **Restart the editor** from the **File** menu, the toolbar, or a customizable hotkey (default **Ctrl+Shift+Alt+R**)
- **Show Project in Explorer** opens your project folder on disk with one click
- **Toolbar dropdown** in the Level Editor for quick access to the plugin's tools and settings
- **Persistent Editor Preferences**: application scale, max FPS, and viewport FPS display that survive restarts and apply across projects
- **Blueprint nodes** for JSON, file IO, global config, debug logging, Blueprint reflection, and Lorem Ipsum placeholder text

See the [User Guide](https://www.scottkirvan.com/ScooterUtils/guide/) for the full feature documentation.

Installation
------------
Supported Unreal Engine versions on `main`: **5.5–5.8**, on Windows, macOS, and Linux (the Blueprint library also supports Android).

To install from Fab, see [Installing and Enabling](https://www.scottkirvan.com/ScooterUtils/guide/installing) in the User Guide. To build from source, the usual approach for GitHub Unreal plugins goes like this:

1. Create a new Unreal C++ project, or open an existing one.
2. Create a `Plugins` folder in your project directory.
3. Clone the repository (or download and unzip it) into your `Plugins` folder. For engine versions older than 5.5, use the matching branch listed below.
4. Launch Unreal; you should be prompted to build the plugin. Alternatively, go to **Tools** > **Refresh Visual Studio Project** and build from your IDE.
5. Optional: once it's built, copy the plugin to other projects, or to your engine's plugin folder (`[UE_PATH]/Engine/Plugins/Marketplace`) to install it as an engine plugin.

> [!NOTE]
> As of UE 5.5, plugins no longer build automatically inside Blueprint-only projects. Use a C++ project to build the source, then copy the built plugin wherever you need it.

Building requires an IDE set up for Unreal C++ development (Visual Studio 2022 Community works well on Windows). If you are new to programming in Unreal, see the official [plugins documentation](https://dev.epicgames.com/documentation/en-us/unreal-engine/plugins-in-unreal-engine).

**Branches:**
```
main
     └─── main development branch - supports UE 5.5 through 5.8
UE-5.3-to-5.4
     └─── tested and working in UE 5.3 to 5.4
UE-5.1-to-5.2
     └─── tested and working in UE 5.1 to 5.2
All-Versions-Prior-to-5.1
     └─── the UE 4.x versions. Tested back to 4.25, may work in earlier versions.
release-please--branches--main
     └─── used by the Release-Please GitHub action
```
New features are added to the `main` branch. Older branches may not have the same feature support.

Usage
-----
Enable the plugin under **Edit** > **Plugins**, then:

- Use **File** > **Restart Editor...** or **File** > **Show Project in Explorer**, or the **Scooter Utils** toolbar dropdown.
- Configure persistent settings under **Edit** > **Editor Preferences** > **Plugins** > **Scooter Utilities**.
- Find the Blueprint nodes under the **Scooter Utilities** category in the Blueprint node browser.

Editor Preferences are saved per user, per engine version, in `EditorSettings.ini`. On Windows that's:
```
C:\Users\<username>\AppData\Local\UnrealEngine\<EngineVersion>\Saved\Config\WindowsEditor\EditorSettings.ini
```
```ini
[/Script/ScooterUtils.ScooterUtilsSettings]
bOverrideUEApplicationScale=True
ApplicationScale=0.800000
MaxFPS=200
ShowViewportFPS=False
```

See the [User Guide](https://www.scottkirvan.com/ScooterUtils/guide/) for details on every menu, setting, and Blueprint node.

Contributions / Contact
-----------------------
- Please [file an issue](https://github.com/ScottKirvan/ScooterUtils/issues/new/choose), or [grab a fork](https://github.com/ScottKirvan/ScooterUtils/fork), hack away, and submit a [pull request](https://github.com/ScottKirvan/ScooterUtils/pulls). See [CONTRIBUTING.md](CONTRIBUTING.md) for details.
- To show your support, star this repo, rate/review the plugin on [Fab](https://www.fab.com/), or sponsor development through [Ko-fi](https://ko-fi.com/ScottKirvan) or [GitHub Sponsors](https://github.com/sponsors/ScottKirvan).
- Find me on the [Unreal Slackers](https://discord.gg/unreal-slackers) Discord as @Fragmanget_. There are a ton of other Unreal programmers up there, so if I'm not around to help, someone else may be able to get you going.
- Contact me at [linkedin.com/in/scottkirvan/](https://www.linkedin.com/in/scottkirvan/) or by [email](mailto:ScooterUtils@skvfx.com).
- You can also contact me at my [discord](https://discord.gg/TN6XJSNK5Y) server, I'm cptvideo.

Credits
-------
**[ScooterUtils](https://github.com/ScottKirvan/ScooterUtils)** — Copyright (c) 2020-2025 [Scott Kirvan](https://github.com/ScottKirvan). [BSD 3-Clause License](LICENSE.md).

- Thanks to [Caio Liberali](https://github.com/caioliberali) for the original Unreal Engine [Pull Request](https://github.com/EpicGames/UnrealEngine/pull/7436) that inspired this project.
- [This tutorial](https://lxjk.github.io/2019/10/01/How-to-Make-Tools-in-U-E.html) by Xun (Eric) Zhang is a great resource for creating editor (not runtime) tools.
- This blog post on [custom project settings](http://www.mov-eax-rgb.net/blog/custom-settings-object/) is short, but it saved me when I got stuck.
- Huge thanks to the Unreal team! I had only been learning Unreal for a little over a month when I first wrote this. Epic's training material is outstanding, and the sheer amount of material available, from Epic and from end users, artists, and programmers, is unlike anything I've ever experienced in the industry.

Project Link:  [ScooterUtils](https://github.com/ScottKirvan/ScooterUtils)  
[CHANGELOG](notes/CHANGELOG.md)  
[TODO](notes/TODO.md)
