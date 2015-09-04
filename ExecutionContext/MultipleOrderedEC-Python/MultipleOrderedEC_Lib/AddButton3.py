# -*- coding: utf-8 -*-
##
#   @file AddButton3.py
#   @brief 並列ブロック削除ボタンを含むウィジェット

from PyQt4 import QtCore, QtGui
from ExComp import CompLayout



##
# @class AddButton3
# @brief 並列ブロック削除ボタンを含むウィジェット
#
class AddButton3(QtGui.QWidget):
    clicked = QtCore.pyqtSignal(object, object)
    ##
    # @brief コンストラクタ
    # @param self 
    # @param text 表示テキスト
    # @param parent 親ウィジェット
    def __init__(self, text, parent=None):
        super(AddButton3, self).__init__(parent)
        
        self.Vl = None
        self.c = None
        self.PB = QtGui.QPushButton(text)
        self.mainLayout = QtGui.QVBoxLayout()
        
        #connect(PB, SIGNAL(clicked()),
        #    this, SLOT(clickedSlot()))

        self.PB.clicked.connect(self.clickedSlot)

        self.mainLayout.addWidget(self.PB)

        self.setLayout(self.mainLayout)

    
    ##
    # @brief ボタンクリック時に呼び出すスロット
    # @param self 
    def clickedSlot(self):
        
        self.clicked.emit(self.Vl, self.c)
