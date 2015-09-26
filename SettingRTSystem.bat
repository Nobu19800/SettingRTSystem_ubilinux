cd /d %~dp0
python startNamingService.py
start runManager.bat
cd workspace
..\DLL\SettingRTSystem -f rtc.conf