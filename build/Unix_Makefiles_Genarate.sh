#!/bin/sh
cd `dirname $0`
sh rtcdControl/Unix_Makefiles_Genarate.sh
sh rtcd_p/Unix_Makefiles_Genarate.sh
sh ECandStateSharedComposite/Unix_Makefiles_Genarate.sh
