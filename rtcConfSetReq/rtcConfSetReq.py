#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

##
#   @file rtcConfSetReq.py
#   @brief RTC設定ファイル操作RTC(コンシュマー側)

import sys
import time
sys.path.append(".")

# Import RTM module
import RTC
import OpenRTM_aist

import os
sys.path.append(os.path.abspath("../RTCD_IDL"))

import rtcconf_idl

# Import Service implementation class
# <rtc-template block="service_impl">

# </rtc-template>

# Import Service stub modules
# <rtc-template block="consumer_import">
import RTCConfData, RTCConfData__POA


# </rtc-template>


# This module's spesification
# <rtc-template block="module_spec">
rtcconfsetreq_spec = ["implementation_id", "rtcConfSetReq", 
		 "type_name",         "rtcConfSetReq", 
		 "description",       "rtcConfSetReq", 
		 "version",           "1.0.0", 
		 "vendor",            "Miyamoto Nobuhiko", 
		 "category",          "TES", 
		 "activity_type",     "STATIC", 
		 "max_instance",      "1", 
		 "language",          "Python", 
		 "lang_type",         "SCRIPT",
		 ""]
# </rtc-template>

##
# @class rtcConfSetReq
# @brief RTC設定ファイル操作RTC(コンシュマー側)
# 
# 
class rtcConfSetReq(OpenRTM_aist.DataFlowComponentBase):
	
	##
	# @brief コンストラクタ
	# @param self
	# @param manager マネージャオブジェクト
	# 
	def __init__(self, manager):
		OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)

		        
		"""
		"""
		self._rtcconfPort = OpenRTM_aist.CorbaPort("rtcconf")

		

		"""
		"""
		self._rtcconf = OpenRTM_aist.CorbaConsumer(interfaceType=RTCConfData.ConfDataInterface)

		# initialize of configuration-data.
		# <rtc-template block="init_conf_param">
		
		# </rtc-template>

        

	##
	# @brief 初期化処理用コールバック関数
	# @param self 
	# @return RTC::ReturnCode_t
	def onInitialize(self):
		# Bind variables and configuration variable
		
		# Set InPort buffers
		
		# Set OutPort buffers
		
		# Set service provider to Ports
		
		# Set service consumers to Ports
		self._rtcconfPort.registerConsumer("rtcconf", "RTCConfData::ConfDataInterface", self._rtcconf)
		
		# Set CORBA Service Ports
		self.addPort(self._rtcconfPort)
		
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
	# @brief 活性化処理用コールバック関数
	# @param self 
	# @param ec_id target ExecutionContext Id
	# @return RTC::ReturnCode_t
	def onActivated(self, ec_id):
	
		return RTC.RTC_OK
	
	##
	# @brief 不活性化処理用コールバック関数
	# @param self 
	# @param ec_id target ExecutionContext Id
	# @return RTC::ReturnCode_t
	def onDeactivated(self, ec_id):
	
		return RTC.RTC_OK
	
	##
	# @brief 周期処理用コールバック関数
	# @param self 
	# @param ec_id target ExecutionContext Id
	# @return RTC::ReturnCode_t
	def onExecute(self, ec_id):
		
		"""try:
			self._rtcconf._ptr().open("./test.txt")
			#print self._rtcconf._ptr().getDataSeq_Cpp()
			self._rtcconf._ptr().startRTCD_Cpp()
			self._rtcconf._ptr().startRTCD_Py()
			print self._rtcconf._ptr().getData_Cpp("corba.nameservers")
			#self._rtcconf._ptr().setData_Cpp(RTCConfData.confData("corba.nameservers","test"))
		except:
			pass"""
		
		return RTC.RTC_OK

	##
	# @brief 辞書オブジェクトからRTCConfData.confDataに変換
	# @param self 
	# @param datas 辞書(name:名前、value:値)のリスト
	# @return RTCConfData.confDataのリスト
	def convConfData(self, datas):
		confData = []
		
		for d in datas:
			confData.append(RTCConfData.confData(d["name"], d["value"]))
		return confData
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
	



def rtcConfSetReqInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=rtcconfsetreq_spec)
    manager.registerFactory(profile,
                            rtcConfSetReq,
                            OpenRTM_aist.Delete)
    

def MyModuleInit(manager):
    rtcConfSetReqInit(manager)

    # Create a component
    comp = manager.createComponent("rtcConfSetReq")

def main():
	mgr = OpenRTM_aist.Manager.init(sys.argv)
	mgr.setModuleInitProc(MyModuleInit)
	mgr.activateManager()
	mgr.runManager()
	
	

if __name__ == "__main__":
	main()

