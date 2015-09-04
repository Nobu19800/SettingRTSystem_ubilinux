# -*- coding: utf-8 -*-
##
#   @file AddButton2.py
#   @brief 並列ブロック追加ボタン、並列ブロックの先頭に直列ブロック追加ボタン


from PyQt4 import QtCore, QtGui
from ExComp import CompLayout



##
# @class AddButton2
# @brief 直列ブロック追加ボタンを含むウィジェット
#
class AddButton2(QtGui.QWidget):
    clicked = QtCore.pyqtSignal(object)
    ##
    # @brief コンストラクタ
    # @param self 
    # @param text 表示テキスト
    # @param parent 親ウィジェット
    def __init__(self, text, parent=None):
        super(AddButton2, self).__init__(parent)
        
        self.Cl = None
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
        
        self.clicked.emit(self.Cl)
