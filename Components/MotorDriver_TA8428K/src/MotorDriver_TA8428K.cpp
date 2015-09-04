// -*- C++ -*-
/*!
 * @file  MotorDriver_TA8428K.cpp
 * @brief MotorDriver_TA8428K
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "MotorDriver_TA8428K.h"

// Module specification
// <rtc-template block="module_spec">
static const char* motordriver_ta8428k_spec[] =
  {
    "implementation_id", "MotorDriver_TA8428K",
    "type_name",         "MotorDriver_TA8428K",
    "description",       "MotorDriver_TA8428K",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Motor",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.pin1", "3",
    "conf.default.pin2", "5",
    // Widget
    "conf.__widget__.pin1", "text",
    "conf.__widget__.pin2", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
MotorDriver_TA8428K::MotorDriver_TA8428K(RTC::Manager* manager)
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
MotorDriver_TA8428K::~MotorDriver_TA8428K()
{
}



RTC::ReturnCode_t MotorDriver_TA8428K::onInitialize()
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
  bindParameter("pin1", m_pin1, "3");
  bindParameter("pin2", m_pin2, "5");
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA8428K::onFinalize()
{
	if(controller)
	{
		delete controller;
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA8428K::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA8428K::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA8428K::onActivated(RTC::UniqueId ec_id)
{
	mraa_result_t response;
  	if(controller == NULL)
	{
		controller = new TA8428K(response, m_pin1, m_pin2);
		if(response != MRAA_SUCCESS)
		{
			delete controller;
			controller = NULL;
			return RTC::RTC_ERROR;
		}
	}
	else
	{
		response = controller->setPinNum(m_pin1, m_pin2);
		if(response != MRAA_SUCCESS)
		{
			return RTC::RTC_ERROR;
		}
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA8428K::onDeactivated(RTC::UniqueId ec_id)
{
  controller->setValue(0);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA8428K::onExecute(RTC::UniqueId ec_id)
{
  	if(m_inIn.isNew())
	{
		m_inIn.read();
		controller->setValue(m_in.data);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA8428K::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA8428K::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA8428K::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA8428K::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotorDriver_TA8428K::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void MotorDriver_TA8428KInit(RTC::Manager* manager)
  {
    coil::Properties profile(motordriver_ta8428k_spec);
    manager->registerFactory(profile,
                             RTC::Create<MotorDriver_TA8428K>,
                             RTC::Delete<MotorDriver_TA8428K>);
  }
  
};


