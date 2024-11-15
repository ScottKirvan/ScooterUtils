OL2Cal - TODO
====
Just a spot to keep track of what's being worked on, what may get worked on next, and  what's been done.  

This is not a formal roadmap, or even a prioritized list, just a shorthand to help keep things on track.

TODO
----
- [ ] get project package'able for the unreal marketplace
- [ ] update documentation with better installation instructions since UE5 is more restrictive on where you install plugins.  See issue [#14](https://github.com/ScottKirvan/ScooterUtils/issues/14)
- [ ] Look into persisting some viewport settings [#13](https://github.com/ScottKirvan/ScooterUtils/issues/13) [#12](https://github.com/ScottKirvan/ScooterUtils/issues/12) [#11](https://github.com/ScottKirvan/ScooterUtils/issues/11)

In Progress
-----------
- [ ] WIP (stuck) on making fps persistent and ran into some engine startup timing issues.  Detailed in [#3](https://github.com/ScottKirvan/ScooterUtils/issues/3)

Done ✓
------
- [x] .

Not Gonna Do ✓
------
- [x] F11/Immersive mode doesn't work properly with application set (window size is wrong) [#2](https://github.com/ScottKirvan/ScooterUtils/issues/2)
    - This is a Slate issue and can be duplicated using Widget Reflector
    - *Update:* as of 5.4, the application scale setting has been added to the engine under `Edit` > `Editor Preferences...` > `General - Appearance` > `User Interface` > `Application Scale`, so I'm removing the functionality in 5.5+ to avoid conflicting behaviors.  This "*bug*" is still present, so even Epic didn't think it was all that important.