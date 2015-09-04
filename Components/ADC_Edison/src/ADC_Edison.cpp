// -*- C++ -*-
/*!
 * @file  ADC_Edison.cpp
 * @brief AD Converter
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "ADC_Edison.h"

// Module specification
// <rtc-template block="module_spec">
static const char* adc_edison_spec[] =
  {
    "implementation_id", "ADC_Edison",
    "type_name",         "ADC_Edison",
    "description",       "AD Converter",
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
    "conf.default.voltage", "5",
    // Widget
    "conf.__widget__.pin", "radio",
    "conf.__widget__.voltage", "text",
    // Constraints
    "conf.__constraints__.pin", "(0,1,2,3)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ADC_Edison::ADC_Edison(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_outOut("out", m_out)

    // </rtc-template>
{
	a = NULL;
	last_pin = -1;
}

/*!
 * @brief destructor
 */
ADC_Edison::~ADC_Edison()
{

}



RTC::ReturnCode_t ADC_Edison::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("out", m_outOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("pin", m_pin, "2");
  bindParameter("voltage", m_voltage, "5");
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_Edison::onFinalize()
{
	if(a)
	{
		delete a;
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_Edison::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_Edison::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_Edison::onActivated(RTC::UniqueId ec_id)
{
	if(last_pin != m_pin)
	{
		if(a)
		{
			delete a;
		}
		a = new mraa::Aio(m_pin);
		if (a == NULL) {
			return RTC::RTC_ERROR;
	    	}
		last_pin = m_pin;
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_Edison::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_Edison::onExecute(RTC::UniqueId ec_id)
{
	if(a)
	{
		double vol = (double)a->readFloat();
		m_out.data = vol*m_voltage;
		setTimestamp(m_out);
		m_outOut.write();
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_Edison::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_Edison::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_Edison::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_Edison::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_Edison::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void ADC_EdisonInit(RTC::Manager* manager)
  {
    coil::Properties profile(adc_edison_spec);
    manager->registerFactory(profile,
                             RTC::Create<ADC_Edison>,
                             RTC::Delete<ADC_Edison>);
  }
  
};


