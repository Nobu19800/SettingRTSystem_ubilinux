# -*- coding: utf-8 -*-
##
#   @file FEComp.py
#   @brief 直列ブロックのウィジェット

from PyQt4 import QtCore, QtGui



##
# @class FEComp
# @brief 直列ブロックのウィジェット
#
class FEComp(QtGui.QWidget):
    ##
    # @brief コンストラクタ
    # @param self 
    # @param parent 親ウィジェット
    def __init__(self, parent=None):
        super(FEComp, self).__init__(parent)
        self.ECS = []
        self.CL = QtGui.QVBoxLayout()
        
        self.setLayout(self.CL)

        
