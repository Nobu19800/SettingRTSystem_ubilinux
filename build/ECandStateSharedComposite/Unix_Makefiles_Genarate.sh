#!/bin/sh
cd `dirname $0`
cmake ../../Composite/ECandStateSharedComposite/ -G "Unix Makefiles"
cp ../../Composite/ECandStateSharedComposite/RTC.xml RTC.xml
