#!/bin/sh
cd `dirname $0`
sh rtcdControl/BuildDebug.sh
sh rtcd_p/BuildDebug.sh
sh ECandStateSharedComposite/BuildDebug.sh
