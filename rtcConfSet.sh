#!/bin/sh
PATH=/bin:/usr/bin:/sbin:/usr/sbin:/usr/local/bin
cd `dirname $0`

cd workspace
python ../rtcConfSet/rtcConfSet.py -f rtc.conf
