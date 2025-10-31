@echo off
REM Generate packaged plugin with precompiled binaries for distribution
REM This builds the plugin for all supported platforms: Win64, Mac, Linux, Android
REM
REM This script can be run from anywhere - it uses relative paths based on its own location

echo.
echo ================================================================================
echo                        SCOOTER UTILS - PLUGIN BUILD
echo ================================================================================
echo.

REM Get the directory where this batch file is located
set SCRIPT_DIR=%~dp0

REM Calculate project root (3 levels up from tools/)
for %%I in ("%SCRIPT_DIR%..\..\..\") do set PROJECT_ROOT=%%~fI

REM Set the paths
set UE_ENGINE_PATH=C:\bin\Epic Games\UE_5.4\Engine
set PLUGIN_PATH=%SCRIPT_DIR%..\ScooterUtils.uplugin
set OUTPUT_PATH=%PROJECT_ROOT%Shipping\ScooterUtils

echo   Target Platforms : Win64, Mac, Linux, Android
echo   Plugin Path      : %PLUGIN_PATH%
echo   Output Location  : %OUTPUT_PATH%
echo.
echo --------------------------------------------------------------------------------

REM Validate that the engine path exists
if not exist "%UE_ENGINE_PATH%\" (
    echo.
    echo ********************************************************************************
    echo   ERROR: Unreal Engine path not found
    echo ********************************************************************************
    echo.
    echo   Expected path: %UE_ENGINE_PATH%
    echo.
    echo   Please edit this batch file and update the UE_ENGINE_PATH variable
    echo   to point to your Unreal Engine installation.
    echo.
    echo ********************************************************************************
    pause
    exit /b 1
)

REM Validate that RunUAT.bat exists
if not exist "%UE_ENGINE_PATH%\Build\BatchFiles\RunUAT.bat" (
    echo.
    echo ********************************************************************************
    echo   ERROR: RunUAT.bat not found
    echo ********************************************************************************
    echo.
    echo   Expected location: %UE_ENGINE_PATH%\Build\BatchFiles\RunUAT.bat
    echo.
    echo   Please verify your Unreal Engine installation is complete.
    echo.
    echo ********************************************************************************
    pause
    exit /b 1
)

REM Validate that the plugin file exists
if not exist "%PLUGIN_PATH%" (
    echo.
    echo ********************************************************************************
    echo   ERROR: Plugin file not found
    echo ********************************************************************************
    echo.
    echo   Expected location: %PLUGIN_PATH%
    echo.
    echo   Please verify the script is in the correct location.
    echo.
    echo ********************************************************************************
    pause
    exit /b 1
)

echo   [OK] Engine path validated
echo   [OK] Build tools found
echo   [OK] Plugin file found
echo.
echo ================================================================================
echo   Starting build process...
echo ================================================================================
echo.

REM Set the engine plugin installation path
set ENGINE_PLUGIN_PATH=%UE_ENGINE_PATH%\Plugins\Marketplace\ScooterUtils

REM Run the Unreal Automation Tool to build the plugin
call "%UE_ENGINE_PATH%\Build\BatchFiles\RunUAT.bat" BuildPlugin -Plugin="%PLUGIN_PATH%" -Package="%OUTPUT_PATH%" -TargetPlatforms=Win64+Mac+Linux+Android

REM Capture the error level immediately
set BUILD_RESULT=%ERRORLEVEL%

REM Check if the build succeeded
if %BUILD_RESULT% EQU 0 (
    echo.
    echo ================================================================================
    echo                           BUILD SUCCESSFUL
    echo ================================================================================
    echo.
    echo   Cleaning up intermediate files...

    REM Remove the Intermediate folder from the packaged output
    if exist "%OUTPUT_PATH%\Intermediate\" (
        rmdir /S /Q "%OUTPUT_PATH%\Intermediate"
        echo   [OK] Intermediate folder removed
    )

    echo.
    echo --------------------------------------------------------------------------------
    echo   BUILD COMPLETE
    echo --------------------------------------------------------------------------------
    echo.
    echo   Packaged plugin location:
    echo   %OUTPUT_PATH%
    echo.
    echo ================================================================================

    REM Ask user if they want to install to engine
    echo.
    echo ================================================================================
    echo                         INSTALL TO ENGINE?
    echo ================================================================================
    echo.
    echo   Would you like to install this plugin to the Unreal Engine?
    echo.
    echo   Target location:
    echo   %ENGINE_PLUGIN_PATH%
    echo.
    echo   WARNING: This will delete any existing plugin at that location.
    echo.
    echo --------------------------------------------------------------------------------
    set /p INSTALL_TO_ENGINE="  Install to engine? (Y/N): "

    REM Check for Y, y, Yes, yes, etc.
    if /i "%INSTALL_TO_ENGINE:~0,1%"=="Y" (
        echo.
        echo   Installing plugin to engine...
        echo.

        REM Remove existing plugin if it exists
        if exist "%ENGINE_PLUGIN_PATH%\" (
            echo   [1/3] Removing existing plugin...
            rmdir /S /Q "%ENGINE_PLUGIN_PATH%"
        )

        REM Create the Marketplace directory if it doesn't exist
        if not exist "%UE_ENGINE_PATH%\Plugins\Marketplace\" (
            mkdir "%UE_ENGINE_PATH%\Plugins\Marketplace"
        )

        REM Copy the packaged plugin to the engine
        echo   [2/3] Copying plugin files...
        xcopy "%OUTPUT_PATH%" "%ENGINE_PLUGIN_PATH%\" /E /I /Y /Q

        if %ERRORLEVEL% EQU 0 (
            echo   [3/3] Verifying installation...
            echo.
            echo ================================================================================
            echo                        INSTALLATION COMPLETE
            echo ================================================================================
            echo.
            echo   Plugin installed to:
            echo   %ENGINE_PLUGIN_PATH%
            echo.
            echo ================================================================================
        ) else (
            echo.
            echo ********************************************************************************
            echo                         INSTALLATION FAILED
            echo ********************************************************************************
            echo.
            echo   Error code: %ERRORLEVEL%
            echo   You may need to run this script as Administrator.
            echo.
            echo ********************************************************************************
        )
    ) else (
        echo.
        echo   Installation skipped.
        echo.
        echo ================================================================================
    )
) else (
    echo.
    echo ********************************************************************************
    echo                              BUILD FAILED
    echo ********************************************************************************
    echo.
    echo   Error code: %ERRORLEVEL%
    echo   Check the output above for errors.
    echo.
    echo ********************************************************************************
)

echo.
