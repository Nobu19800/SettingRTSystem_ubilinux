#!/bin/sh
cd `dirname $0`
sh rtcdControl/BuildRelease.sh
sh rtcd_p/BuildRelease.sh
sh ECandStateSharedComposite/BuildRelease.sh
