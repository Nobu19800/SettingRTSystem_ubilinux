# -*- coding: utf-8 -*-

##
#   @file AddButton.py
#   @brief 直列ブロックの先頭にブロックを追加するボタン

from PyQt4 import QtCore, QtGui
from FEComp import FEComp


##
# @class AddButton
# @brief 直列ブロックの先頭にブロックを追加するボタン
#
class AddButton(QtGui.QWidget):
    clicked = QtCore.pyqtSignal(object)
    ##
    # @brief コンストラクタ
    # @param self 
    # @param text 表示テキスト
    # @param parent 親ウィジェット
    def __init__(self, text, parent=None):
        super(AddButton, self).__init__(parent)
        
        self.Fc = None
        self.PB = QtGui.QPushButton(text)
        self.mainLayout = QtGui.QVBoxLayout()
        
        #connect(PB, SIGNAL(clicked()),
        #    this, SLOT(clickedSlot()))
        #QtCore.QObject.connect(self.PB, QtCore.SIGNAL("clicked()"), self, QtCore.SLOT("clickedSlot()"))

        self.PB.clicked.connect(self.clickedSlot)

        self.mainLayout.addWidget(self.PB)

        self.setLayout(self.mainLayout)

        
        
    
    ##
    # @brief ボタンクリック時に呼び出すスロット
    # @param self 
    def clickedSlot(self):
        self.clicked.emit(self.Fc)
