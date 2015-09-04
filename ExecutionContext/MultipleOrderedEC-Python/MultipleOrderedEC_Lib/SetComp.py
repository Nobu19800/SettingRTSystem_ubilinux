# -*- coding: utf-8 -*-

##
#   @file SetComp.py
#   @brief 全実行順序のブロック表示ウィジェット

from PyQt4 import QtCore, QtGui
from FrameComp import FrameComp
import MPComp
import OpenRTM_aist

import struct




##
# @class SetComp
# @brief 全実行順序のブロック表示ウィジェット
#
class SetComp(QtGui.QTabWidget):
    UpdateSizeSignal = QtCore.pyqtSignal(int,int)
    ##
    # @brief コンストラクタ
    # @param self 
    # @param ec 実行コンテキストオブジェクト
    # @param parent 親ウィジェット
    def __init__(self, ec, parent=None):
        super(SetComp, self).__init__(parent)

        self.rtclist = []
        self.rtclist2 = []
        self.FCS = []
        
        self.m_ec = ec

	

	

	

        self.currentChanged.connect(self.UpdateSizeSlot)

	

        self.time = QtCore.QTimer(self)


        self.time.timeout.connect(self.UpdateEC)

	

        self.time.start(100)

	

        if self.open(self.m_ec.FileName) == False:
            self.newFile()

    
    ##
    # @brief 実行順序の削除の関数
    # @param self 
    # @param fc 実行順序ウィジェット
    def DeleteComp(self, fc):

        self.FCS.remove(fc)


        self.removeTab(self.indexOf(fc))
        self.removeTab(self.indexOf(fc.cf))

        fc.cf.close()
        fc.close()

    
    ##
    # @brief 実行順序追加のスロット
    # @param self 
    def CreateComp(self):

        FC = FrameComp(self.m_ec, self)


        FC.UpdateSizeSignal.connect(self.UpdateSizeSlot)

        self.FCS.append(FC)

        N = "system:" + str(len(self.FCS))
        self.addTab(FC, N)
        N = N + u"条件"
        self.addTab(FC.cf, N)

	
	


	

    
    ##
    # @brief ファイル保存スロット
    # @param self
    # @param Name ファイル名
    # @return 成功でTrue、失敗でFalse
    def save(self, Name):

        mR = []

    
        ofs2 = open(Name, 'wb')


        c = len(self.FCS)
        a = struct.pack("i", c)
        ofs2.write(a)

        for i in range(0, len(self.FCS)):
            self.FCS[i].save(ofs2, mR)


        self.m_ec.LoadRuleGUI(mR)

        ofs2.close()
        return True

    
    ##
    # @brief ブロック図に現在のRTCのリストを反映するスロット
    # @param self
    def UpdateComp2(self):
        

        for h in range(0, len(self.FCS)):

            self.FCS[h].cf.resetComp()

            for i in range(0, len(self.rtclist)):

                self.FCS[h].cf.addComp(self.rtclist[i])



            self.FCS[h].UpdateComp2(self.rtclist, self.rtclist2)


        for h in range(0, len(self.m_ec.rs)):
            if len(self.FCS) > h:

                ar = self.m_ec.rs[h].ar


                for i in range(0, len(ar)):

                    for j in range(0, len(self.FCS[h].cf.Cl)):

                        if self.FCS[h].cf.Cl[j].Name == ar[i].name:

                            if ar[i].state == -1:

                                self.FCS[h].cf.Cl[j].c_none.setChecked(True)

                            elif ar[i].state == OpenRTM_aist.RTC.CREATED_STATE:

                                self.FCS[h].cf.Cl[j].c_created.setChecked(True)

                            elif ar[i].state == OpenRTM_aist.RTC.INACTIVE_STATE:

                                self.FCS[h].cf.Cl[j].c_inactive.setChecked(True)

                            elif ar[i].state == OpenRTM_aist.RTC.ACTIVE_STATE:

                                self.FCS[h].cf.Cl[j].c_active.setChecked(True)

                            elif ar[i].state == OpenRTM_aist.RTC.ERROR_STATE:

                                self.FCS[h].cf.Cl[j].c_error.setChecked(True)

						
					
				
			

			


                rs = self.m_ec.rs[h].rs


                for i in range(0, len(rs)):
                    
                    if len(self.FCS[h].Comps) > i:

                        for j in range(0, len(rs[i].SR)):

                            if len(self.FCS[h].Comps[i].VL) > j:

                                fd = self.FCS[h].Comps[i].VL[j].layout().itemAt(1).widget()

                                for k in range(0, len(rs[i].SR[j])):

                                    if len(fd.ECS) > k:


                                        for l in range(0, fd.ECS[k].CB.count()):

                                            if fd.ECS[k].CB.itemText(l) == rs[i].SR[j][k].v:

                                                fd.ECS[k].CB.setCurrentIndex(l)

    
    ##
    # @brief RTCが追加、削除されたときにブロック図に反映するスロット
    # @param self
    def UpdateComps(self):

		Size = self.m_ec.getCompNum()
		

		rtclist3 = []
		rtclist4 = []

	

	

		for i in range(0, Size):
			rtclist3.append(self.m_ec.getCompName(i))
	

		if self.rtclist == rtclist3:
			pass
		

	
		else:
			self.rtclist = []
			self.rtclist = rtclist3

		
			self.UpdateComp2()

		
	




    ##
    # @brief ファイル読み込みスロット
    # @param self
    # @param Name ファイル名
    # @return 成功でTrue、失敗でFalse
    def open(self, Name):

        mR = []

        if MPComp.LoadMainRule(mR, Name) == False:
            return False

        for i in range(0, len(self.FCS)):

            self.removeTab(self.indexOf(self.FCS[i]))
            self.removeTab(self.indexOf(self.FCS[i].cf))

            self.FCS[i].cf.close()
            self.FCS[i].close()

		


        self.FCS = []

        for i in range(0, len(mR)):
            self.CreateComp()


            self.FCS[i].SetFrame(mR[i])

	


        self.m_ec.LoadRuleGUI(mR)

	

	

        self.UpdateComps()
        self.UpdateComp2()



        return True

    
    ##
    # @brief 実行しているRTCのブロックの色を変えるスロット
    # @param self
    def UpdateEC(self):

        for h in range(0, len(self.m_ec.rs)):

            rs = self.m_ec.rs[h].rs
            if len(self.FCS) > h:

                self.FCS[h].UpdateEC(rs)


        self.UpdateComps()


    
    ##
    # @brief サイズ変更時に呼ばれるスロット
    # @param self
    def UpdateSizeSlot(self):
         


        maxX = 0
        maxY = 0


        if self.currentIndex()%2 == 0:

            if self.currentIndex()/2 < len(self.FCS):

                maxX = self.FCS[self.currentIndex()/2].X
                maxY = self.FCS[self.currentIndex()/2].Y

	

        if maxX < 450:
            maxX = 450
        if maxY < 600:
            maxY = 600

	


        self.UpdateSizeSignal.emit(maxX, maxY)

        self.UpdateComps()

	

    ##
    # @brief 未使用
    # @param self
    def UpdateComp(self):

        pass

	

    
    ##
    # @brief ボタンクリック時に呼び出すスロット
    # @param self
    # @param rs 実行順序
    def UpdateRTC(self, rs):

        self.FCS[0].UpdateRTC(rs)

    
    ##
    # @brief 初期化
    # @param self
    def newFile(self):

        for i in range(0, len(self.FCS)):

            self.removeTab(self.indexOf(self.FCS[i]))
            self.removeTab(self.indexOf(self.FCS[i].cf))

            self.FCS[i].cf.close()
            self.FCS[i].close()

		


        self.FCS = []

        self.CreateComp()
        self.FCS[0].newFile()




        
