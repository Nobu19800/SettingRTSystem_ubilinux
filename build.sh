#!/bin/sh
cd `dirname $0`



sh build/Unix_Makefiles_Genarate.sh
sh build/BuildRelease.sh
sh build/CopyFile.sh