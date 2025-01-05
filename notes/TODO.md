ScooterUtils - TODO
====
Just a spot to keep track of what's being worked on, what may get worked on next, and  what's been done.  

This is not a formal roadmap, or even a prioritized list, just a shorthand to help keep things on track.

TODO
----
- [ ] Look into persisting some viewport settings [#13](https://github.com/ScottKirvan/ScooterUtils/issues/13) [#12](https://github.com/ScottKirvan/ScooterUtils/issues/12) [#11](https://github.com/ScottKirvan/ScooterUtils/issues/11)
- [ ] Doublecheck TOC in all readmes
- [ ] check the _layout css - I think I have to modify this to work better/differently on mobile (low priority - no one is using unreal engine on mobile, so it's reasonable to consider this an edge use)

In Progress
-----------
- [ ] get project package'able for the unreal marketplace/fab
	- [ ] delete unused artifact, like pictures in resources folder
	- [x] plugin manifest?
	- [ ] user docs
		- [ ] change formatting to epic's documentation style
		- [ ] update TOC
		- [ ] 
	- [ ] thumbnail image 1920x1080 < 3MB
	- [ ] media gallery image(s) 1920x1080 < 3MB
	- [ ] come up with a naming convention for the release binaries
		- [ ] platform, version, ue version - ScooterUtils_Win64_UE_5.5_v1.0.0.zip
		- [ ] maybe put together a script that can pull and build multiple versions so these aren't maintained by hand
			- [ ] for each platform:
				- [ ] build
				- [ ] delete artifacts
				- [ ] zip
				- [ ] upload
	- [ ] upload package(s) to bluehost
	- [ ] upload images to fab and add product files
	- [ ] fab creator profile wants a website... *sigh*... I have to do something, I guess :-)
	- [ ] build a decent sized logo so I can reuse this thing - haha :-)
	- [ ] *NOTE* Although you need to test compilation of your plugin by building it, please do not send the output of this packaged version of the plugin to the Marketplace team, as we're also going to compile your plugin on our build farm. We prefer to only receive the source folders and files of your plugin (such as Config, Content, Resources, Source folders and the .uplugin), not any folders generated from the packaging process (such as Binaries, Build, Intermediate, or Saved).
	- [x] add copyright notice to all cpp/h files: ie. // Copyright 2020 MyCompany Inc. All Rights Reserved.
	- [ ] can I retarget this stuff off of scottkirvan.com and over to skvfx.com?
- [x] add binaries to the github releases - use unreal's "package" function to build them.  For simplicity, I may keep github source-only, and just host binaries on fab.
- [ ] Update the image in the user docs under "enable the plugin" - the image is from before I changed the category from Utility to Editor 

Done ✓
------
- [x] maybe what I've got as "features" in the readme should be more like simple descriptions of what things do, not what they are.
- [x] I've got the version number automation all working in the PleaseReleaseTest project - roll all that code into here now.
- [x] update the installation docs with something clearer - I like how BrightEye does it
- [x] break documentation up so there's github savvy docs and user docs
- [x] WIP (stuck) on making fps persistent and ran into some engine startup timing issues.  Detailed in [#3](https://github.com/ScottKirvan/ScooterUtils/issues/3)
- [x] reimplement the **Persistent Editor Scale** settings - Epics implementation is project based, not an editor setting. fml.
- [x] update documentation with better engine installation instructions since UE5 is more restrictive on where you install plugins.  See issue [#14](https://github.com/ScottKirvan/ScooterUtils/issues/14)

Not Gonna Do ✓
------
- [x] F11/Immersive mode doesn't work properly with application set (window size is wrong) [#2](https://github.com/ScottKirvan/ScooterUtils/issues/2)
    - This is a Slate issue and can be duplicated using Widget Reflector
    - *Update:* as of 5.4, the application scale setting has been added to the engine under `Edit` > `Editor Preferences...` > `General - Appearance` > `User Interface` > `Application Scale`, so I'm removing the functionality in 5.5+ to avoid conflicting behaviors.  This "*bug*" is still present, so even Epic didn't think it was all that important.
    - -*Update Update:* Epic's implementation is per-project, not global, so this functionality is being re-introduced.