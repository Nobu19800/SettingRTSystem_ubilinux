// -*- C++ -*-
/*!
 * @file  AccelerationSensor_KXSC7_2050.cpp
 * @brief AccelerationSensor_KXSC7_2050
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "AccelerationSensor_KXSC7_2050.h"

// Module specification
// <rtc-template block="module_spec">
static const char* accelerationsensor_kxsc7_2050_spec[] =
  {
    "implementation_id", "AccelerationSensor_KXSC7_2050",
    "type_name",         "AccelerationSensor_KXSC7_2050",
    "description",       "AccelerationSensor_KXSC7_2050",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Sensor",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.pinX", "0",
    "conf.default.pinY", "1",
    "conf.default.pinZ", "2",
    "conf.default.voltage", "3.3",
    // Widget
    "conf.__widget__.pinX", "radio",
    "conf.__widget__.pinY", "radio",
    "conf.__widget__.pinZ", "radio",
    "conf.__widget__.voltage", "text",
    // Constraints
    "conf.__constraints__.pinX", "(0,1,2,3)",
    "conf.__constraints__.pinY", "(0,1,2,3)",
    "conf.__constraints__.pinZ", "(0,1,2,3)",
    "conf.__constraints__.voltage", "1.8<x<3.6",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
AccelerationSensor_KXSC7_2050::AccelerationSensor_KXSC7_2050(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_outOut("out", m_out)

    // </rtc-template>
{
	accSensor = NULL;
}

/*!
 * @brief destructor
 */
AccelerationSensor_KXSC7_2050::~AccelerationSensor_KXSC7_2050()
{
}



RTC::ReturnCode_t AccelerationSensor_KXSC7_2050::onInitialize()
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
  bindParameter("pinX", m_pinX, "0");
  bindParameter("pinY", m_pinY, "1");
  bindParameter("pinZ", m_pinZ, "2");
  bindParameter("voltage", m_voltage, "3.3");
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccelerationSensor_KXSC7_2050::onFinalize()
{
	if(accSensor)
	{
		delete accSensor;
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccelerationSensor_KXSC7_2050::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccelerationSensor_KXSC7_2050::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccelerationSensor_KXSC7_2050::onActivated(RTC::UniqueId ec_id)
{
	mraa_result_t response;
	if(accSensor == NULL)
	{
		accSensor = new KXSC7_2050(response, m_pinX, m_pinY, m_pinZ, m_voltage);
		if(response != MRAA_SUCCESS)
		{
			delete accSensor;
			accSensor = NULL;
			return RTC::RTC_ERROR;
		}
	}
	else
	{
		response = accSensor->setPinNum(m_pinX, m_pinY, m_pinZ);
		if(response != MRAA_SUCCESS)
		{
			return RTC::RTC_ERROR;
		}
		accSensor->setVoltage(m_voltage);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccelerationSensor_KXSC7_2050::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccelerationSensor_KXSC7_2050::onExecute(RTC::UniqueId ec_id)
{
	if(accSensor)
	{
		double ax,ay,az;
		accSensor->getAcceleration(ax,ay,az);
		m_out.data.ax = ax;
		m_out.data.ay = ay;
		m_out.data.az = az;
		setTimestamp(m_out);
		m_outOut.write();
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccelerationSensor_KXSC7_2050::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccelerationSensor_KXSC7_2050::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccelerationSensor_KXSC7_2050::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccelerationSensor_KXSC7_2050::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccelerationSensor_KXSC7_2050::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void AccelerationSensor_KXSC7_2050Init(RTC::Manager* manager)
  {
    coil::Properties profile(accelerationsensor_kxsc7_2050_spec);
    manager->registerFactory(profile,
                             RTC::Create<AccelerationSensor_KXSC7_2050>,
                             RTC::Delete<AccelerationSensor_KXSC7_2050>);
  }
  
};


