set ENGINEDIR=C:\bin\Epic Games\UE_5.5
set PROJECTDIR=D:\3\UE\5.5\dev\ScooterUtils_Base
set BUILDDIR=D:\build

pushd "%ENGINEDIR%"
call Engine\Build\BatchFiles\RunUAT.bat BuildPlugin ^
-Plugin="%PROJECTDIR%\Plugins\ScooterUtils\ScooterUtils.uplugin" ^
-Package="%BUILDDIR%\ScooterUtils" ^
-Rocket
popd



