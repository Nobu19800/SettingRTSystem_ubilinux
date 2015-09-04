#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file ECandStateSharedComposite.py
 @brief EC and State Shared Composite Component
 @date $Date$


 LGPL

"""
import sys
import time
sys.path.append(".")

# Import RTM module
import RTC
import OpenRTM_aist


# Import Service implementation class
# <rtc-template block="service_impl">

# </rtc-template>

# Import Service stub modules
# <rtc-template block="consumer_import">
# </rtc-template>


# This module's spesification
# <rtc-template block="module_spec">
ecandstatesharedcomposite_spec = ["implementation_id", "ECandStateSharedComposite", 
		 "type_name",         "ECandStateSharedComposite", 
		 "description",       "EC and State Shared Composite Component", 
		 "version",           "1.0.0", 
		 "vendor",            "Miyamoto Nobuhiko", 
		 "category",          "composite.PeriodicECShared", 
		 "activity_type",     "STATIC", 
		 "max_instance",      "1", 
		 "language",          "Python", 
		 "lang_type",         "SCRIPT",
		 "conf.default.members", "",
		 "conf.default.exported_ports", "",
		 ""]
# </rtc-template>

##
# @class ECandStateSharedComposite
# @brief EC and State Shared Composite Component
# 
# 実行コンテキスト、状態を共有する複合コンポーネント
# 
# 
class ECandStateSharedComposite(OpenRTM_aist.PeriodicECSharedComposite):
	
	##
	# @brief constructor
	# PeriodicECSharedComposite.pyのPeriodicECSharedCompositeのコンストラクタを一部改編
	# @param manager Maneger Object
	# 
	def __init__(self, manager):
		#OpenRTM_aist.PeriodicECSharedComposite.__init__(self, manager)
		OpenRTM_aist.RTObject_impl.__init__(self,manager)
		self._ref = self._this()
		self._objref = self._ref
		self._org = OpenRTM_aist.PeriodicECOrganization(self)
		OpenRTM_aist.CORBA_SeqUtil.push_back(self._sdoOwnedOrganizations,self._org.getObjRef())

		self._members = [[]]
		self.bindParameter("members", self._members, " ", OpenRTM_aist.stringToStrVec)
		self._rtcout = OpenRTM_aist.Manager.instance().getLogbuf("rtobject.periodic_ec_shared")
		self._configsets.addConfigurationSetListener(\
		OpenRTM_aist.ConfigurationSetListenerType.ON_SET_CONFIG_SET,
		OpenRTM_aist.setCallback(self._org))

		self._configsets.addConfigurationSetListener(\
		OpenRTM_aist.ConfigurationSetListenerType.ON_ADD_CONFIG_SET,
		OpenRTM_aist.addCallback(self._org))
		
	
		
		#self._members = [[]]
		#self.bindParameter("members", self._members, "p", OpenRTM_aist.stringToStrVec)

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
	#def onInitialize(self):
		#self.bindParameter("members", self._members,"0.0,1.0,2.0,3.0,4.0")
		# Bind variables and configuration variable
		
		# Set InPort buffers
		
		# Set OutPort buffers
		
		# Set service provider to Ports
		
		# Set service consumers to Ports
		
		# Set CORBA Service Ports
		
		#return RTC.RTC_OK
	
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
	
	#	##
	#	#
	#	# The activated action (Active state entry action)
	#	# former rtc_active_entry()
	#	#
	#	# @param ec_id target ExecutionContext Id
	#	# 
	#	# @return RTC::ReturnCode_t
	#	#
	#	#
	#def onActivated(self, ec_id):
	#
	#	return RTC.RTC_OK
	
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
	#def onDeactivated(self, ec_id):
	
	#	return RTC.RTC_OK
	
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
	def onExecute(self, ec_id):
		
		#print self._members
		self._rtcout.RTC_TRACE("onExecute(%d)", ec_id)
		ecs = self.get_owned_contexts()
		sdos = self._org.get_members()

		for sdo in sdos:
			rtc = sdo._narrow(RTC.RTObject)
			if OpenRTM_aist.RTC.ERROR_STATE == ecs[0].get_component_state(rtc):
				return RTC.RTC_ERROR
			
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
	



def ECandStateSharedCompositeInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=ecandstatesharedcomposite_spec)
    manager.registerFactory(profile,
                            ECandStateSharedComposite,
                            OpenRTM_aist.Delete)

def MyModuleInit(manager):
    ECandStateSharedCompositeInit(manager)

    # Create a component
    comp = manager.createComponent("ECandStateSharedComposite")

def main():
	mgr = OpenRTM_aist.Manager.init(sys.argv)
	mgr.setModuleInitProc(MyModuleInit)
	mgr.activateManager()
	mgr.runManager()

if __name__ == "__main__":
	main()

