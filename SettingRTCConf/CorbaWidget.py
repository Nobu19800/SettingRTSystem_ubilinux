#!/bin/env python
# -*- encoding: utf-8 -*-

##
#   @file CorbaWidget.py
#   @brief CORBA関連設定ウインドウ



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
# @class CorbaWidget
# @brief CORBA関連設定ウィジェット
#
class CorbaWidget(MTabWidget):
    ##
    # @brief コンストラクタ
    # @param self 
    # @param mgrc マネージャ操作オブジェクト
    # @param parent 親ウィジェット
    def __init__(self, mgrc, parent=None):
        MTabWidget.__init__(self, mgrc, parent)
        self.setGUI("corba")

        self.addEndpointsButton = QtGui.QPushButton(u"エンドポイント追加")
        self.WidList["corba.endpoints"]["Layout"].addWidget(self.addEndpointsButton)
        self.addEndpointsButton.clicked.connect(self.addEndpointsSlot)

        self.delEndpointsButton = QtGui.QPushButton(u"エンドポイント削除")
        self.WidList["corba.endpoints"]["Layout"].addWidget(self.delEndpointsButton)
        self.delEndpointsButton.clicked.connect(self.delEndpointsSlot)

    ##
    # @brief エンドポイント追加ボタンのスロット
    # @param self 
    def addEndpointsSlot(self):
        wid = self.WidList["corba.endpoints"]["Widget"]
        
        if wid.findText(wid.currentText()) == -1:
            s = str(wid.currentText().toLocal8Bit())
            if s != "":
                wid.addItem(s)
        
    ##
    # @brief エンドポイント削除ボタンのスロット
    # @param self 
    def delEndpointsSlot(self):
        wid = self.WidList["corba.endpoints"]["Widget"]
        wid.removeItem(wid.findText(wid.currentText()))
