#!/bin/env python
# -*- encoding: utf-8 -*-

##
#   @file MainWindow.py
#   @brief メインウインドウ



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



from SettingRTCConf.ConfigWidget import ConfigWidget
from SettingRTCConf.CorbaWidget import CorbaWidget
from SettingRTCConf.ExecCxtWidget import ExecCxtWidget
from SettingRTCConf.LoggerWidget import LoggerWidget

from SettingRTCConf.ManagerWidget import ManagerWidget
from SettingRTCConf.NamingWidget import NamingWidget
from SettingRTCConf.TimerWidget import TimerWidget

from SettingRTCWindow.TabWidget import TabWidget
from SettingRTCWindow.ManagerControl import ManagerControl

from SettingRTCWindow.rtcdWidget import rtcdWidget

import imp

import SettingRTCWindow.RTCListWindow


from rtcConfSet import rtcConfSet
from rtcConfSetReq import rtcConfSetReq

##
# @brief サービスポートを接続する関数
# @param obj1 ポートオブジェクト1
# @param obj2 ポートオブジェクト2
# @param c_name コネクタ名
def connectServicePort(obj1, obj2, c_name):

    

    obj1.disconnect_all()
    
    obj2.disconnect_all()

    # connect ports
    conprof = RTC.ConnectorProfile(c_name, "", [obj1,obj2], [])

    

    ret = obj2.connect(conprof)

    


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

        self.setWindowTitle(u"複合コンポーネント作成支援ツール")
        self.setMinimumWidth(700)
        
        self.tree = None
        
        self.mgr = OpenRTM_aist.Manager.init(sys.argv)
        
        self.mgr.activateManager()
        self.mgr.runManager(True)


        rtcConfSetReq.rtcConfSetReqInit(self.mgr)
        filename = "rtcConfSetReq"
        #filepath = ["../rtcConfSetReq"]
        #func = self.getFunc(filename, filepath)
        #func(self.mgr)
        self.control_comp = self.mgr.createComponent(filename)

        rtcConfSet.MyModuleInit(self.mgr)

        

        self.tab_widget = QtGui.QTabWidget(self)
        self.rtcd_widget = rtcdWidget(self)

        self.tab_widget.addTab(self.rtcd_widget, u"RTCD")

        self.rtclistWindow = None
        self.rtclistArea = None
        

        self.setCentralWidget(self.tab_widget)

        self.createAction()
        self.createMenus()
        self.createToolBars()
        #self.mgrc = ManagerControl("")
        
        self.tab_widget_cpp =  None
        self.tab_widget_python = None


        
        self.curFile = ""
        self.rtcdFlag = False
        #self.mgrc.CreateComp("MyFirstComponent",[".\\MyFirstComponent"])
        #self.mgrc.CreateComp("MyFirstComponent",[".\\MyFirstComponent"])

    ##
    # @brief RTCを検索する
    # @param self 
    # @param name RTC名
    # @param ip IPアドレス
    # @return RTCのリスト
    def searchRTC(self, name, ip='localhost'):
        ans = []
        
        self.tree = rtctree.tree.RTCTree(servers=ip, orb=self.control_comp._manager.getORB())
        node = self.tree._root
        
        compList = []
        self.getNode(node, compList)

        for c in compList:
            if c.name == name:
                ans.append(c)

        

        return ans

    ##
    # @brief RTCのツリーからRTCを検索してリストにする
    # @param self
    # @param node 現在検索中のノード
    # @param cl リスト
    def getNode(self, node, cl):
        values = node._children.values()
        for v in values:
            if v.is_component:
                cl.append(v)
                    
            elif v.is_manager:
                pass
            else:
                                
                self.getNode(v, cl)
        
    
    ##
    # @brief アクションの作成の関数
    # @param self
    def createAction(self):

        self.newAct = QtGui.QAction(QtGui.QIcon(':/images/new.png'),"&New...",self)
        self.newAct.setShortcuts(QtGui.QKeySequence.New)
        self.newAct.triggered.connect(self.newFile)
        


        self.openAct = QtGui.QAction(QtGui.QIcon(':/images/open.png'),"&Open...",self)
        self.openAct.setShortcuts(QtGui.QKeySequence.Open)
        self.openAct.triggered.connect(self.open)


        self.saveAct = QtGui.QAction(QtGui.QIcon(':/images/save.png'),"&Save",self)
        self.saveAct.setShortcuts(QtGui.QKeySequence.Save)
        self.saveAct.triggered.connect(self.save)

        self.saveAsAct = QtGui.QAction("&Save &As",self)
        self.saveAsAct.setShortcuts(QtGui.QKeySequence.SaveAs)
        self.saveAsAct.triggered.connect(self.saveAs)

        self.createPackageAct = QtGui.QAction("&Create &Package",self)
        self.createPackageAct.triggered.connect(self.createPackage)

        self.rtcdAct = QtGui.QAction(QtGui.QIcon(':/images/run.png'),"&rtcd &Start",self)
        self.rtcdAct.triggered.connect(self.rtcdRun)

    ##
    # @brief タブ削除の関数
    # @param self
    def deleteTabs(self):
        if self.tab_widget_cpp:
            self.tab_widget.removeTab(self.tab_widget.indexOf(self.tab_widget_cpp))
            self.tab_widget_cpp = None
        if self.tab_widget_python:
            self.tab_widget.removeTab(self.tab_widget.indexOf(self.tab_widget_python))
            self.tab_widget_python = None
        if self.rtclistArea:
            self.tab_widget.removeTab(self.tab_widget.indexOf(self.rtclistArea))
            self.rtclistWindow = None
            self.rtclistArea = None
    
    ##
    # @brief メニューの作成の関数
    # @param self
    def createMenus(self):

        self.fileMenu = self.menuBar().addMenu("&File")
        self.fileMenu.addAction(self.newAct)
        self.fileMenu.addAction(self.openAct)
        self.fileMenu.addAction(self.saveAct)
        self.fileMenu.addAction(self.saveAsAct)
        self.fileMenu.addAction(self.createPackageAct)
        
        
        
    ##
    # @brief ツールバーの作成の関数
    # @param self
    def createToolBars(self):
        self.fileToolBar = self.addToolBar("File")
        self.fileToolBar.addAction(self.newAct)
        self.fileToolBar.addAction(self.openAct)
        self.fileToolBar.addAction(self.saveAct)
        self.fileToolBar.addAction(self.rtcdAct)

    ##
    # @brief タブの作成の関数
    # @param self
    # @param filapath 読み込むファイル名
    def createTabs(self, filapath):
        ipaddress = str(self.rtcd_widget.WidList["textBox"]["Widget"].text().toLocal8Bit())
        confsetComp = self.searchRTC("rtcConfSet0.rtc",ipaddress)
        confsetPort = confsetComp[0].get_port_by_name("rtcconf")
        #print confsetPort

        confsetComp[0].activate_in_ec(0)
        portname = confsetComp[0].name + "." + confsetPort.name + "." + self.control_comp.get_sdo_id() + "." + self.control_comp._rtcconfPort.getName()
        
        connectServicePort(confsetPort.object, self.control_comp._rtcconfPort.getPortRef(), portname)

        

        self.control_comp.get_owned_contexts()[0].activate_component(self.control_comp.getObjRef())


        self.mgrc_cpp = ManagerControl(filapath,self.control_comp,ManagerControl.CPP)
        self.mgrc_py = ManagerControl(filapath,self.control_comp,ManagerControl.PY)

        flag = True

        while flag:
            
            try:
                ans = self.control_comp._rtcconf._ptr().open(filapath)
                if ans != True:
                    self.mesBox(u"ファイルを開くのに失敗しました")
                    return
                wid = self.rtcd_widget.WidList["rtcList"]["Widget"]
                clist = self.control_comp._rtcconf._ptr().getExRTCList()[1]
                wid.clear()
                for c in clist:
                    wid.addItem(c)
                
                flag = False
            except:
                
                info = sys.exc_info()
                tbinfo = traceback.format_tb( info[2] )
                for tbi in tbinfo:
                    print tbi

        self.mgrc_cpp.SetParam()
        self.mgrc_py.SetParam()


        self.deleteTabs()

        if self.tab_widget_cpp == None:
            self.tab_widget_cpp = TabWidget(self.mgrc_cpp,"C++")
            self.tab_widget.addTab(self.tab_widget_cpp, u"CPP")

        if self.tab_widget_python == None:
            self.tab_widget_python = TabWidget(self.mgrc_py,"Python")
            self.tab_widget.addTab(self.tab_widget_python, u"Python")

        if self.rtclistWindow == None:
            """filename = "RTCListWindow"
            filepath = ["SettingRTCWindow"]
            sys.path.append(filepath[0])
            (file, pathname, description) = imp.find_module(filename, filepath)
            RTCListWindow = imp.load_module(filename, file, pathname, description)
            """
            self.rtclistWindow = SettingRTCWindow.RTCListWindow.RTC_Window(self)
            self.rtclistArea = SettingRTCWindow.RTCListWindow.ScrollArea()
            
            self.tab_widget.addTab(self.rtclistArea, u"RTCのリスト")
            try:
                data = self.control_comp._rtcconf._ptr().getProfileList()
            
                self.rtclistWindow.loadList(data[1])
            except:
                info = sys.exc_info()
                tbinfo = traceback.format_tb( info[2] )
                for tbi in tbinfo:
                    print tbi
            
            self.rtclistArea.setWidget(self.rtclistWindow)

    ##
    # @brief タブの作成の関数
    # @param self
    # @param name RTC名
    # @param type 0でrtcdの起動、1で実行ファイルの起動
    def createComp(self, name, type):
        if self.rtcdFlag == False:
            self.mesBox(u"rtcdを起動していません。\nツールバーのrtcd起動ボタンを押してください。")
            return
        try:
            ans = self.control_comp._rtcconf._ptr().createComp(name, type)
            if ans == False:
                self.mesBox(u"起動に失敗しました")
            else:
                self.mesBox(name+u"を起動しました")
        except:
            info = sys.exc_info()
            tbinfo = traceback.format_tb( info[2] )
            for tbi in tbinfo:
                print tbi

    
    ##
    # @brief RTCの初期化関数を取得
    # @param self
    # @param filename ファイル名
    # @param filepath ファイルパス
    # @return 初期化関数
    def getFunc(self, filename, filepath):
        try:
            sys.path.append(filepath[0])
            (file, pathname, description) = imp.find_module(filename, filepath)
            mod = imp.load_module(filename, file, pathname, description)
            func = getattr(mod,filename+"Init",None)

            return func
        except:
            info = sys.exc_info()
            tbinfo = traceback.format_tb( info[2] )
            for tbi in tbinfo:
                print tbi
            return None

    ##
    # @brief ダイアログでファイル選択
    # @param self
    # @return ファイルパス
    def getFilePath(self):
        fileName = QtGui.QFileDialog.getOpenFileName(self,u"開く","","Config File (*.conf);;All Files (*)")
        if fileName.isEmpty():
            return ""
        ba = str(fileName.toLocal8Bit())
        #ba = ba.replace("/","\\")
        

        return ba

    
    ##
    # @brief ファイル読み込みスロット
    # @param self
    def open(self):
        
        

        filepath = self.getFilePath()
        if filepath == "":
            return

        self.createTabs(filepath)
        self.curFile = filepath
        
        
    ##
    # @brief C++の設定ファイルにGUIの設定を反映
    # @param self    
    def setDataCpp(self):
        if self.tab_widget_cpp !=  None:
            data = self.tab_widget_cpp.getConfData() 
            cdata = self.control_comp.convConfData(data)
            try:
                self.control_comp._rtcconf._ptr().setDataSeq_Cpp(cdata)
            except:
                info = sys.exc_info()
                tbinfo = traceback.format_tb( info[2] )
                for tbi in tbinfo:
                    print tbi

    ##
    # @brief Pythonの設定ファイルにGUIの設定を反映
    # @param self   
    def setDataPy(self):
        if self.tab_widget_python !=  None:
            data = self.tab_widget_python.getConfData() 
            cdata = self.control_comp.convConfData(data)
            try:
                self.control_comp._rtcconf._ptr().setDataSeq_Py(cdata)
            except:
                info = sys.exc_info()
                tbinfo = traceback.format_tb( info[2] )
                for tbi in tbinfo:
                    print tbi
    

    
        
    ##
    # @brief ファイルに保存する
    # @param self
    # @param filename ファイル名
    def saveFile(self, filename):
        result = False
        self.setDataCpp()
        self.setDataPy()
        
        try:
            wid = self.rtcd_widget.WidList["rtcList"]["Widget"]
            clist = []
            for c in range(0, wid.count()):
                clist.append(str(wid.itemText(c).toLocal8Bit()))
            self.control_comp._rtcconf._ptr().setExRTCList(clist)
            result = self.control_comp._rtcconf._ptr().save(filename)
        except:
            info = sys.exc_info()
            tbinfo = traceback.format_tb( info[2] )
            for tbi in tbinfo:
                print tbi
        return result
    ##
    # @brief ファイル保存のスロット
    # @param self
    def save(self):
        if self.curFile == "":
            return self.saveAs()
        else:
            self.saveFile(self.curFile)
            return True

    ##
    # @brief パッケージを作成、保存
    # @param self
    # @param filename パッケージ名
    def createPack(self, filename):
        result = False
        try:
            result = self.control_comp._rtcconf._ptr().createProject(filename)
        except:
            info = sys.exc_info()
            tbinfo = traceback.format_tb( info[2] )
            for tbi in tbinfo:
                print tbi
        return result
    ##
    # @brief パッケージを作成、保存のスロット
    # @param self           
    def createPackage(self):
        fileName = QtGui.QFileDialog.getSaveFileName(self,u"保存", "","Config File (*.conf);;All Files (*)")
        if fileName.isEmpty():
            return False
        ba = str(fileName.toLocal8Bit())

        self.createPack(ba)

    
    ##
    # @brief ファイルを別名で保存のスロット
    # @param self   
    def saveAs(self):
        
        fileName = QtGui.QFileDialog.getSaveFileName(self,u"保存", "","Config File (*.conf);;All Files (*)")
        if fileName.isEmpty():
            return False

        ba = str(fileName.toLocal8Bit())
        
        self.saveFile(ba)
        self.curFile = ba
        return True
        #self.tab_widget_python = None


        """fname = os.path.basename(ba)
        name, ext = os.path.splitext(fname)
        dname = os.path.dirname(os.path.relpath(ba))

        
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
                
            



	f.close()"""

	

	

    
    ##
    # @brief 初期化のスロット
    # @param self
    def newFile(self):
        text, ok = QtGui.QInputDialog.getText(self, u"アドレス入力",
                u"アドレス", QtGui.QLineEdit.Normal,
                self.rtcd_widget.WidList["textBox"]["Widget"].text())
        if ok and text != '':
            self.rtcd_widget.WidList["textBox"]["Widget"].setText(text)
            self.createTabs("rtc.conf")
            self.curFile = ""
        

    ##
    # @brief rtcdを起動する
    # @param self
    def rtcdRun(self):
        self.rtcd_widget.rtcdSlot()
        self.rtcdFlag = True

    ##
    # @brief メッセージボックス表示
    # @param self
    # @param mes 表示する文字列
    def mesBox(self, mes):
        msgbox = QtGui.QMessageBox( self )
        msgbox.setText( mes )
        msgbox.setModal( True )
        ret = msgbox.exec_()
