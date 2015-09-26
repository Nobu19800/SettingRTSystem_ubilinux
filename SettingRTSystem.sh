#!/bin/sh
cd `dirname $0`
python startNamingService.py
sh runManager.sh&
cd workspace
python ../SettingRTSystem.py -f rtc.conf
