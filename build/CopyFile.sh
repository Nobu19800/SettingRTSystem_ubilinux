#!/bin/sh
PATH=/bin:/usr/bin:/sbin:/usr/sbin:/usr/local/bin
cd `dirname $0`


cp rtcd_p/rtcd_p ../Manager/Cpp/rtcd_p/rtcd_p


cp rtcdControl/src/rtcdControlComp ../rtcdControl/src/rtcdControlComp


cp ECandStateSharedComposite/src/ECandStateSharedComposite.so ../Composite/ECandStateSharedComposite/src/ECandStateSharedComposite.so
