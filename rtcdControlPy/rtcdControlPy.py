#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file rtcdControlPy.py
 @brief rtcdControlPy
 @date $Date$


"""
import sys
import traceback
import os
import time
sys.path.append(".")

import rtctree.tree

# Import RTM module
import RTC
import OpenRTM_aist

import imp

import LoadRTCs

import rtcControl_idl

# Import Service implementation class
# <rtc-template block="service_impl">
import omniORB
from omniORB import CORBA, PortableServer
import rtcControl, rtcControl__POA




##
# @class RTCDataInterface_i
# @brief 起動するRTCの操作のインターフェース
# 
# 
class RTCDataInterface_i (rtcControl__POA.RTCDataInterface):
    ##
    # @brief コンストラクタ
    # @param self
    # @param comp rtcdControlPyコンポーネントオブジェクト
    # 
    def __init__(self, comp):
        """
        @brief standard constructor
        Initialise member variables here
        """
        self.comp = comp
        #self.compList = {}
        self.LoadRTCs = LoadRTCs.LoadRTCs(comp.manager)
        self.LoadRTCs.openFile()

    ##
    # @brief 起動中のRTCのリスト取得
    # @param self
    # @return (True,RTCのリスト)
    # 
    def getRTC(self):
        return (True, self.comp.getNameList())
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result, paths

    ##
    # @brief RTCの起動
    # @param self
    # @param name RTC名
    # @param filename　ファイル名
    # @param filepath ディレクトリパス
    # @return 成功でTrue、失敗でFalse
    # 
    def createComp(self, name, filename, filepath):
        return self.LoadRTCs.createComp(name, filename, filepath)
    
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result

    

    ##
    # @brief RTCの終了
    # @param self
    # @param filename RTC名
    # @return 成功でTrue、失敗でFalse
    # 
    def removeComp(self, filename):
        return self.LoadRTCs.createComp(filename)
        
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result

    ##
    # @brief 起動中のRTCのリスト取得
    # @param self
    # @return RTCのリスト
    # 
    def getCompList(self):
        return self.LoadRTCs.getCompList()
        


# </rtc-template>

# Import Service stub modules
# <rtc-template block="consumer_import">
# </rtc-template>


# This module's spesification
# <rtc-template block="module_spec">
rtcdcontrolpy_spec = ["implementation_id", "rtcdControlPy", 
		 "type_name",         "rtcdControlPy", 
		 "description",       "rtcdControlPy", 
		 "version",           "1.0.0", 
		 "vendor",            "Miyamoto Nobuhiko", 
		 "category",          "TEST", 
		 "activity_type",     "STATIC", 
		 "max_instance",      "1", 
		 "language",          "Python", 
		 "lang_type",         "SCRIPT",
		 ""]
# </rtc-template>

##
# @class rtcdControlPy
# @brief rtcdControlPy
# 
# 
class rtcdControlPy(OpenRTM_aist.DataFlowComponentBase):
	
	##
	# @brief constructor
	# @param manager Maneger Object
	# 
	def __init__(self, manager):
		OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)

		self.manager = manager
		"""
		"""
		self._rtcControl_pyPort = OpenRTM_aist.CorbaPort("rtcControl_py")

		"""
		"""
		self._rtcControl_py = RTCDataInterface_i(self)
		
		#print self._rtcControl_py.createComp("MySecondComponent","..\\Components\\MySecondComponent")
		


		# initialize of configuration-data.
		# <rtc-template block="init_conf_param">
		
		# </rtc-template>


		 
	##
	#
	# The initialize action (on CREATED->ALIVE transition)
	# formaer rtc_init_entry() 
	# 
	# @return RTC::ReturnCode_t
	# 
	#
	##
	# @brief 初期化処理用コールバック関数
	# @param self 
	# @return RTC::ReturnCode_t
	def onInitialize(self):
		# Bind variables and configuration variable
		
		# Set InPort buffers
		
		# Set OutPort buffers
		
		# Set service provider to Ports
		self._rtcControl_pyPort.registerProvider("rtcControl_py", "rtcControl::RTCDataInterface", self._rtcControl_py)
		
		# Set service consumers to Ports
		
		# Set CORBA Service Ports
		self.addPort(self._rtcControl_pyPort)
		
		return RTC.RTC_OK
	
	#	##
	#	# 
	#	# The finalize action (on ALIVE->END transition)
	#	# formaer rtc_exiting_entry()
	#	# 
	#	# @return RTC::ReturnCode_t
	#
	#	# 
	#def onFinalize(self):
	#
	#	return RTC.RTC_OK
	
	#	##
	#	#
	#	# The startup action when ExecutionContext startup
	#	# former rtc_starting_entry()
	#	# 
	#	# @param ec_id target ExecutionContext Id
	#	#
	#	# @return RTC::ReturnCode_t
	#	#
	#	#
	#def onStartup(self, ec_id):
	#
	#	return RTC.RTC_OK
	
	#	##
	#	#
	#	# The shutdown action when ExecutionContext stop
	#	# former rtc_stopping_entry()
	#	#
	#	# @param ec_id target ExecutionContext Id
	#	#
	#	# @return RTC::ReturnCode_t
	#	#
	#	#
	#def onShutdown(self, ec_id):
	#
	#	return RTC.RTC_OK
	
		##
		#
		# The activated action (Active state entry action)
		# former rtc_active_entry()
		#
		# @param ec_id target ExecutionContext Id
		# 
		# @return RTC::ReturnCode_t
		#
		#
	##
	# @brief 活性化処理用コールバック関数
	# @param self 
	# @param ec_id target ExecutionContext Id
	# @return RTC::ReturnCode_t
	def onActivated(self, ec_id):
                """try:
                    self._rtcControl_py.createComp("MySecondComponent","..\\Components\\MySecondComponent")
                    self._rtcControl_py.createComp("MySecondComponent","..\\Components\\MySecondComponent")
                    self._rtcControl_py.createComp("MySecondComponent","..\\Components\\MySecondComponent")
                except:
                    info = sys.exc_info()
                    tbinfo = traceback.format_tb( info[2] )
                    for tbi in tbinfo:
                        print tbi"""
                
		return RTC.RTC_OK
	
		##
		#
		# The deactivated action (Active state exit action)
		# former rtc_active_exit()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	##
	# @brief 不活性化処理用コールバック関数
	# @param self 
	# @param ec_id target ExecutionContext Id
	# @return RTC::ReturnCode_t
	def onDeactivated(self, ec_id):
            #for c in self._rtcControl_py.compList["MySecondComponent"]["compList"]:
            #    print c._exiting
            """try:
                print self._rtcControl_py.getCompList()
            except:
                info = sys.exc_info()
                tbinfo = traceback.format_tb( info[2] )
                for tbi in tbinfo:
                    print tbi"""
            return RTC.RTC_OK
	
		##
		#
		# The execution action that is invoked periodically
		# former rtc_active_do()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	##
	# @brief 起動中のRTCのリスト
	# @param self 
	# @return RTCのリスト
	def getNameList(self):
		ans = []
		objs = self.manager.getComponents()
		for o in objs:
				props = o.getProperties()
				ans.append(props.findNode("naming").getProperty("names"))
		return ans

	##
	# @brief 周期処理用コールバック関数
	# @param self 
	# @param ec_id target ExecutionContext Id
	# @return RTC::ReturnCode_t
	def onExecute(self, ec_id):
		
		#print self.getNameList()
		return RTC.RTC_OK
	
	#	##
	#	#
	#	# The aborting action when main logic error occurred.
	#	# former rtc_aborting_entry()
	#	#
	#	# @param ec_id target ExecutionContext Id
	#	#
	#	# @return RTC::ReturnCode_t
	#	#
	#	#
	#def onAborting(self, ec_id):
	#
	#	return RTC.RTC_OK
	
	#	##
	#	#
	#	# The error action in ERROR state
	#	# former rtc_error_do()
	#	#
	#	# @param ec_id target ExecutionContext Id
	#	#
	#	# @return RTC::ReturnCode_t
	#	#
	#	#
	#def onError(self, ec_id):
	#
	#	return RTC.RTC_OK
	
	#	##
	#	#
	#	# The reset action that is invoked resetting
	#	# This is same but different the former rtc_init_entry()
	#	#
	#	# @param ec_id target ExecutionContext Id
	#	#
	#	# @return RTC::ReturnCode_t
	#	#
	#	#
	#def onReset(self, ec_id):
	#
	#	return RTC.RTC_OK
	
	#	##
	#	#
	#	# The state update action that is invoked after onExecute() action
	#	# no corresponding operation exists in OpenRTm-aist-0.2.0
	#	#
	#	# @param ec_id target ExecutionContext Id
	#	#
	#	# @return RTC::ReturnCode_t
	#	#

	#	#
	#def onStateUpdate(self, ec_id):
	#
	#	return RTC.RTC_OK
	
	#	##
	#	#
	#	# The action that is invoked when execution context's rate is changed
	#	# no corresponding operation exists in OpenRTm-aist-0.2.0
	#	#
	#	# @param ec_id target ExecutionContext Id
	#	#
	#	# @return RTC::ReturnCode_t
	#	#
	#	#
	#def onRateChanged(self, ec_id):
	#
	#	return RTC.RTC_OK
	


##
# @brief RTCをファクトリに追加
# @param manager マネージャーオブジェクト
def rtcdControlPyInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=rtcdcontrolpy_spec)
    manager.registerFactory(profile,
                            rtcdControlPy,
                            OpenRTM_aist.Delete)
    # Create a component
    comp = manager.createComponent("rtcdControlPy")

##
# @brief RTC初期化
# @param manager マネージャーオブジェクト
def MyModuleInit(manager):
    rtcdControlPyInit(manager)

    
    
    
def main():
	mgr = OpenRTM_aist.Manager.init(sys.argv)
	mgr.setModuleInitProc(MyModuleInit)
	
	mgr.activateManager()
	mgr.runManager()

        """
	# Create a component
        comp1 = mgr.createComponent("rtcdControlPy")
        comp2 = mgr.createComponent("rtcdControlPy")
        #comp = manager.createComponent("rtcdControlPy")

        comp = mgr.createComponent("PeriodicECSharedComposite?&instance_name=CompositeRTC")
        #print comp.getObjRef().add_members
        comp.getObjRef().get_owned_organizations()[0].add_members([comp1.getObjRef()])
        #comp.getObjRef().get_owned_organizations()[0].add_members([comp2.getObjRef()])

        props = comp.getProperties()
        name = props.findNode("naming").getProperty("names")

        time.sleep(2)
        
        tree = rtctree.tree.RTCTree(servers='localhost', orb=mgr.getORB())

        path = ['/', 'localhost']
        nlist = name.split("/")
        for n in nlist:
            path.append(n)

        c = tree.get_node(path)
        #c.set_conf_set_value('default', 'exported_ports', "rtcdControlPy1.rtcControl_py,rtcdControlPy0.rtcControl_py")
        #c.activate_conf_set('default')
	#cproperties = OpenRTM_aist.Properties("default2")
        #cproperties.setProperty("exported_ports", "rtcdControlPy0.rtcControl_py")
        #cproperties.setProperty("members", "")

        
        #comp._configsets.setConfigurationSetValues(cproperties)
        #comp._configsets.update("default","exported_ports")

        while(True):
            pass"""

if __name__ == "__main__":
	main()

