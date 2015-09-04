# -*- coding: utf-8 -*-

##
#   @file FrameComp.py
#   @brief 実行順序のブロックを表示するウィジェット

from PyQt4 import QtCore, QtGui
from ExComp import ExComp, CompLayout
from FEComp import FEComp
from Config import Configs
import MPComp
from AddButton import AddButton
from AddButton2 import AddButton2
from AddButton3 import AddButton3
import OpenRTM_aist

import MultipleOrderedEC_rc

import struct



##
# @class FrameComp
# @brief 実行順序のブロックを表示するウィジェット
#
class FrameComp(QtGui.QWidget):
    UpdateSizeSignal = QtCore.pyqtSignal()
    ##
    # @brief コンストラクタ
    # @param self 
    # @param ec 実行コンテキストオブジェクト
    # @param sc 全実行順序のブロック表示ウィジェット
    # @param parent 親ウィジェット
    def __init__(self, ec, sc, parent=None):
        super(FrameComp, self).__init__(parent)
        self.CLS = []
        self.Comps = []
        
        self.m_ec = ec
        self.mainLayout = QtGui.QVBoxLayout()
        self.TB = QtGui.QPushButton(u"追加")
        
        self.TB.clicked.connect(self.AddCompsT)
        self.mainLayout.addWidget(self.TB)
        
        self.DB = QtGui.QPushButton(u"削除")
        
        self.DB.clicked.connect(self.DeleteFrame)
        self.mainLayout.addWidget(self.DB)
        
        self.setLayout(self.mainLayout)

        self.cf = Configs()

        self.Sc = sc

        self.X = 0
        self.Y = 0
        self.AB2 = []
        self.mBT = []
        self.UB = []

    
    ##
    # @brief このブロックを削除する関数
    # @param self 
    def DeleteFrame(self):

        self.Sc.DeleteComp(self)


    
    ##
    # @brief 並列ブロックの先頭に直列ブロックを追加
    # @param self
    # @param c 並列ブロックレイアウト
    def AddCompSlot3(self, c):

        AB2 = AddButton(u"追加")
        self.AB2.append(AB2)



        AB2.clicked.connect(self.AddCompSlot1)
        

        FC = FEComp()

        AB2.Fc = FC



        self.AddComp(FC)


	

        self.CLS.append(FC)


        Vl = QtGui.QVBoxLayout()
        c.VL.append(Vl)

	

        VD = QtGui.QWidget()
        CP = QtGui.QHBoxLayout()
        CP.addWidget(AB2.PB)
        VD.setLayout(CP)

	

        VD.setMaximumWidth(100)
        VD.setMinimumWidth(100)

	

        Vl.addWidget(VD)
        Vl.addWidget(FC)

        VW = QtGui.QWidget()
        VW.setLayout(Vl)

        mBT = AddButton3(u"削除")
        self.mBT.append(mBT)
        mBT.Vl = VW
        mBT.c = c

        Vl.addStretch()
        Vl.addWidget(mBT.PB)


	

	

        mBT.clicked.connect(self.DeleteComp)

	

        palette = QtGui.QPalette()
        palette.setColor(QtGui.QPalette.Background, QtGui.QColor(0, 140, 140))
        VW.setPalette(palette)
        VW.setForegroundRole(QtGui.QPalette.Dark)

        VW.setAutoFillBackground(True)

        VW.setFixedWidth(150)



        c.subLayout.insertWidget(0, VW)


        self.UpdateSize()

    ##
    # @brief 並列ブロック初期化
    # @param self
    # @param c 並列ブロックレイアウト
    def AddCompSlot2(self, c):

        c.subLayout = QtGui.QHBoxLayout()
        self.AddCompSlot3(c)



        c.AB = AddButton2(u"追\n加")
        c.AB.Cl = c


        c.AB.PB.setMaximumSize(25, 100)
        c.AB.PB.setMinimumSize(25, 100)

	

        c.AB.clicked.connect(self.AddCompSlot3)

	

        c.subLayout.addWidget(c.AB.PB)
        c.subLayout.addStretch()


        UB = AddButton2(u"追加")
        self.UB.append(UB)
        UB.Cl = c


        UB.clicked.connect(self.AddCompsU)

	

        c.mainLayout = QtGui.QVBoxLayout()
        c.mainWidget = QtGui.QWidget()
        c.mainWidget.setLayout(c.mainLayout)

        sL = QtGui.QWidget()
        sL.setLayout(c.subLayout)

        palette = QtGui.QPalette()
        palette.setColor(QtGui.QPalette.Background, QtGui.QColor(140, 0, 140))
        sL.setPalette(palette)
        sL.setForegroundRole(QtGui.QPalette.Dark)

        sL.setAutoFillBackground(True)

        c.Lb = QtGui.QLabel()

        c.mainLayout.addWidget(sL)
        c.mainLayout.addWidget(c.Lb)
        c.mainLayout.addWidget(UB.PB)


	
	
	


        self.UpdateSize()

    ##
    # @brief 並列ブロック追加
    # @param self 
    def AddComps2(self):

        CL = CompLayout()
        self.AddCompSlot2(CL)
        self.Comps.append(CL)
        self.mainLayout.addWidget(CL.mainWidget)

        self.UpdateSize()


	


    
    ##
    # @brief 並列ブロック削除
    # @param self
    # @param Vl 並列ブロック追加ボタンのウィジェット
    # @param c 並列ブロック削除
    def DeleteComp(self, Vl, c):


        c.subLayout.removeWidget(Vl)
        Vl.close()

	

        c.VL.remove(Vl.layout())
        

        if len(c.VL) == 0 and len(self.Comps) > 1:
            self.Comps.remove(c)
            self.mainLayout.removeWidget(c.mainWidget)

	


        self.UpdateSize()

	


    

    
    ##
    # @brief サイズ変更の関数
    # @param self 
    def UpdateSize(self):

        Ws = 0
        Hs = 0
        Ks = 0
        for i in range(0, len(self.Comps)):
            Ks += 1
            tHs = 0
            if Ws < len(self.Comps[i].VL):

                Ws = len(self.Comps[i].VL)

            for j in range(0, len(self.Comps[i].VL)):
                if tHs < self.Comps[i].VL[j].itemAt(1).widget().layout().count():
                    tHs = self.Comps[i].VL[j].itemAt(1).widget().layout().count()
                    
            Hs += tHs

        ws = Ws*180+90
        hs = Hs*200+70+Ks*200

        self.X = ws
        self.Y = hs

	


        self.UpdateSizeSignal.emit()


        for i in range(0, len(self.Comps)):
            self.Comps[i].Lb.setPixmap(QtGui.QPixmap(":/images/arrow.png").scaled(Ws*180,30))

    
    ##
    # @brief 並列ブロックを先頭に追加するスロット
    # @param self 
    def AddCompsT(self):
        self.InsertComps2(2)



    
    ##
    # @brief 並列ブロックを指定並列ブロックの後に追加するスロット
    # @param self 
    # @param c 指定並列ブロック
    def AddCompsU(self, c):
        t = self.mainLayout.indexOf(c.mainWidget)
        self.InsertComps2(t+1)


	

    ##
    # @brief 並列ブロックを指定位置に追加
    # @param self 
    # @param num 指定位置
    def InsertComps2(self, num):

        CL = CompLayout()
        self.AddCompSlot2(CL)
        self.Comps.append(CL)

        self.mainLayout.insertWidget(num, CL.mainWidget)

        self.UpdateSize()

	

    ##
    # @brief 直列ブロック初期化
    # @param self 
    # @param FC 直列ブロックウィジェット
    def AddComp(self, FC):

        EC = ExComp()

        FC.ECS.append(EC)
        FC.CL.addWidget(EC)
        EC.Fc = FC

	

        EC.AddCompSignal.connect(self.AddCompSlot)


        EC.UpdateComp(self.Sc.rtclist, self.Sc.rtclist2)

        self.UpdateSize()

	


    ##
    # @brief 直列ブロック追加
    # @param self
    # @param num 指定位置
    # @param FC 直列ブロックウィジェット
    def InsertComp(self, num, FC):

        EC = ExComp()

        FC.ECS.append(EC)
        FC.CL.insertWidget(num, EC)
        EC.Fc = FC


        EC.AddCompSignal.connect(self.AddCompSlot)

        EC.UpdateComp(self.Sc.rtclist, self.Sc.rtclist2)


        self.UpdateSize()

	

    
    ##
    # @brief RTCが追加、削除されたときにブロックに反映する関数
    # @param self
    # @param rtclist RTCのリスト
    # @param rtclist2 未使用
    def UpdateComp2(self, rtclist, rtclist2):

        for i in range(0,len(self.CLS)):
            for j in range(0, len(self.CLS[i].ECS)):
                self.CLS[i].ECS[j].UpdateComp(rtclist,rtclist2)

	



    
    ##
    # @brief 直列ブロックの指定位置にブロック追加するスロット
    # @param self 
    # @param ec 挿入箇所手前のブロックウィジェット
    # @param fc 直列ブロックウィジェット
    def AddCompSlot(self, ec, fc):
        
        self.InsertComp(fc.CL.indexOf(ec)+1, fc)

    
    ##
    # @brief 直列ブロックの先頭にブロックを追加するスロット
    # @param self 
    # @param fc 直列ブロックウィジェット
    def AddCompSlot1(self, fc):

        self.InsertComp(0, fc)


    
    ##
    # @brief RTCが追加、削除されたときに実行条件に反映する関数
    # @param self 
    # @param mR 実行順序
    def SetFrame(self, mR):
        r = len(mR.ar)
        for i in range(0, r):
            for j in range(0, len(self.cf.Cl)):
                v = mR.ar[i].state
                if self.cf.Cl[j].Name == mR.ar[i].name:
                    if v == -1:
                        self.cf.Cl[j].c_none.setChecked(True)

                    elif v == OpenRTM_aist.RTC.CREATED_STATE:
                        self.cf.Cl[j].c_created.setChecked(True)

                    elif v == OpenRTM_aist.RTC.INACTIVE_STATE:
                        self.cf.Cl[j].c_inactive.setChecked(True)

                    elif v == OpenRTM_aist.RTC.ACTIVE_STATE:
                        self.cf.Cl[j].c_active.setChecked(True)

                    elif v == OpenRTM_aist.RTC.ERROR_STATE:
                        self.cf.Cl[j].c_error.setChecked(True)


			
		
	

		
	

        for i in range(0, len(mR.rs)): 
            self.AddComps2()
            for j in range(0, len(mR.rs[i].SR)):
                
                if j != 0:
                    self.AddCompSlot3(self.Comps[i])
                fd = self.Comps[i].VL[j].layout().itemAt(1).widget()
                    
                for k in range(0, len(mR.rs[i].SR[j])):
                    if k != 0:
                            
                        self.AddComp(fd)
                    for l in range(0, fd.ECS[k].CB.count()):
                        if fd.ECS[k].CB.itemText(l) == mR.rs[i].SR[j][k].v:
                            fd.ECS[k].CB.setCurrentIndex(l)

	


    


    
    ##
    # @brief バイナリファイル保存の関数
    # @param self 
    # @param ofs2 ファイルストリーム
    # @param mR 実行順序
    # @return 成功でTrue、失敗でFalse
    def save(self, ofs2, mR):

        rs = MPComp.main_Rule()

        r = len(self.cf.Cl)
        d = struct.pack("i", r)
        ofs2.write(d)
        for i in range(0, r):
            cn = self.cf.Cl[i].Name


            MPComp.WriteString(cn , ofs2 )

            a = -1


            if self.cf.Cl[i].c_none.isChecked():

                a = -1

            elif self.cf.Cl[i].c_created.isChecked():

                a = OpenRTM_aist.RTC.CREATED_STATE

            elif self.cf.Cl[i].c_inactive.isChecked():

                a = OpenRTM_aist.RTC.INACTIVE_STATE

            elif self.cf.Cl[i].c_active.isChecked():

                a = OpenRTM_aist.RTC.ACTIVE_STATE

            elif self.cf.Cl[i].c_error.isChecked():

                a = OpenRTM_aist.RTC.ERROR_STATE


		

            a_t = -1
            if a == -1:
                a_t = -1
            elif a == OpenRTM_aist.RTC.CREATED_STATE:
                a_t = 0
            elif a == OpenRTM_aist.RTC.INACTIVE_STATE:
                a_t = 1
            elif a == OpenRTM_aist.RTC.ACTIVE_STATE:
                a_t = 2
            elif a == OpenRTM_aist.RTC.ERROR_STATE:
                a_t = 3
            
            d = struct.pack("i", a_t)
            ofs2.write(d)

            ar = MPComp.add_Rule()
            ar.name = self.cf.Cl[i].Name
            ar.state = a

            rs.ar.append(ar)

        c = len(self.Comps)
        d = struct.pack("i", c)
        ofs2.write(d)

	

        for i in range(0, len(self.Comps)):
            r = MPComp.Rule()
            d = len(self.Comps[i].VL)

            a = struct.pack("i", d)
            ofs2.write(a)

		

            for j in range(0, d):

                SRs = []


                fd = self.Comps[i].VL[j].layout().itemAt(1).widget()
                e = len(fd.ECS)
                a = struct.pack("i", e)
                ofs2.write(a)


                for k in range(0, e):
                    fd_text = fd.ECS[k].CB.currentText()

                    N = str(fd_text.toLocal8Bit())
                    MPComp.WriteString(N , ofs2 )
                    SR = MPComp.sub_Rule()

                    SR.v = N

                    SR.s = 0


                    SRs.append(SR)


			

                r.SR.append(SRs)


            rs.rs.append(r)


	


        mR.append(rs)

	
	

	


        return True




    
    ##
    # @brief ブロックの色を変えるスロット
    # @param self
    # @param rs 実行順序
    def UpdateEC(self, rs):
        for i in range(0, len(rs)):

            if len(self.Comps) > i:

                for j in range(0, len(rs[i].SR)):

                    if len(self.Comps[i].VL) > j:

                        fd = self.Comps[i].VL[j].layout().itemAt(1).widget()
                        for k in range(0, len(rs[i].SR[j])):
                            if len(fd.ECS) > k:

                                palette = QtGui.QPalette()

                                if rs[i].SR[j][k].s == 0:
                                    palette.setColor(QtGui.QPalette.Background, QtGui.QColor(140, 140, 140))
                                else:
                                    palette.setColor(QtGui.QPalette.Background, QtGui.QColor(140, 140, 0))


                                fd.ECS[k].subWidget.setPalette(palette)
                                fd.ECS[k].subWidget.setForegroundRole(QtGui.QPalette.Dark)

                                fd.ECS[k].subWidget.setAutoFillBackground(True)

    ##
    # @brief 未使用
    # @param self
    # @param rs 実行順序
    def UpdateRTC(self, rs):
        pass

	

    
    ##
    # @brief 初期化
    # @param self
    def newFile(self):

        for i in range(0, len(self.Comps)):
            self.Comps[i].mainWidget.close()

        self.Comps = []

        self.AddComps2()


	
