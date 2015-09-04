#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

##
#   @file startNamingService.py
#   @brief ネームサービス起動

import time

import sys,os,platform
import subprocess
#import rtctree.tree
from omniORB import CORBA, PortableServer
from OpenRTM_aist import CorbaNaming


##
# @brief メイン関数
def main():

    try:
        orb = CORBA.ORB_init(sys.argv, CORBA.ORB_ID)
        namingserver = CorbaNaming(orb, "localhost")
    except:
        if os.name == 'posix':
            subprocess.Popen("rtm-naming&".split(" "),shell=True)
        elif os.name == 'nt':
            subprocess.Popen("start rtm-naming", shell=True)

        time.sleep(3)
    

if __name__ == "__main__":
    main()