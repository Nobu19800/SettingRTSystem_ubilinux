// -*- C++ -*-
/*!
 * @file  RangeSensor_GP2Y0A21YK.cpp
 * @brief RangeSensor_GP2Y0A21YK
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "RangeSensor_GP2Y0A21YK.h"

// Module specification
// <rtc-template block="module_spec">
static const char* rangesensor_gp2y0a21yk_spec[] =
  {
    "implementation_id", "RangeSensor_GP2Y0A21YK",
    "type_name",         "RangeSensor_GP2Y0A21YK",
    "description",       "RangeSensor_GP2Y0A21YK",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Sensor",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.pin", "2",
    // Widget
    "conf.__widget__.pin", "radio",
    // Constraints
    "conf.__constraints__.pin", "(0,1,2,3)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RangeSensor_GP2Y0A21YK::RangeSensor_GP2Y0A21YK(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_outOut("out", m_out)

    // </rtc-template>
{
	rangeSensor = NULL;
}

/*!
 * @brief destructor
 */
RangeSensor_GP2Y0A21YK::~RangeSensor_GP2Y0A21YK()
{
}



RTC::ReturnCode_t RangeSensor_GP2Y0A21YK::onInitialize()
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
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RangeSensor_GP2Y0A21YK::onFinalize()
{
	if(rangeSensor)
	{
		delete rangeSensor;
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RangeSensor_GP2Y0A21YK::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RangeSensor_GP2Y0A21YK::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RangeSensor_GP2Y0A21YK::onActivated(RTC::UniqueId ec_id)
{
	mraa_result_t response;
	if(rangeSensor == NULL)
	{
		rangeSensor = new GP2Y0A21YK(response, m_pin);
		if(response != MRAA_SUCCESS)
		{
			delete rangeSensor;
			rangeSensor = NULL;
			return RTC::RTC_ERROR;
		}
	}
	else
	{
		response = rangeSensor->setPinNum(m_pin);
		if(response != MRAA_SUCCESS)
		{
			return RTC::RTC_ERROR;
		}
	}
	
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RangeSensor_GP2Y0A21YK::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RangeSensor_GP2Y0A21YK::onExecute(RTC::UniqueId ec_id)
{
	if(rangeSensor)
	{
		m_out.data = rangeSensor->getDistance();
		setTimestamp(m_out);
		m_outOut.write();
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RangeSensor_GP2Y0A21YK::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RangeSensor_GP2Y0A21YK::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RangeSensor_GP2Y0A21YK::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RangeSensor_GP2Y0A21YK::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RangeSensor_GP2Y0A21YK::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void RangeSensor_GP2Y0A21YKInit(RTC::Manager* manager)
  {
    coil::Properties profile(rangesensor_gp2y0a21yk_spec);
    manager->registerFactory(profile,
                             RTC::Create<RangeSensor_GP2Y0A21YK>,
                             RTC::Delete<RangeSensor_GP2Y0A21YK>);
  }
  
};


