@echo off
cd /d "%~dp0"
"C:\Program Files\Microsoft Visual Studio\18\Professional\MSBuild\Current\Bin\MSBuild.exe" "%~dp0Project3.sln" /p:Configuration=Debug /p:Platform=x64 /v:m
if errorlevel 1 pause & exit /b 1
cd /d "%~dp0Project3"
"%~dp0x64\Debug\Project3.exe"
pause
