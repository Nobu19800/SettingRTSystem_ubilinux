#!/usr/bin/env python
# -*- Python -*-
# -*- coding: utf-8 -*-

import time

import sys,os,platform
import subprocess
#import rtctree.tree
from omniORB import CORBA, PortableServer
from OpenRTM_aist import CorbaNaming




try:
    orb = CORBA.ORB_init(sys.argv, CORBA.ORB_ID)
    namingserver = CorbaNaming(orb, "localhost")
except:
    if os.name == 'posix':
        subprocess.Popen("rtm-naming&".split(" "),shell=True)
    elif os.name == 'nt':
        #print "start python " + '"' + os.path.join(os.environ["RTM_ROOT"],"bin/rtm-naming.py").replace("/","\\") + '"'
        subprocess.Popen("start python " + '"' + os.path.join(os.environ["RTM_ROOT"],"bin/rtm-naming.py").replace("/","\\") + '"', shell=True)
        #subprocess.Popen("start rtm-naming", shell=True)

    time.sleep(3)
    

