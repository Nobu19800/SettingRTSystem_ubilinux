#!/usr/bin/env python
# -*- coding: utf-8 -*-

##
#   @file CreateMultipleOrderedEC.py
#   @brief 実行順序の設定ができる実行コンテキスト


import threading
import time

import OpenRTM_aist
from MPTask import MPTask,GUITask
import MPComp

pyqtExist = True
try:
    from PyQt4 import QtCore, QtGui
except:
    pyqtExist = False



##
# @class MultipleOrderedEC
# @brief 実行順序の設定ができる実行コンテキスト
#
class MultipleOrderedEC(OpenRTM_aist.PeriodicExecutionContext):
    ##
    # @brief コンストラクタ
    # @param self 
    def __init__(self):
        
        OpenRTM_aist.PeriodicExecutionContext.__init__(self)
        
        
        
        self._rtcout = OpenRTM_aist.Manager.instance().getLogbuf("rtobject.mp_ec")
        self.prop = OpenRTM_aist.Manager.instance().getConfig()
        #print OpenRTM_aist.Manager.instance().getConfig()
        self.SetGui = "YES"
        self.FileName = ""
        #self.DebugFlag = ""
        self.SetGui = self.getProperty(self.prop, "exec_cxt.periodic.gui", self.SetGui)
        #print self.SetGui
        self.FileName = self.getProperty(self.prop, "exec_cxt.periodic.filename", self.FileName)
        #print self.FileName
        #self.DebugFlag = self.getProperty(self.prop, "exec_cxt.periodic.debug", self.DebugFlag)
        
        self.rs = []
        self.r_num = 0

        
        
        self.SetGui = [self.SetGui]
        OpenRTM_aist.eraseBlank(self.SetGui)
        self.SetGui = self.SetGui[0]

        self.FileName = [self.FileName]
        OpenRTM_aist.eraseBlank(self.FileName)
        self.FileName = self.FileName[0]

        
        #self.DebugFlag = [self.DebugFlag]
        #OpenRTM_aist.eraseBlank(self.DebugFlag)
        #self.DebugFlag = self.DebugFlag[0]


        self._mutex_del2 = threading.RLock()
        if self.SetGui == "YES":
            #print pyqtExist
            if pyqtExist:
                self.g_task = GUITask(self)
                self.g_task.activate()

        self.nameList = []
        self.comp_t = []
    
    ##
    # @brief rtc.confの設定を取得する関数
    # @param self 
    # @param prop プロパティ
    # @param key キー
    # @param value 値
    # @return 値
    def getProperty(self, prop, key, value):
        
        if  prop.findNode(key) != None:
            #print value
            value = prop.getProperty(key)
        return value
          
    ##
    # @brief RTCのリスト更新
    # @param self 
    def Update_Name(self):
        self._worker.updateComponentList()
        
        if self.comp_t == self._worker._comps:
            pass
        else:
            guard2 = OpenRTM_aist.ScopedLock(self._mutex_del2)
            self.comp_t = []
            self.nameList = []
            for i in range(0, len(self._worker._comps)):
                self.comp_t.append(self._worker._comps[i])
                self._worker._comps[i].i_name = self._worker._comps[i]._rtobj.get_component_profile().instance_name
                #self.nameList.append(self._worker._comps[i]._sm._obj.get_component_profile().instance_name)
            del guard2
    
    ##
    # @brief 番号からコンポーネントの名前取得の関数
    # @param self
    # @param num 番号
    # @return RTC名
    def getCompName(self, num):
        
        self.Update_Name()
        
        
        #guard2 = OpenRTM_aist.ScopedLock(self._mutex_del2)
        #Name = self._worker._comps[num]._sm._obj.get_component_profile().instance_name
        #del guard2
        #Name = self.nameList[num]
        Name = self._worker._comps[num].i_name
        return Name

    
    ##
    # @brief コンポーネントの数取得の関数
    # @param self
    # @return RTC数
    def getCompNum(self):
        return len(self._worker._comps)

    
    ##
    # @brief コンポーネントのロジック実行の関数
    # @param self
    # @param c ブロック
    def workerComp(self, c):
        sd = c.r in self._worker._comps
        
        #if self.DebugFlag == "YES":
        #    print c.v
        #print c.v, c.r


        if sd == True:
            #t0_ = OpenRTM_aist.Time()
            c.r._sm.worker()
            #t1_ = OpenRTM_aist.Time()
            #print c.v,(t1_ - t0_).getTime().toDouble()
        else:
            
            for i in range(0, len(self._worker._comps)):
                if c.v == self.getCompName(i):
                    c.r = self._worker._comps[i]
                    self._worker._comps[i]._sm.worker()

    
    ##
    # @brief 設定した実行順序のRTCを格納する関数
    # @param self
    def LoadRules(self):
        for h in range(0, len(self.rs)):
            for i in range(0, len(self.rs[h].ar)):
                for j in range(0, len(self._worker._comps)):
                    
                    #Name = self._worker._comps[j]._sm._obj.get_component_profile().instance_name
                    Name = self.getCompName(j)

                    if Name == self.rs[h].ar[i].name:
                        self.rs[h].ar[i].r = self._worker._comps[j]

            for i in range(0, len(self.rs[h].rs)):
                for j in range(0, len(self.rs[h].rs[i].SR)):
                    for k in range(0, len(self.rs[h].rs[i].SR[j])):
                        
                        for l in range(0, len(self._worker._comps)):
                            #Name = self._worker._comps[l]._sm._obj.get_component_profile().instance_name
                            Name = self.getCompName(l)
                            if Name == self.rs[h].rs[i].SR[j][k].v:
                                
                                self.rs[h].rs[i].SR[j][k].r = self._worker._comps[l]
        
    
    ##
    # @brief GUIから実行順序の読み込みの関数
    # @param self
    # @param RS_d 実行順序のリスト
    def LoadRuleGUI(self, RS_d):
        guard = OpenRTM_aist.ScopedLock(self._workerthread._mutex)

        self.rs = []
        self.rs = RS_d
        
        
        self.LoadRules()

        del guard
  
    
    ##
    # @brief ファイルから実行順序の読み込みの関数
    # @param self
    def LoadRule(self):
        
        
        guard = OpenRTM_aist.ScopedLock(self._workerthread._mutex)
        
        
        
        
        for h in range(0, len(self.rs)):
                self.rs[h].rs = []
        self.rs = []

        MPComp.LoadMainRule(self.rs, self.FileName)

        self.LoadRules()
        

        del guard

    
    ##
    # @brief スレッド実行関数
    # @param self
    # @return 0
    def svc(self):
        self._rtcout.RTC_TRACE("svc()")
        #flag = True
        count_ = 0

        self.LoadRule()
        
    
        
        #while flag:
        while self.threadRunning():
            
            guard = OpenRTM_aist.ScopedLock(self._workerthread._mutex)
            #self.LoadRules()
            #self._worker._cond.acquire()
            #while not self._worker._running:
            #    self._worker._cond.wait()
            
            while not self._workerthread._running:
                self._workerthread._cond.wait()

            self._worker.updateComponentList()

            t0_ = OpenRTM_aist.Time()

            if self._worker._running:
                
                for i in range(0, len(self.rs)):
                    S = True
                    for j in range(0, len(self.rs[i].ar)):
                        
                        Flag = False
                        for k in range(0, len(self._worker._comps)):
                            if self.rs[i].ar[j].r == self._worker._comps[k]:
                                
                                if self.rs[i].ar[j].state == -1:
                                    
                                    pass
                                else:
                                    if self.rs[i].ar[j].state != self._worker._comps[k]._sm.get_state():
                                        S = False
                        if Flag == False:
                            for k in range(0, len(self._worker._comps)):
                                if self.getCompName(k) == self.rs[i].ar[j].name:
                                    self.rs[i].ar[j].r = self._worker._comps[k]
                                    if self.rs[i].ar[j].state == -1:
                                        pass
                                    else:
                                        if self.rs[i].ar[j].state != self._worker._comps[k]._sm.get_state():
                                            S = False

                    if S == True:
                        self.r_num = i
                        break
                        
                if self.r_num < len(self.rs):
                    
                    for i in range(0, len(self.rs[self.r_num].rs)):
                        
                        if len(self.rs[self.r_num].rs[i].SR) == 0:
                            pass
                        elif len(self.rs[self.r_num].rs[i].SR) == 1:
                            
                            for j in range(0, len(self.rs[self.r_num].rs[i].SR[0])):
                                self.rs[self.r_num].rs[i].SR[0][j].s = 1
                                """sd = self.rs[self.r_num].rs[i].SR[0][j].r in self._worker._comps
                                print self.rs[self.r_num].rs[i].SR[0][j].v,self.rs[self.r_num].rs[i].SR[0][j].r
                                if sd == True:
                                    self.rs[self.r_num].rs[i].SR[0][j].r._sm.worker()"""
                                self.workerComp(self.rs[self.r_num].rs[i].SR[0][j])
                                self.rs[self.r_num].rs[i].SR[0][j].s = 0

                        else:
                                
                               p_num = len(self.rs[self.r_num].rs[i].SR)
                               m_task = []
                               for j in range(0, p_num):
                                   m_task_s = MPTask(self)
                                   m_task.append(m_task_s)
                                   for k in range(0, len(self.rs[self.r_num].rs[i].SR[j])):
                                       m_task_s.addComp(self.rs[self.r_num].rs[i].SR[j][k],i,j,k)
                                   m_task_s.activate()
                               for j in range(0, p_num):
                                   m_task[j].wait()
                                   m_task[j].close()
            
                
            

            #self._worker._cond.release()

            del guard

            t1_ = OpenRTM_aist.Time()

            period_ = self.getPeriod()

            if count_ > 1000:
                exctm_ = (t1_ - t0_).getTime().toDouble()
                #slptm_ = self._period.toDouble() - exctm_
                slptm_ = period_.toDouble() - exctm_
                self._rtcout.RTC_PARANOID("Period:    %f [s]", period_.toDouble())
                self._rtcout.RTC_PARANOID("Execution: %f [s]", exctm_)
                self._rtcout.RTC_PARANOID("Sleep:     %f [s]", slptm_)

            t2_ = OpenRTM_aist.Time()

            if not self._nowait and period_.toDouble() > ((t1_ - t0_).getTime().toDouble()):
                if count_ > 1000:
                    self._rtcout.RTC_PARANOID("sleeping...")
                slptm_ = period_.toDouble() - (t1_ - t0_).getTime().toDouble()
                time.sleep(slptm_)

            if count_ > 1000:
                t3_ = OpenRTM_aist.Time()
                self._rtcout.RTC_PARANOID("Slept:     %f [s]", (t3_ - t2_).getTime().toDouble())
                count_ = 0
            count_ += 1
            #flag = self._running
        
        return 0
    

  

##
# @brief 実行コンテキスト初期化関数
# @param manager マネージャオブジェクト
def MultipleOrderedECInit(manager):
  
  OpenRTM_aist.ExecutionContextFactory.instance().addFactory("MultipleOrderedEC",
                            MultipleOrderedEC,
                            OpenRTM_aist.ECDelete)
  
