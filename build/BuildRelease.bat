cd /d %~dp0
cmd /c rtcdControl\BuildRelease.bat
cmd /c rtcd_p\BuildRelease.bat
cmd /c ECandStateSharedComposite\BuildRelease.bat
