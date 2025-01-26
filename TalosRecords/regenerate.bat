@echo off
:: Delete specified folders
echo Removing .vs && rmdir /s /q .vs
echo Removing .idea && rmdir /s /q .idea
echo Removing Binaries && rmdir /s /q Binaries
echo Removing DerivedDataCache && rmdir /s /q DerivedDataCache
echo Removing Intermediate && rmdir /s /q Intermediate
echo Removing Saved && rmdir /s /q Saved

:: Delete specified files
echo Removing .vsconfig && del /q .vsconfig
echo Removing TalosRecords.sln && del /q TalosRecords.sln

:: Regenerate Visual Studio project files
echo Regenerating Visual Studio project files && call "C:\Program Files\Epic Games\UE_5.5\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe" -projectfiles -project="%~dp0TalosRecords.uproject" -game -rocket -progress

:: Keep the console open for easier debugging
pause