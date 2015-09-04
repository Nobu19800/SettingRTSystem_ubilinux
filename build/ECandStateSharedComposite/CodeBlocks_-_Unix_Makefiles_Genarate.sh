#!/bin/sh
cd `dirname $0`
cmake ../../Composite/ECandStateSharedComposite/ -G "CodeBlocks - Unix Makefiles"
cp ../../Composite/ECandStateSharedComposite/RTC.xml RTC.xml
