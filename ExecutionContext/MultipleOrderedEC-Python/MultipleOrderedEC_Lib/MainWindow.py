# -*- coding: utf-8 -*-
##
#   @file MainWindow.py
#   @brief メインウィンドウ

import os
from PyQt4 import QtCore, QtGui
from SetComp import SetComp



##
# @class MainWindow
# @brief メインウィンドウ
#
class MainWindow(QtGui.QMainWindow):
    ##
    # @brief コンストラクタ
    # @param self 
    # @param ec 実行コンテキストオブジェクト
    def __init__(self, ec):
        super(MainWindow, self).__init__()

        self.layout = QtGui.QVBoxLayout()
        self.m_ec = ec
        self.SC = SetComp(self.m_ec)
        
        self.SC.UpdateSizeSignal.connect(self.m_resize)
        self.layout.addWidget(self.SC)

        self.layout.addStretch()
        self.UB = QtGui.QPushButton(u"更新")
        self.layout.addWidget(self.UB)


        self.UB.clicked.connect(self.UpdateComp)

        self.DB = QtGui.QPushButton(u"追加")
        self.layout.addWidget(self.DB)

        self.DB.clicked.connect(self.SC.CreateComp)

	
	

        self.widget = QtGui.QWidget()
        self.widget.setLayout(self.layout)
        self.area = QtGui.QScrollArea()
        self.area.setWidget(self.widget)
        self.setCentralWidget(self.area)
        self.setWindowTitle("MultipleOrderedECGUI")
        self.setUnifiedTitleAndToolBarOnMac(True)

        self.SC.UpdateSizeSlot()

        self.newAct = None
        self.openAct = None
        self.saveAct = None
        self.fileMenu = None

        self.createAction()
        self.createMenus()

        #self.widget.resize(400, 400)

    
    ##
    # @brief サイズを変更するときに呼び出されるスロット
    # @param self 
    # @param w 幅
    # @param h 高さ
    def m_resize(self, w, h):

        self.widget.resize(w, h)

    
    ##
    # @brief RTCが追加、削除されたときに呼び出されるスロット
    # @param self 
    def UpdateComp(self):

        self.SC.UpdateComps()
        self.SC.UpdateComp2()

    
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

        self.saveAsAct = QtGui.QAction("&Save &As",self)
        self.saveAsAct.setShortcuts(QtGui.QKeySequence.SaveAs)
        self.saveAsAct.triggered.connect(self.saveAs)
        

    
    ##
    # @brief メニューの作成の関数
    # @param self 
    def createMenus(self):

        self.fileMenu = self.menuBar().addMenu("&File")
        self.fileMenu.addAction(self.newAct)
        self.fileMenu.addAction(self.openAct)
        self.fileMenu.addAction(self.saveAct)
        self.fileMenu.addAction(self.saveAsAct)




    
    ##
    # @brief ファイル読み込みスロット
    # @param self 
    def open(self):

        fileName = QtGui.QFileDialog.getOpenFileName(self,u"開く","","Config File (*.conf);;Python File (*.py);;All Files (*)")
        

        ba = str(fileName.toLocal8Bit())
        self.SC.open(ba)
        self.m_ec.FileName = ba

    ##
    # @brief ファイル保存スロット
    # @param self
    # @return 成功でTrue、失敗でFalse
    def save(self):
        root, ext = os.path.splitext(self.m_ec.FileName)
        if self.m_ec.FileName == "" or ext == ".py":
            return self.saveAs()
        else:
            return self.SC.save(self.m_ec.FileName)
            
            

    
    ##
    # @brief 別のファイル保存のスロット
    # @param self
    # @return 成功でTrue、失敗でFalse
    def saveAs(self):

        fileName = QtGui.QFileDialog.getSaveFileName(self,u"保存", "","Config File (*.conf);;All Files (*)")
        if fileName.isEmpty():
            return False

        ba = str(fileName.toLocal8Bit())
        self.m_ec.FileName = ba


        return self.SC.save(ba)


    
    ##
    # @brief 初期化のスロット
    # @param self 
    def newFile(self):

        self.SC.newFile()
        self.m_ec.FileName = ""

    


    
    ##
    # @brief 実行順序をGUIに反映させる関数
    # @param self
    # @param rs 並列ブロックのリスト
    def UpdateRTC(self,rs):

        self.SC.UpdateRTC(rs)

