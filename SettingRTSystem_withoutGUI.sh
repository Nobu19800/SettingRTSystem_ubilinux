#!/bin/sh
cd `dirname $0`
python startNamingService.py
sh runManager.sh&
sh rtcConfSet.sh&
