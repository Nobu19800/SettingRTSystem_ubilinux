# -*- coding: utf-8 -*-

##
#   @file MPTask.py
#   @brief GUI、直列ブロック実行スレッド

import threading
import time

import OpenRTM_aist


pyqtExist = True
try:
    from PyQt4 import QtCore, QtGui
except:
    pyqtExist = False


if pyqtExist:
    from MainWindow import MainWindow



##
# @class MPComp
# @brief 同一スレッドでの実行順序クラス
#
class MPComp:
    ##
    # @brief コンストラクタ
    # @param self 
    def __init__(self):
        self.comp = None
        self.I = 0
        self.J = 0
        self.K = 0


##
# @class MPTask
# @brief 直列ブロックを実行するスレッドのクラス
#
class MPTask(OpenRTM_aist.Task):
    ##
    # @brief コンストラクタ
    # @param self
    # @param c 実行コンテキストオブジェクト
    def __init__(self, c):
        OpenRTM_aist.Task.__init__(self)
        self.m_ec = c
        self.m_comp = []
    
    ##
    # @brief コンポーネントを追加する関数
    # @param self
    # @param c ブロック
    # @param I　全体の並列ブロックの番号
    # @param J 並列ブロック内の直列ブロックの番号
    # @param K 直列ブロック内のブロックの番号
    def addComp(self, c, I, J, K):
        self.mc = MPComp()
        self.mc.comp = c
        self.mc.I = I
        self.mc.J = J
        self.mc.K = K
        self.m_comp.append(self.mc)
    
    ##
    # @brief スレッド実行関数
    # @param self
    # @return 0
    def svc(self):
        if len(self.m_ec.rs) > self.m_ec.r_num:
            for i in range(0, len(self.m_comp)):
                self.m_ec.rs[self.m_ec.r_num].rs[self.m_comp[i].I].SR[self.m_comp[i].J][self.m_comp[i].K].s = 1
                self.m_ec.workerComp(self.m_comp[i].comp)
                self.m_ec.rs[self.m_ec.r_num].rs[self.m_comp[i].I].SR[self.m_comp[i].J][self.m_comp[i].K].s = 0

        return 0



##
# @class GUITask
# @brief GUIを実行するスレッド
#
class GUITask(OpenRTM_aist.Task):
    app_flag = False
    ##
    # @brief コンストラクタ
    # @param self 
    # @param ec 実行コンテキストオブジェクト
    def __init__(self, ec):
        OpenRTM_aist.Task.__init__(self)
        self.m_ec = ec
    ##
    # @brief スレッド実行関数
    # @param self
    # @return 0
    def svc(self):
        if GUITask.app_flag == False:
            GUITask.app_flag = True
            guard = OpenRTM_aist.ScopedLock(self.m_ec._workerthread._mutex)

            app = QtGui.QApplication([""])
            mainWin = MainWindow(self.m_ec)
            mainWin.show()
            
            del guard

            app.exec_()
        else:
            pass

        return 0

    ##
    # @brief 未使用
    # @param self
    def updateRTC(self):
        pass





