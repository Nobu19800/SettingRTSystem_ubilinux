#!/bin/env python
# -*- encoding: utf-8 -*-

##
#   @file MainWindow.py
#   @brief メインウインドウ



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

from ConfigWidget import ConfigWidget
from CorbaWidget import CorbaWidget
from ExecCxtWidget import ExecCxtWidget
from LoggerWidget import LoggerWidget
from ManagerControl import ManagerControl
from ManagerWidget import ManagerWidget
from NamingWidget import NamingWidget
from TimerWidget import TimerWidget


##
# @class MainWindow
# @brief メインウインドウ
#
class MainWindow(QtGui.QMainWindow):
    ##
    # @brief コンストラクタ
    # @param self 
    def __init__(self):
        super(MainWindow, self).__init__()
        self.setWindowTitle(u"RTC設定ファイル作成ツール")

        self.tab_widget = QtGui.QTabWidget(self)
        self.setCentralWidget(self.tab_widget)

        self.createAction()
        self.createMenus()

        #self.mgrc = ManagerControl("")
        self.mgrc = None
        
        self.curFile = ""

        #self.mgrc.CreateComp("MyFirstComponent",[".\\MyFirstComponent"])
        #self.mgrc.CreateComp("MyFirstComponent",[".\\MyFirstComponent"])
        
    
    ##
    # @brief アクションの作成の関数
    # @param self
    def createAction(self):

        self.newAct = QtGui.QAction("&New...",self)
        self.newAct.setShortcuts(QtGui.QKeySequence.New)
        self.newAct.triggered.connect(self.newFile)
        


        self.openAct = QtGui.QAction("&Open...",self)
        self.openAct.setShortcuts(QtGui.QKeySequence.Open)
        self.openAct.triggered.connect(self.open)


        self.saveAct = QtGui.QAction("&Save",self)
        self.saveAct.setShortcuts(QtGui.QKeySequence.Save)
        self.saveAct.triggered.connect(self.save)

    
    ##
    # @brief メニューの作成の関数
    # @param self
    def createMenus(self):

        self.fileMenu = self.menuBar().addMenu("&File")
        self.fileMenu.addAction(self.newAct)
        self.fileMenu.addAction(self.openAct)
        self.fileMenu.addAction(self.saveAct)

    ##
    # @brief タブの作成の関数
    # @param self
    def createTabs(self):
        self.Tabs = []
        self.ManagerTab = ManagerWidget(self.mgrc)
        self.tab_widget.addTab(self.ManagerTab, u"マネージャ")
        self.Tabs.append(self.ManagerTab)
        self.CorbaTab = CorbaWidget(self.mgrc)
        self.tab_widget.addTab(self.CorbaTab, u"CORBA")
        self.Tabs.append(self.CorbaTab)
        self.ConfigTab = ConfigWidget(self.mgrc)
        self.tab_widget.addTab(self.ConfigTab, u"一般的")
        self.Tabs.append(self.ConfigTab)
        self.NamingTab = NamingWidget(self.mgrc)
        self.tab_widget.addTab(self.NamingTab, u"ネームサービス")
        self.Tabs.append(self.NamingTab)
        self.LoggerTab = LoggerWidget(self.mgrc)
        self.tab_widget.addTab(self.LoggerTab, u"ロガー")
        self.Tabs.append(self.LoggerTab)
        self.TimerTab = TimerWidget(self.mgrc)
        self.tab_widget.addTab(self.TimerTab, u"タイマ")
        self.Tabs.append(self.TimerTab)
        self.ExecCxtTab = ExecCxtWidget(self.mgrc, self.ManagerTab)
        self.tab_widget.addTab(self.ExecCxtTab, u"実行コンテキスト")
        self.Tabs.append(self.ExecCxtTab)
	

    
    ##
    # @brief ファイル読み込みスロット
    # @param self 
    def open(self):
        if self.mgrc == None:
            fileName = QtGui.QFileDialog.getOpenFileName(self,u"開く","","Config File (*.conf);;All Files (*)")
            if fileName.isEmpty():
                return
            ba = str(fileName.toLocal8Bit())
            #ba = ba.replace("/","\\")
            self.mgrc = ManagerControl(ba)
            self.createTabs()

            self.curFile = ba           

            
        else:
            self.mesBox(u"既にコンフィギュレーションファイルは開いています")
    ##
    # @brief ファイル別名で保存するときのスロット(未実装)
    # @param self 
    def saveAs(self):
        pass
    
    ##
    # @brief ファイル保存のスロット
    # @param self 
    def save(self):

        fileName = QtGui.QFileDialog.getSaveFileName(self,u"保存", "","Config File (*.conf);;All Files (*)")
        if fileName.isEmpty():
                return False

        ba = str(fileName.toLocal8Bit())
        
        fname = os.path.basename(ba)
        name, ext = os.path.splitext(fname)
        dname = os.path.dirname(os.path.relpath(ba))

        

        f = open(ba, "w")

        for t in self.Tabs:
                for k,j in t.WidList.items():
                    if k.split(".")[-1] != "sub":
                        s = k + ": "
                        v = ""
                        if j["Type"] == ManagerControl.TextBox:
                            text = str(j["Widget"].text().toLocal8Bit())
                            if k == "exec_cxt.periodic.filename" and text == "":
                                text = dname + "/order.conf"
                                of = open(text, "wb")
                                of.close()
                            
                            v += text
                        elif j["Type"] == ManagerControl.TextCombox or j["Type"] == ManagerControl.Combox:
                            
                            
                            if k == "manager.modules.load_path" or k == "manager.modules.preload" or k == "manager.components.precreate" or k == "corba.endpoints":
                                for c in range(0, j["Widget"].count()):
                                    v += str(j["Widget"].itemText(c).toLocal8Bit()).replace("\\","/")
                                    if c < j["Widget"].count()-1:
                                        v += ","
                            else:
                                v += str(j["Widget"].currentText().toLocal8Bit())
                        elif j["Type"] == ManagerControl.SpinBox or j["Type"] == ManagerControl.DoubleSpinBox:
                            v += str(j["Widget"].value())
                        if v != "":
                            s += v + "\n"
                            f.write(s)



            

            
        inv_dname = os.path.relpath(os.path.abspath(".\\"), dname)
        s = "cd " + inv_dname + "\n"
        s += "rtcd_python -f " + ".\\" + os.path.relpath(ba)

        if dname == "":
            path = ".\\"+name+".bat"
        else:
            path = dname+"\\"+name+".bat"
        pf = open(path, "w")
        pf.write(s)
        pf.close()


            
        for c in self.mgrc.mgr.getComponents():
                
                if dname == "":
                    path = "./"+c.get_sdo_id() + ".conf"
                else:
                    path = dname.replace("\\","/") + "/" +c.get_sdo_id() + ".conf"
                f2 = open(path, "w")

                s = c.getCategory() + "." + c.get_sdo_id() + ".config_file: " + path + "\n"
                f.write(s)

                
                cstes = c.get_configuration().get_active_configuration_set()
                s = "configuration.active_config: " + cstes.id + "\n"
                f2.write(s)
                
                for l in c.get_configuration().get_configuration_sets():
                    for d in l.configuration_data:
                        s = "conf." + l.id + "." + d.name + ": " + d.value.value() + "\n"
                        f2.write(s)

                oEC = c.get_owned_contexts()[0]
                rate = oEC.get_rate()
                s = "exec_cxt.periodic.rate: " + str(rate) + "\n"
                f2.write(s)

                #s = "exec_cxt.periodic.type: " + "" + "\n"
                f2.close()
                    
                



        f.close()

	

	

    
    ##
    # @brief 初期化のスロット
    # @param self 
    def newFile(self):
        if self.mgrc == None:
            self.mgrc = ManagerControl("")
            self.createTabs()

            
            """for c in self.mgrc.mgr.getComponents():
                print c.get_sdo_id()
                for l in c.get_configuration().get_configuration_sets():
                    print l.id
                    print l.description
                    #prop = OpenRTM_aist.SDOPackage.NVList
                    #OpenRTM_aist.toProperties(prop,l.configuration_data)
                    #print prop
                    for d in l.configuration_data:
                        print d.name
                        print d.value.value()"""
                
        else:
            self.mesBox(u"既にコンフィギュレーションファイルは開いています")


        
    ##
    # @brief メッセージボックス表示
    # @param self 
    # @param mes 表示する文字列
    def mesBox(self, mes):
        msgbox = QtGui.QMessageBox( self )
        msgbox.setText( mes )
        msgbox.setModal( True )
        ret = msgbox.exec_()
