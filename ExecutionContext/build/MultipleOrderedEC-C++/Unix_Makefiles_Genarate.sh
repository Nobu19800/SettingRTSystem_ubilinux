#!/bin/sh
PATH=/bin:/usr/bin:/sbin:/usr/sbin:/usr/local/bin
cd `dirname $0`
cmake ../../MultipleOrderedEC-C++/ -G "Unix Makefiles"
