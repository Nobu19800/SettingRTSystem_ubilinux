#!/bin/env python
# -*- encoding: utf-8 -*-

##
#   @file .py
#   @brief 



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

from SettingRTCConf.ConfigWidget import ConfigWidget
from SettingRTCConf.CorbaWidget import CorbaWidget
from SettingRTCConf.ExecCxtWidget import ExecCxtWidget
from SettingRTCConf.LoggerWidget import LoggerWidget
from SettingRTCWindow.ManagerControl import ManagerControl
from SettingRTCConf.ManagerWidget import ManagerWidget
from SettingRTCConf.NamingWidget import NamingWidget
from SettingRTCConf.TimerWidget import TimerWidget


class TabWidget(QtGui.QTabWidget):
    def __init__(self, mgrc, language="Python", parent=None):
        super(TabWidget, self).__init__(parent)
        self.language = language
        self.mgrc = mgrc
        
        
        self.createTabs()
        

    def createTabs(self):
        self.Tabs = []
        self.ManagerTab = ManagerWidget(self.mgrc,self.language)
        self.addTab(self.ManagerTab, u"マネージャ")
        self.Tabs.append(self.ManagerTab)
        self.CorbaTab = CorbaWidget(self.mgrc)
	self.addTab(self.CorbaTab, u"CORBA")
	self.Tabs.append(self.CorbaTab)
	self.ConfigTab = ConfigWidget(self.mgrc)
	self.addTab(self.ConfigTab, u"一般的")
	self.Tabs.append(self.ConfigTab)
	self.NamingTab = NamingWidget(self.mgrc)
	self.addTab(self.NamingTab, u"ネームサービス")
	self.Tabs.append(self.NamingTab)
	self.LoggerTab = LoggerWidget(self.mgrc)
	self.addTab(self.LoggerTab, u"ロガー")
	self.Tabs.append(self.LoggerTab)
	self.TimerTab = TimerWidget(self.mgrc)
	self.addTab(self.TimerTab, u"タイマ")
	self.Tabs.append(self.TimerTab)
	self.ExecCxtTab = ExecCxtWidget(self.mgrc, self.ManagerTab,self.language)
	self.addTab(self.ExecCxtTab, u"実行コンテキスト")
	self.Tabs.append(self.ExecCxtTab)

    def getConfData(self):
        datas = []
        for t in self.Tabs:
            for k,j in t.WidList.items():
                if k.split(".")[-1] != "sub":
                    d = {}
                    d["name"] = k
                    d["value"] = ""
                    if j["Type"] == ManagerControl.TextBox:
                        d["value"] = str(j["Widget"].text().toLocal8Bit())
                    elif j["Type"] == ManagerControl.TextCombox or j["Type"] == ManagerControl.Combox:
                        
                        
                        if k == "manager.modules.load_path" or k == "manager.modules.preload" or k == "manager.components.precreate" or k == "corba.endpoints":
                            for c in range(0, j["Widget"].count()):
                                d["value"] += str(j["Widget"].itemText(c).toLocal8Bit()).replace("\\","/")
                                if c < j["Widget"].count()-1:
                                    d["value"] += ","
                        else:
                            d["value"] = str(j["Widget"].currentText().toLocal8Bit())
                    elif j["Type"] == ManagerControl.SpinBox or j["Type"] == ManagerControl.DoubleSpinBox:
                        d["value"] = str(j["Widget"].text().toLocal8Bit())
                    datas.append(d)
            
        return datas
                
        
