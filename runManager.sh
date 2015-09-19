#!/bin/sh
PATH=/bin:/usr/bin:/sbin:/usr/sbin:/usr/local/bin
cd `dirname $0`
cd workspace
python ../Manager/Python/rtcd_p.py -f ../Manager/Python/rtc.conf
