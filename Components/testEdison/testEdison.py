#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file testEdison.py
 @brief test intel Edison
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
testedison_spec = ["implementation_id", "testEdison", 
		 "type_name",         "testEdison", 
		 "description",       "test intel Edison", 
		 "version",           "1.0.0", 
		 "vendor",            "Miyamoto Nobuhiko", 
		 "category",          "TEST", 
		 "activity_type",     "STATIC", 
		 "max_instance",      "1", 
		 "language",          "Python", 
		 "lang_type",         "SCRIPT",
		 "conf.default.outValueDigital", "0",
		 "conf.default.outValuePWM", "0",
		 "conf.__widget__.outValueDigital", "radio",
		 "conf.__widget__.outValuePWM", "text",
		 "conf.__constraints__.outValueDigital", "(0,1)",
		 "conf.__constraints__.outValuePWM", "0<=x<=1",
		 ""]
# </rtc-template>

##
# @class testEdison
# @brief test intel Edison
# 
# Intel Edison用テスト用RTC
# 
# 
class testEdison(OpenRTM_aist.DataFlowComponentBase):
	
	##
	# @brief constructor
	# @param manager Maneger Object
	# 
	def __init__(self, manager):
		OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)

		self._d_in_adc = RTC.TimedDouble(RTC.Time(0,0),0)
		"""
		ADCコンポーネント(ADC_Edison)の出力を受け取って表示
		 - Type: RTC::TimedDouble
		"""
		self._in_adcIn = OpenRTM_aist.InPort("in_adc", self._d_in_adc)
		self._d_out_pwm = RTC.TimedDouble(RTC.Time(0,0),0)
		"""
		PWMコンポーネント(PWM_Edison)にデューティー比を入力
		 - Type: RTC::TimedDouble
		"""
		self._out_pwmOut = OpenRTM_aist.OutPort("out_pwm", self._d_out_pwm)
		self._d_out_dp = RTC.TimedBoolean(RTC.Time(0,0),0)
		"""
		デジタルピン制御RTC(DigitalOutput_Edison)にHighかLowを入力する
		 - Type: RTC::TimedBoolean
		"""
		self._out_dpOut = OpenRTM_aist.OutPort("out_dp", self._d_out_dp)


		


		# initialize of configuration-data.
		# <rtc-template block="init_conf_param">
		"""
		out_dpで出力する値を設定
		 - Name: outValueBoolean outValueDigital
		 - DefaultValue: 0
		 - Constraint: (0,1)
		"""
		self._outValueDigital = [0]
		"""
		out_pwmで出力する値を設定する
		 - Name: outValuePWM outValuePWM
		 - DefaultValue: 0
		"""
		self._outValuePWM = [0]
		
		# </rtc-template>


		 
	##
	#
	# The initialize action (on CREATED->ALIVE transition)
	# formaer rtc_init_entry() 
	# 
	# @return RTC::ReturnCode_t
	# 
	#
	def onInitialize(self):
		# Bind variables and configuration variable
		self.bindParameter("outValueDigital", self._outValueDigital, "0")
		self.bindParameter("outValuePWM", self._outValuePWM, "0")
		
		# Set InPort buffers
		self.addInPort("in_adc",self._in_adcIn)
		
		# Set OutPort buffers
		self.addOutPort("out_pwm",self._out_pwmOut)
		self.addOutPort("out_dp",self._out_dpOut)
		
		# Set service provider to Ports
		
		# Set service consumers to Ports
		
		# Set CORBA Service Ports
		
		return RTC.RTC_OK
	
		##
		# 
		# The finalize action (on ALIVE->END transition)
		# formaer rtc_exiting_entry()
		# 
		# @return RTC::ReturnCode_t
	
		# 
	def onFinalize(self):
	
		return RTC.RTC_OK
	
		##
		#
		# The startup action when ExecutionContext startup
		# former rtc_starting_entry()
		# 
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onStartup(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The shutdown action when ExecutionContext stop
		# former rtc_stopping_entry()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onShutdown(self, ec_id):
	
		return RTC.RTC_OK
	
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
	def onActivated(self, ec_id):
	
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
	def onDeactivated(self, ec_id):
	
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
	def onExecute(self, ec_id):
		self._d_out_pwm.data = self._outValuePWM[0]
		self._out_pwmOut.write()
		self._d_out_dp.data = self._outValueDigital[0]
		self._out_dpOut.write()
		if self._in_adcIn.isNew():
			data = self._in_adcIn.read()
			print "ADC: " + str(data.data)
		return RTC.RTC_OK
	
		##
		#
		# The aborting action when main logic error occurred.
		# former rtc_aborting_entry()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onAborting(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The error action in ERROR state
		# former rtc_error_do()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onError(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The reset action that is invoked resetting
		# This is same but different the former rtc_init_entry()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onReset(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The state update action that is invoked after onExecute() action
		# no corresponding operation exists in OpenRTm-aist-0.2.0
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#

		#
	def onStateUpdate(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The action that is invoked when execution context's rate is changed
		# no corresponding operation exists in OpenRTm-aist-0.2.0
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onRateChanged(self, ec_id):
	
		return RTC.RTC_OK
	



def testEdisonInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=testedison_spec)
    manager.registerFactory(profile,
                            testEdison,
                            OpenRTM_aist.Delete)

def MyModuleInit(manager):
    testEdisonInit(manager)

    # Create a component
    comp = manager.createComponent("testEdison")

def main():
	mgr = OpenRTM_aist.Manager.init(sys.argv)
	mgr.setModuleInitProc(MyModuleInit)
	mgr.activateManager()
	mgr.runManager()

if __name__ == "__main__":
	main()

