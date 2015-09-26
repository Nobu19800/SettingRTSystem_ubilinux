#!/bin/env python
# -*- encoding: utf-8 -*-

##
#   @file SettingRTCConf.py
#   @brief 複合コンポーネント作成支援ツール



import thread



import sys,os,platform
import re
import time
import random
import commands
import math
import imp

import subprocess

import rtctree.tree

import RTC
import OpenRTM_aist

from OpenRTM_aist import CorbaNaming
from OpenRTM_aist import RTObject
from OpenRTM_aist import CorbaConsumer
from omniORB import CORBA
import CosNaming

from PyQt4 import QtCore, QtGui

import SettingRTCWindow.MainWindow


import SettingRTSystem_rc

        
##
# @brief メイン関数
def main():
    #mgrc = ManagerControl("")
    app = QtGui.QApplication([""])
    splash_pix = QtGui.QPixmap(':/images/splash_loading.png')
    splash = QtGui.QSplashScreen(splash_pix, QtCore.Qt.WindowStaysOnTopHint)
    splash.setMask(splash_pix.mask())
    splash.show()
    app.processEvents()
    
    if os.name == 'posix':
        #process_rtcd = subprocess.Popen("python Manager/Python/rtcd.py -f Manager/Python/rtc.conf".split(" "))
        process_confset = subprocess.Popen("sh ../rtcConfSet.sh".split(" "))
        #process_confset = os.system("sh rtcConfSet.sh&")
    elif os.name == 'nt':
        #process_rtcd = subprocess.Popen("python Manager/Python/rtcd.py -f Manager/Python/rtc.conf")
        #process_rtcd = os.system("start python Manager/Python/rtcd.py -f Manager/Python/rtc.conf")
        process_confset = subprocess.Popen("..\\rtcConfSet.bat")
        #process_confset = os.system("start rtcConfSet.bat")
    
    

    
    mainWin = SettingRTCWindow.MainWindow.MainWindow()
    mainWin.show()
    splash.finish(mainWin)
    app.exec_()

    

    if os.name == 'posix':
        subprocess.Popen("python ../exitRTCs.py".split(" "))
    elif os.name == 'nt':
        subprocess.Popen("python ../exitRTCs.py")
        
    
    
    
    
    
    

    
    
    
if __name__ == "__main__":
    main()
