#!/bin/sh
cd `dirname $0`
cmake ./ -G "CodeBlocks - Unix Makefiles"
cp ./RTC.xml RTC.xml
