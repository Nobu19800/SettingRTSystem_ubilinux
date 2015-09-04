#!/bin/sh
cd `dirname $0`
cmake ../../rtcdControl/ -G "CodeBlocks - Unix Makefiles"
cp ../../rtcdControl/RTC.xml RTC.xml
