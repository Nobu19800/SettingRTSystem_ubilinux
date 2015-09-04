#!/bin/env python
# -*- encoding: utf-8 -*-

##
#   @file rtcdWidget.py
#   @brief rtcd操作ウインドウ



import thread


import optparse
import sys,os,platform
import traceback
import re
import time
import random
import commands
import math
import imp

import rtctree.tree

import RTC
import OpenRTM_aist

from OpenRTM_aist import CorbaNaming
from OpenRTM_aist import RTObject
from OpenRTM_aist import CorbaConsumer
from omniORB import CORBA
import CosNaming

from PyQt4 import QtCore, QtGui

from SettingRTCConf.MTabWidget import MTabWidget


##
# @class TreeNode
# @brief ツリーノード
#
class TreeNode:
    ##
    # @brief コンストラクタ
    # @param self 
    # @param node ツリーアイテム
    # @param mw メインウインドウオブジェクト
    def __init__(self, node, mw):
        self.node = node
        self.window = mw
    ##
    # @brief 子ノード追加
    # @param self
    # @param child 子ノード
    def appendChild(self, child):
        self.node.addChild(child.node)
    ##
    # @brief 親ノード取得
    # @param self
    # @return 親ノード
    def getParent(self):
        parent = self.node.parent()
        if parent == None:
            return None
        return self.window.getTreeNode(parent)
    ##
    # @brief 子ノード数取得
    # @param self
    # @return 子ノード数
    def getChildCount(self):
        return int(self.node.childCount())
    ##
    # @brief 表示名取得
    # @param self
    # @return 表示名
    def getDisplayValue(self):
        return str(self.node.text(0).toLocal8Bit())

