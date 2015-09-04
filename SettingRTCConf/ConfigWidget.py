#!/bin/env python
# -*- encoding: utf-8 -*-

##
#   @file ConfigWidget.py
#   @brief 一般的な設定をするためのウインドウ



import thread


import optparse
import sys,os,platform
import re
import time
import random
import commands
import math
import imp



import RTC
import OpenRTM_aist

from OpenRTM_aist import CorbaNaming
from OpenRTM_aist import RTObject
from OpenRTM_aist import CorbaConsumer
from omniORB import CORBA
import CosNaming

from PyQt4 import QtCore, QtGui


from MTabWidget import MTabWidget
from ManagerControl import ManagerControl

##
# @class ConfigWidget
# @brief 一般的な設定をするためのウィジェット
#
class ConfigWidget(MTabWidget):
    ##
    # @brief コンストラクタ
    # @param self 
    # @param mgrc マネージャ操作オブジェクト
    # @param parent 親ウィジェット
    def __init__(self, mgrc, parent=None):
        MTabWidget.__init__(self, mgrc, parent)
        self.setGUI("config")
