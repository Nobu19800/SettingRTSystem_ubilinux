#!/bin/env python
# -*- encoding: utf-8 -*-

##
#   @file MTabWidget.py
#   @brief タブの基本ウィジェット



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

from ManagerControl import ManagerControl

##
# @class MTabWidget
# @brief タブの基本ウィジェット
#
class MTabWidget(QtGui.QWidget):
    ##
    # @brief コンストラクタ
    # @param self 
    # @param mgrc マネージャ操作オブジェクト
    # @param parent 親ウィジェット
    def __init__(self, mgrc, parent=None):
        super(MTabWidget, self).__init__(parent)
        self.mgrc = mgrc
        self.mainLayout = QtGui.QHBoxLayout()

        self.setLayout(self.mainLayout)

        self.WidList = {}
        self.widNum = 0

        self.subLayouts = [QtGui.QVBoxLayout()]
        self.mainLayout.addLayout(self.subLayouts[-1])

    ##
    # @brief ウィジェット追加
    # @param self 
    # @param wid 追加するウィジェット
    # @param name 名前
    # @param label 表示する文字列
    # @return 追加したウィジェットの情報(Widget:ウィジェット、Layout：レイアウト、Type：ウィジェットの種類)
    def apendWidget(self, wid, name, label):
        #widget = QtGui.QWidget(self)
        widget = QtGui.QGroupBox(label)
        layout = QtGui.QVBoxLayout()
        widget.setLayout(layout)
        #Lb = QtGui.QLabel(label)
        
        
        #layout.addWidget(Lb)
        layout.addWidget(wid)

        self.widNum += 1
        if self.widNum%7 == 0:
            self.subLayouts.append(QtGui.QVBoxLayout())
            self.mainLayout.addLayout(self.subLayouts[-1])
            
        self.subLayouts[-1].addWidget(widget)

        self.subLayouts[-1].addStretch()

        self.WidList[name] = {"Widget":wid,"Layout":layout}

        return self.WidList[name]
        
    ##
    # @brief コンボボックス追加
    # @param self 
    # @param name 名前
    # @param label 表示する文字列
    # @param value 選択可能な値のリスト(rtc.confで設定された値)
    # @param ls 選択可能な値のリスト(デフォルトで選択可能)
    # @param default デフォルト値
    # @return 追加したウィジェットの情報(Widget:ウィジェット、Layout：レイアウト、Type：ウィジェットの種類)
    def addCombox(self, name, label, value, ls, default):
        wid = QtGui.QComboBox()
        for l in ls:
            if l != "":
                wid.addItem(l)

        if name == "manager.modules.load_path" or name == "manager.modules.preload" or name == "manager.components.precreate" or name == "corba.endpoints":
            for l in value:
                if l != "":
                    wid.addItem(l)

        
        if len(value) != 0:
            if value[0] != "":
                wid.setCurrentIndex(wid.findText(value[0]))
            else:
                wid.setCurrentIndex(wid.findText(default))
        else:
            wid.setCurrentIndex(wid.findText(default))

        wl = self.apendWidget(wid, name, label)
        wl["Type"] = ManagerControl.Combox
        
        return wl

        
    ##
    # @brief テキストコンボボックス追加
    # @param self 
    # @param name 名前
    # @param label 表示する文字列
    # @param value 選択可能な値のリスト(設定ファイルから読み込んだ値)
    # @param ls 選択可能な値のリスト(デフォルトで選択可能)
    # @param default デフォルト値
    # @return 追加したウィジェットの情報(Widget:ウィジェット、Layout：レイアウト、Type：ウィジェットの種類)
    def addTextCombox(self, name, label, value, ls, default):
        wl = self.addCombox(name, label, value, ls, default)
        wl["Widget"].setLineEdit(QtGui.QLineEdit())
        if len(value) == 0:
            wl["Widget"].lineEdit().setText(default)
        elif value[0] == "":
            wl["Widget"].lineEdit().setText(default)
        else:
            wl["Widget"].lineEdit().setText(value[0])

        
        wl["Type"] = ManagerControl.TextCombox
        
        return wl
        

    ##
    # @brief スピンボックス追加
    # @param self 
    # @param name 名前
    # @param label 表示する文字列
    # @param value 設定ファイルから読み込んだ値
    # @param default デフォルト値
    # @return 追加したウィジェットの情報(Widget:ウィジェット、Layout：レイアウト、Type：ウィジェットの種類)
    def addSpinBox(self, name, label, value, default):
        wid = QtGui.QSpinBox()
        wid.setRange(0,10000)
        if len(value) == 0:
            wid.setValue(int(default))
        elif value[0] == "":
            wid.setValue(int(default))
        else:
            wid.setValue(int(value[0]))

        wl = self.apendWidget(wid, name, label)
        wl["Type"] = ManagerControl.SpinBox
        
        return wl

        
    ##
    # @brief スピンボックス(浮動小数点型)追加
    # @param self 
    # @param name 名前
    # @param label 表示する文字列
    # @param value 設定ファイルから読み込んだ値
    # @param default デフォルト値
    # @return 追加したウィジェットの情報(Widget:ウィジェット、Layout：レイアウト、Type：ウィジェットの種類)
    def addDoubleSpinBox(self, name, label, value, default):
        wid = QtGui.QDoubleSpinBox()
        wid.setRange(0,10000)
        if len(value) == 0:
            wid.setValue(float(default))
        elif value[0] == "":
            wid.setValue(float(default))
        else:
            wid.setValue(float(value[0]))

        wl = self.apendWidget(wid, name, label)
        wl["Type"] = ManagerControl.DoubleSpinBox
        
        return wl


    ##
    # @brief テキストボックス追加
    # @param self 
    # @param name 名前
    # @param label 表示する文字列
    # @param value 設定ファイルから読み込んだ値
    # @param default デフォルト値
    # @return 追加したウィジェットの情報(Widget:ウィジェット、Layout：レイアウト、Type：ウィジェットの種類)
    def addTextBox(self, name, label, value, default):
        wid = QtGui.QLineEdit()
        if len(value) == 0:
            wid.setText(default)
        elif value[0] == "":
            wid.setText(default)
        else:
            wid.setText(value[0])

        wl = self.apendWidget(wid, name, label)
        wl["Type"] = ManagerControl.TextBox
        
        return wl

    ##
    # @brief 設定情報からウィジェットを追加
    # @param self 
    # @param tabName タブの名前
    def setGUI(self, tabName):
        for j in self.mgrc.confList:
            name = j["name"].split(".")[0]
            if name == tabName:
                if j["type"] == ManagerControl.Combox:
                    self.addCombox(j["name"],j["label"],j["value"],j["list"],j["default"])
                elif j["type"] == ManagerControl.TextCombox:
                    self.addTextCombox(j["name"],j["label"],j["value"],j["list"],j["default"])
                elif j["type"] == ManagerControl.SpinBox:
                    self.addSpinBox(j["name"],j["label"],j["value"],j["default"])
                elif j["type"] == ManagerControl.DoubleSpinBox:
                    self.addDoubleSpinBox(j["name"],j["label"],j["value"],j["default"])
                elif j["type"] == ManagerControl.TextBox:
                    self.addTextBox(j["name"],j["label"],j["value"],j["default"])

    ##
    # @brief メッセージボックスボックス表示
    # @param self 
    # @param mes 表示する文字列
    def mesBox(self, mes):
        msgbox = QtGui.QMessageBox( self )
        msgbox.setText( mes )
        msgbox.setModal( True )
        ret = msgbox.exec_()
