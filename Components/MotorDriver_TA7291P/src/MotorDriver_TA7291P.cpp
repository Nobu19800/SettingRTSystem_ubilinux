// -*- C++ -*-
/*!
 * @file  MotorDriver_TA7291P.cpp
 * @brief MotorDriver_TA7291P
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "MotorDriver_TA7291P.h"

// Module specification
// <rtc-template block="module_spec">
static const char* motordriver_ta7291p_spec[] =
  {
    "implementation_id", "MotorDriver_TA7291P",
    "type_name",         "MotorDriver_TA7291P",
    "description",       "MotorDriver_TA7291P",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Motor",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.pin1", "2",
    "conf.default.pin2", "4",
    "conf.default.pinv", "3",
    // Widget
    "conf.__widget__.pin1", "text",
    "conf.__widget__.pin2", "text",
    "conf.__widget__.pinv", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
MotorDriver_TA7291P::MotorDriver_TA7291P(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inIn("in", m_in)

    // </rtc-template>
{
	controller = NULL;
}

/*!
 * @brief destructor
 */
MotorDriver_TA7291P::~MotorDriver_TA7291P()
{
}



RTC::ReturnCode_t MotorDriver_TA7291P::onInitialize()
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
  bindParameter("pin1", m_pin1, "2");
  bindParameter("pin2", m_pin2, "4");
  bindParameter("pinv", m_pinv, "3");
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA7291P::onFinalize()
{
	if(controller)
	{
		delete controller;
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA7291P::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA7291P::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA7291P::onActivated(RTC::UniqueId ec_id)
{
	mraa_result_t response;
	if(controller == NULL)
	{
		controller = new TA7291P(response, m_pinv, m_pin1, m_pin2);
		if(response != MRAA_SUCCESS)
		{
			delete controller;
			controller = NULL;
			return RTC::RTC_ERROR;
		}
	}
	else
	{
		response = controller->setPinNum(m_pinv,m_pin1,m_pin2);
		if(response != MRAA_SUCCESS)
		{
			return RTC::RTC_ERROR;
		}
	}

  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA7291P::onDeactivated(RTC::UniqueId ec_id)
{
	controller->setValue(0);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA7291P::onExecute(RTC::UniqueId ec_id)
{
	if(m_inIn.isNew())
	{
		if(controller)
		{
			m_inIn.read();
			controller->setValue(m_in.data);
		}
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA7291P::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA7291P::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA7291P::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA7291P::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA7291P::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void MotorDriver_TA7291PInit(RTC::Manager* manager)
  {
    coil::Properties profile(motordriver_ta7291p_spec);
    manager->registerFactory(profile,
                             RTC::Create<MotorDriver_TA7291P>,
                             RTC::Delete<MotorDriver_TA7291P>);
  }
  
};


