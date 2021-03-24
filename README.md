# UE4-ScooterUtils
 A UE4 editor plugin which contains multiple miscellaneous artist/utilities utilities for Unreal Engine.

Plugin currently contains:
- *Scooter Utilities: Screen Real Estate settings* - can be found in *Editor Preferences* under *Plugins/Scooter Utilities*
- *Scooter Utilities: Maximum FPS* - can be found in *Editor Preferences* under *Plugins/Scooter Utilities*

## Getting up and running

The persistent editor Settings are stored in this file:  
```C:\Users\<username>\AppData\Local\UnrealEngine\<EngineVersion>\Saved\Config\Windows\EditorSettings.ini```

### Screen Real Estate Setting
Once the plugin is built and loaded, you can find the Screen Real Estate setting by going to **Edit**, selecting **Editor Preferences**, and then selecting **Scooter Utilities** under the **Plugins** sub-heading in the preferences menu.

The *Persistant Editor Scale* value is a percentage relative to the default screen size of elements like 
fonts, buttons, and other widgets in the Unreal Engine UI.  I like to work with 
all the fluff scaled down to about 80% of what's considered "normal," so I set the
Persistant Editor Scale to *0.8*.

This same setting is available in the Unreal Editor by going to **Window**, selecting **Developer Tools**, **Widget Reflector**, and setting the *Application Scale*, however, the *Widget Reflector* method doesn't stick -- you have to set it everytime you restart **Unreal Engine**.  The Scooter Utility writes this value to one of your Config files, so you don't have to constantly re-set it.

### FPS Settings

The *Max FPS* setting can be found by going to **Edit**, selecting **Editor Preferences**, and then selecting **Scooter Utilities** under the **Plugins** sub-heading in the preferences menu.

The *Max FPS* overrides the console variable setting (t.MaxFPS) and sets the engine's maximum frame rate.  

Turn off **Smooth Frame Rate** and **Used Fixed Frame Rate** under **Edit|Project Preferences|General Settings|Framerate** if you need
to unclamp the system and run it as freewheeling as possible. (These are off by default)


### Installation
This is kind of standard practice for GitHub Unreal plugins; it goes like this:
1. Create a new Unreal project.
1. Create a ```Plugins``` folder in your project directory.
1. Clone the GitHub repository (or grab and unzip the project) into your ```Plugins``` folder.
1. Launch Unreal; You should be prompted to build the plugin.
2. Optional:  Use or convert your unreal project to a C++ project so that you can edit and build the code outside of Unreal.

## About - for Developers

This was my first plugin in Unreal Engine.  It was inspired by a [declined Epic Games Github Pull Request](https://github.com/EpicGames/UnrealEngine/pull/7436).  It's very simple and direct -- I wanted to understand the bare bones of the system, so there's not a lot of bells-and-whistles in this code.

The plugin has two components, an ``IModuleInterface`` derived ``FScooterUtilsModule``, which bootstraps and provides basic life-support to the plugin, and an ``IObject`` derived ``IScooterUtilsSettings`` object which is the system-aware component that works directly
with Unreal's ``ISettingsModule`` and ``FSlateApplication``'s ``ApplicationScale``.  The *Module* registers the callbacks and the *IObject* manages the data and processes the callbacks.

First impressions, being new to the system:  The system itself -- the thin veil between the editor and the code, between the *UnrealBuildTool* and the Artist -- brilliant.  Conceptually, there is a hurdle -- *there is no plugin api.*  You write your code to the entire surface of the application and all it's various plugins.  -- and getting build dependencies figured is a very high bar, but those details should be in the background, and once they are, it takes very little hard coding to pull together the pieces you need to accomplish what you're after.

## Supported Platforms

This plug-in was developed and built against **Unreal Engine 4.25**. It should work on all
platforms.  It was also tested on 4.26 Preview 6.

## Dependencies

This plugin is source code only - I'm not currently providing binaries.  If you're looking for binaires for the 4.26 windows version, contact me and I'll try get you a build.  If you need an older build or another platform, you're going to have to get in touch with someone that can help you (See the Support/Contacts section below).

The source requires Visual Studio (I used the free 2019 community version) and either an Unreal C++ code (rather than blueprint) project or the full
Unreal Engine 4 source code from GitHub (just use the project-based approach, it's so easy). 
Building it inside a project is dead simple.  Clone the repository into the *Plugins* directory of your Unreal C++ based project. Go to **File**, and select **Update Visual Studio Project**.  From there, the plugin should be buildable, and once compiled, can be left in your project directory for the project you're working on, or copied into your Engine's main *Plugins* folder so it's available to all your future editing sessions.  

If you are new to programming in UE4,
please see the official [Programming Guide](https://docs.unrealengine.com/en-US/Programming/Plugins/index.html)! 
The plugin development workflow is really very impressive, and if you've ever developed plugins for other applications, you should check it out.  

## Contributions

- Please [file an issue](https://github.com/ScottKirvan/UE4-ScooterUtils/issues),
or grab a fork, hack away, and submit [pull requests](https://github.com/ScottKirvan/UE4-ScooterUtils/pulls?q=is%3Aopen+is%3Apr).
- Contact me at [linkedin.com/in/scottkirvan/](https://www.linkedin.com/in/scottkirvan/)
- You can also contact me at my [discord](https://discord.gg/TSKHvVFYxB) server, I'm cptvideo.

To locate other developers, I recommend the **# cpp** and **# engine-source** channels on the **Unreal Slackers** Discord server.

## References / Inspirations / Credits
- sign into the Unreal Engine [Learning & Support](https://www.unrealengine.com/en-US/learn) area and take the *Best Practices for Creating and Using Plugins* course - it's great!
- This blog post on [custom project settings](http://www.mov-eax-rgb.net/blog/custom-settings-object/) is short, but it saved me when I got stuck
- The Unreal Team!  I had only been learning Unreal for a little over a month when I first wrote this.  I am so totally blown away.  Epic's training material is outstanding - The sheer amount of material available, directly from Unreal, and being produced by end users, artists, and programmers is unlike anything I've ever experienced in the industry, and I'm all in.
- Again, thanks to [Caio Liberali](https://github.com/caioliberali) for the original [Pull Request](https://github.com/EpicGames/UnrealEngine/p) on Github.  I had been hacking around in the engine source trying to accomplish the same thing when the Pull Request came in.  Had it not been declined, I probably never would have said, "hey, why not make it a plugin?"

Updated: *March 24, 2021*
