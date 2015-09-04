#!/bin/sh
cd `dirname $0`
sh ExecutionContext/Unix_Makefiles_Genarate.sh
sh ExecutionContext/BuildRelease.sh

