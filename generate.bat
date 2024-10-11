@echo off
cd Premake
premake5.exe --file=bomberman.lua --fatal vs2022
cd ..
powershell "$s=(New-Object -COM WScript.Shell).CreateShortcut('%~dp0\Bomberman.lnk');$s.TargetPath='%~dp0\.gen\prj\Bomberman.sln';$s.Save()"
@echo Done