##
# @class rtcdWidget
# @brief RTCD操作ウィジェット
#
class rtcdWidget(MTabWidget):
    ##
    # @brief コンストラクタ
    # @param self 
    # @param parent 親ウィジェット
    def __init__(self, parent=None):
        MTabWidget.__init__(self, None, parent)
        self.parent = parent
        self.addTextBox("textBox", u"IPアドレス", ["localhost"] , "localhost")
        self.addTextBox("filepath", u"ファイル名を直接入力してください", [""] , "")

        self.addFilePathButton = QtGui.QPushButton(u"ファイル名設定")
        self.WidList["filepath"]["Layout"].addWidget(self.addFilePathButton)
        self.addFilePathButton.clicked.connect(self.addFilePathSlot)

        self.addLoadButton = QtGui.QPushButton(u"ファイル読み込み")
        self.WidList["filepath"]["Layout"].addWidget(self.addLoadButton)
        self.addLoadButton.clicked.connect(self.addLoadSlot)


        self.newFileButton = QtGui.QPushButton(u"新規作成")
        self.WidList["filepath"]["Layout"].addWidget(self.newFileButton)
        self.newFileButton.clicked.connect(self.newFileSlot)


        self.saveFileButton = QtGui.QPushButton(u"ファイル保存")
        self.WidList["filepath"]["Layout"].addWidget(self.saveFileButton)
        self.saveFileButton.clicked.connect(self.saveFileSlot)

        self.rtcdButton = QtGui.QPushButton(u"rtcd起動")
        self.WidList["filepath"]["Layout"].addWidget(self.rtcdButton)
        self.rtcdButton.clicked.connect(self.rtcdSlot)

        self.addTextBox("packagepath", u"パッケージ名を直接入力してください", [""] , "")
        self.pkgButton = QtGui.QPushButton(u"パッケージ生成")
        self.WidList["packagepath"]["Layout"].addWidget(self.pkgButton)
        self.pkgButton.clicked.connect(self.pkgSlot)

        
        self.treelayout = QtGui.QVBoxLayout()
        
        self.treeWidget = QtGui.QTreeWidget(self)
        self.treelayout.addWidget(self.treeWidget)
        self.treeWidget.itemClicked.connect(self.treeWidgetSlot)

        self.updateTreeButton = QtGui.QPushButton(u"RTCツリー更新")
        self.treelayout.addWidget(self.updateTreeButton)
        self.updateTreeButton.clicked.connect(self.updateTreeSlot)

        self.addCombox("rtcList", u"システムに加える外部のRTC一覧", [], [] , "")

        self.addRTCButton = QtGui.QPushButton(u"外部のRTCをシステムに追加")
        self.treelayout.addWidget(self.addRTCButton)
        self.addRTCButton.clicked.connect(self.addRTCSlot)

        self.remRTCButton = QtGui.QPushButton(u"外部のRTCをシステムから削除")
        self.treelayout.addWidget(self.remRTCButton)
        self.remRTCButton.clicked.connect(self.remRTCSlot)

        

        self.treeNodeList = []
        self.mainLayout.addLayout(self.treelayout)

        self.compList = []

        self.selItem = None
        #print self.getRTCList("localhost")
        #self.setRTCTree()
        #print self.compList


    ##
    # @brief パッケージ作成ボタンのスロット
    # @param self 
    def pkgSlot(self):
        filename = str(self.WidList["packagepath"]["Widget"].text().toLocal8Bit())
        if filename != "":
            self.parent.createPack(filename)
        else:
            self.mesBox(u"ファイル名を入力してください")

    ##
    # @brief RTC追加ボタンのスロット
    # @param self 
    def addRTCSlot(self):
        
        rtc = self.getSelectRTC()
        if rtc:
            s = ""
            for i in range(0,len(rtc)):
                s += rtc[i]
                if i != 0 and i != len(rtc)-1:
                    s += "/"
            wid = self.WidList["rtcList"]["Widget"]
            if wid.findText(s) == -1:        
                wid.addItem(s)

    ##
    # @brief RTC削除ボタンのスロット
    # @param self 
    def remRTCSlot(self):
        wid = self.WidList["rtcList"]["Widget"]
        wid.removeItem(wid.findText(wid.currentText()))

    ##
    # @brief ツリーのマウスでの操作に対するコールバック
    # @param self
    # @param obj 
    #
    def treeWidgetSlot(self, obj):
        
        self.selItem = self.getTreeNode(obj)
        #print self.getSelectRTC()

    ##
    # @brief ツリーで選択中のRTCを取得
    # @param self
    # @return RTCオブジェクト
    def getSelectRTC(self):
        mlist = []
        node = self.selItem


        if node:
            
            parent = node.getParent()
            
            if parent:
                mlist.insert(0, node.getDisplayValue())
            else:
                return None
            if node.getChildCount() != 0:
                return None
        else:
            return None
        while(True):
            if node:
                node = node.getParent()
                if node:
                    mlist.insert(0, node.getDisplayValue())
                else:
                    break
        for c in self.compList:
            if mlist == c:
                return c
        
        return None
    ##
    # @brief 選択中のツリーアイテム取得
    # @param self 
    # @return 選択中のツリーアイテム
    #
    def getSelection(self):
        return self.selItem

    ##
    # @brief ツリー更新ボタンのスロット
    # @param self
    def updateTreeSlot(self):
        self.setRTCTree()

    ##
    # @brief ツリー初期化
    # @param self
    def setRTCTree(self):
        self.treeWidget.clear()
        self.treeNodeList = []

        tmp = QtGui.QTreeWidgetItem(["/"])
        self.treeWidget.addTopLevelItem(tmp)
        root = TreeNode(tmp, self)
        self.treeNodeList.append(root)

        ipaddress = str(self.WidList["textBox"]["Widget"].text().toLocal8Bit())

        self.compList = self.getRTCList(ipaddress, root)
        
            

        
    ##
    # @brief ツリーノードを取得
    # @param self
    # @param obj オブジェクト
    # @return ツリーノード
    def getTreeNode(self, obj):
        for i in self.treeNodeList:
            if i.node == obj:
                return i
        return None

    ##
    # @brief ツリーノードを作成
    # @param self
    # @param name 名前
    # @param sel 
    # @return ツリーノード
    def createNode(self, name, sel):
        tmp = TreeNode(QtGui.QTreeWidgetItem([name]), self)
        self.treeNodeList.append(tmp)
        return tmp

    ##
    # @brief RTCのリスト、ツリーを作成
    # @param self
    # @param server ネームサーバー
    # @param oParent ツリーノード
    # @return RTCリスト
    def getRTCList(self, server, oParent):
         self.tree = rtctree.tree.RTCTree(servers=server,orb=self.parent.control_comp._manager.getORB())
         plist = []
         path = ["/"]
         self.getNode(self.tree._root, path, plist, oParent)
         return plist

    ##
    # @brief RTCのリスト、ツリーを作成
    # @param self
    # @param node 現在のノード
    # @param path 現在のパス
    # @param plist RTCリスト
    # @param oParent 親ノード  
    def getNode(self, node, path, plist, oParent):
        
        values = node._children.values()
        
        for v in values:
            
            
            if v.is_component:
                oChild = self.createNode(v.name,False)
                oParent.appendChild(oChild)
                
                tmpPath = path[:]
                tmpPath.append(v.name)
                plist.append(tmpPath[:])
            elif v.is_manager:
                pass
            elif v.is_directory or v.is_nameserver:
                oChild = self.createNode(v.name,False)
                oParent.appendChild(oChild)
                
                tmpPath = path[:]
                tmpPath.append(v.name)
                self.getNode(v,tmpPath,plist,oChild)
            
                
    ##
    # @brief RTCD起動ボタンのスロット
    # @param self
    def rtcdSlot(self):
        try:
            self.parent.setDataCpp()
            self.parent.setDataPy()
            self.parent.control_comp._rtcconf._ptr().startRTCD_Cpp()
            self.parent.control_comp._rtcconf._ptr().startRTCD_Py()

            

            self.parent.control_comp._rtcconf._ptr().setSystem()
            self.mesBox(u"rtcdを起動しました")
        except:
            self.mesBox(u"rtcdの起動に失敗しました")
            info = sys.exc_info()
            tbinfo = traceback.format_tb( info[2] )
            for tbi in tbinfo:
                print tbi

    ##
    # @brief ファイル読み込みボタンのスロット
    # @param self
    def addLoadSlot(self):
        text, ok = QtGui.QInputDialog.getText(self, u"IPアドレス入力",
                u"IPアドレス", QtGui.QLineEdit.Normal,
                self.WidList["textBox"]["Widget"].text())
        if ok and text != '':
            self.WidList["textBox"]["Widget"].setText(text)
            filepath, ok2 = QtGui.QInputDialog.getText(self, u"ファイル名入力",
                u"ファイル名", QtGui.QLineEdit.Normal,
                self.WidList["filepath"]["Widget"].text())
            if ok2 and filepath != '':
                self.WidList["filepath"]["Widget"].setText(filepath)
                path = str(self.WidList["filepath"]["Widget"].text().toLocal8Bit())
                
                self.parent.createTabs(path)
                self.parent.curFile = path
            else:
                self.mesBox(u"ファイル名を入力してください")

    ##
    # @brief ファイル読み込みボタンのスロット
    # @param self
    def addFilePathSlot(self):
        wid = self.WidList["filepath"]["Widget"]
        text = self.parent.getFilePath()
        self.WidList["filepath"]["Widget"].setText(text)
            
        
        wid.setText(text)

    ##
    # @brief 新規作成ボタンのスロット
    # @param self
    def newFileSlot(self):
        self.parent.newFile()

    ##
    # @brief ファイル保存ボタンのスロット
    # @param self 
    def saveFileSlot(self):
        path = str(self.WidList["filepath"]["Widget"].text().toLocal8Bit())
        if path == "":
            filepath, ok = QtGui.QInputDialog.getText(self, u"ファイル名入力",
                u"ファイル名", QtGui.QLineEdit.Normal,
                self.WidList["filepath"]["Widget"].text())
            if ok and filepath != '':
                self.WidList["filepath"]["Widget"].setText(filepath)

        path = str(self.WidList["filepath"]["Widget"].text().toLocal8Bit())
        if path != "":
            self.parent.saveFile(path)
            self.parent.curFile = path
        else:
            self.mesBox(u"ファイル名を入力してください")

