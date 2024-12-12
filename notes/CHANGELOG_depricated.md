> **Note**  
> All notable changes to this project will be documented in this file.  
> This project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html). 
> The format of this file is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

[Unreleased]
============
[Released]
==========

[1.2.0] - 2024-12-12
--------------------
- ***Added***
    - Icon for the plugin prefs dialog.
    - persistent *Show FPS* viewport setting.
    - a checkbox for *Persistent Editor Scale* - this now overrides the setting in **Editor Preferences/Appearance** (UE 5.4+)
- ***Refactored***
    - massive changes to README.md
    - Application scale was reworked due to Epic's implementation of this in Editor Prefs - **ScooterUtil**'s setting is global to all editor instances, not tied to a project

[1.1.0] - 2023-10-17
--------------------
- ***Added***
    - [enhancement] Menu item:  **File > Show Project in Explorer**

- ***Fixed***
    - [update] Depricated API. FEditorStyle::GetStyleSetName() -> AppStyle::GetAppStyleSetName()

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