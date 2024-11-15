> **Note**  
> All notable changes to this project will be documented in this file.  
> This project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html). 
> The format of this file is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

[Unreleased]
============
- ***Added***
    - Icon for the plugin prefs dialog
- ***Refactored***
    - massive changes to README.md
- ***Removed*** 
    - removed *Screen Real Estate* - historically found in the **Editor Preferences** under **Plugins/Scooter Utilities** - **[UPDATE]** I just found out that Epic's implementation of Application Scale is scoped to the project and isn't actually an editor setting - I'm going to have to roll all this code back in and do some thinking on how to deal with the potential weirdness/conflict of having the same setting in two places (one of which will be ignored for now)

[1.1.0] - 2023-10-17
--------------------
- ***Added***
    - [enhancement] Menu item:  **File > Show Project in Explorer**

- ***Fixed***
    - [update] Depricated API. FEditorStyle::GetStyleSetName() -> AppStyle::GetAppStyleSetName()

[Released]
==========

[1.0.1] - 2023-10-17
--------------------
- ***Added***
    - VERSION.md, CHANGELOG.md

- ***Refactored***
    - moving files and cleaning up directory structures

----------------------------------------------------------------------

### Types of changes
- ***Added*** - for new features.   
- ***Changed*** - for changes in existing functionality.  
- ***Depricated*** - for soon-to-be removed features.  
- ***Removed*** - for removed features.  
- ***Fixed*** - for any bug fixes.  
- ***Refactored*** - no functional changes, just cleanup or reorganizing.  
- ***Security*** - in case of vulnerabilities.  