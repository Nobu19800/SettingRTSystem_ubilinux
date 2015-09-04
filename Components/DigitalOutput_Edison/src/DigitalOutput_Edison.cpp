// -*- C++ -*-
/*!
 * @file  DigitalOutput_Edison.cpp
 * @brief Digital Output
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "DigitalOutput_Edison.h"

// Module specification
// <rtc-template block="module_spec">
static const char* digitaloutput_edison_spec[] =
  {
    "implementation_id", "DigitalOutput_Edison",
    "type_name",         "DigitalOutput_Edison",
    "description",       "Digital Output",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Device",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.pin", "2",
    // Widget
    "conf.__widget__.pin", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
DigitalOutput_Edison::DigitalOutput_Edison(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inIn("in", m_in)

    // </rtc-template>
{
	gpio = NULL;
	last_pin = -1;
}

/*!
 * @brief destructor
 */
DigitalOutput_Edison::~DigitalOutput_Edison()
{

}



RTC::ReturnCode_t DigitalOutput_Edison::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in", m_inIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("pin", m_pin, "2");
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DigitalOutput_Edison::onFinalize()
{
	if(gpio)
	{
		gpio->write(0);
		delete gpio;
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DigitalOutput_Edison::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DigitalOutput_Edison::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DigitalOutput_Edison::onActivated(RTC::UniqueId ec_id)
{
	if(last_pin != m_pin)
	{
		if(gpio)
		{
			gpio->write(0);
			delete gpio;
		}
		gpio = new mraa::Gpio(m_pin);
		mraa_result_t response = gpio->dir(mraa::DIR_OUT);
		
		if (response != MRAA_SUCCESS) {
			gpio = NULL;
	        	return RTC::RTC_ERROR;
	    	}
		last_pin = m_pin;
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DigitalOutput_Edison::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DigitalOutput_Edison::onExecute(RTC::UniqueId ec_id)
{
	if(gpio)
	{
		if(m_inIn.isNew())
		{
			m_inIn.read();
			if(m_in.data)gpio->write(1);
			else gpio->write(0);
			
		}
		
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DigitalOutput_Edison::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DigitalOutput_Edison::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DigitalOutput_Edison::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DigitalOutput_Edison::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DigitalOutput_Edison::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void DigitalOutput_EdisonInit(RTC::Manager* manager)
  {
    coil::Properties profile(digitaloutput_edison_spec);
    manager->registerFactory(profile,
                             RTC::Create<DigitalOutput_Edison>,
                             RTC::Delete<DigitalOutput_Edison>);
  }
  
};


