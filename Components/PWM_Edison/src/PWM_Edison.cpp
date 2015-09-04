// -*- C++ -*-
/*!
 * @file  PWM_Edison.cpp
 * @brief Control PWM
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "PWM_Edison.h"

// Module specification
// <rtc-template block="module_spec">
static const char* pwm_edison_spec[] =
  {
    "implementation_id", "PWM_Edison",
    "type_name",         "PWM_Edison",
    "description",       "Control PWM",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Device",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.pin", "3",
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
PWM_Edison::PWM_Edison(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inIn("in", m_in)

    // </rtc-template>
{
	pwm = NULL;
	last_pin = -1;
}

/*!
 * @brief destructor
 */
PWM_Edison::~PWM_Edison()
{
}



RTC::ReturnCode_t PWM_Edison::onInitialize()
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
  bindParameter("pin", m_pin, "3");
  // </rtc-template>
  
  return RTC::RTC_OK;
}




RTC::ReturnCode_t PWM_Edison::onFinalize()
{
	if(pwm)
	{
		pwm->write(0);
		pwm->enable(false);
		delete pwm;
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PWM_Edison::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PWM_Edison::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PWM_Edison::onActivated(RTC::UniqueId ec_id)
{
	if(last_pin != m_pin)
	{
		if(pwm)
		{
			pwm->write(0);
			pwm->enable(false);
			delete pwm;
		}
		pwm = new mraa::Pwm(m_pin);
		if (pwm == NULL) {
			return RTC::RTC_ERROR;
    		}
		pwm->enable(true);
		last_pin = m_pin;
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PWM_Edison::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PWM_Edison::onExecute(RTC::UniqueId ec_id)
{
	if(pwm)
	{
		if(m_inIn.isNew())
		{
			m_inIn.read();
			pwm->write(m_in.data);
		}
		
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PWM_Edison::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PWM_Edison::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PWM_Edison::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PWM_Edison::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PWM_Edison::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void PWM_EdisonInit(RTC::Manager* manager)
  {
    coil::Properties profile(pwm_edison_spec);
    manager->registerFactory(profile,
                             RTC::Create<PWM_Edison>,
                             RTC::Delete<PWM_Edison>);
  }
  
};


