#!/bin/sh
PATH=/bin:/usr/bin:/sbin:/usr/sbin:/usr/local/bin
cd `dirname $0`

python Manager/Python/rtcd.py -f Manager/Python/rtc.conf
