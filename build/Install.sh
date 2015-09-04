#!/bin/sh
cd `dirname $0`
sh rtcdControl/Install.sh
sh rtcd_p/Install.sh
sh ECandStateSharedComposite/Install.sh
