// -*- C++ -*-
/*!
 * @file  GyroSensor_ENC_03R.cpp
 * @brief GyroSensor_ENC_03R
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "GyroSensor_ENC_03R.h"

// Module specification
// <rtc-template block="module_spec">
static const char* gyrosensor_enc_03r_spec[] =
  {
    "implementation_id", "GyroSensor_ENC_03R",
    "type_name",         "GyroSensor_ENC_03R",
    "description",       "GyroSensor_ENC_03R",
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
    // Widget
    "conf.__widget__.pinX", "radio",
    "conf.__widget__.pinY", "radio",
    // Constraints
    "conf.__constraints__.pinX", "(0,1,2,3)",
    "conf.__constraints__.pinY", "(0,1,2,3)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
GyroSensor_ENC_03R::GyroSensor_ENC_03R(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_avxOut("avx", m_avx),
    m_avyOut("avy", m_avy)

    // </rtc-template>
{
	gyroSensor = NULL;
}

/*!
 * @brief destructor
 */
GyroSensor_ENC_03R::~GyroSensor_ENC_03R()
{
}



RTC::ReturnCode_t GyroSensor_ENC_03R::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("avx", m_avxOut);
  addOutPort("avy", m_avyOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("pinX", m_pinX, "0");
  bindParameter("pinY", m_pinY, "1");
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_ENC_03R::onFinalize()
{
	if(gyroSensor)
	{
		delete gyroSensor;
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_ENC_03R::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_ENC_03R::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_ENC_03R::onActivated(RTC::UniqueId ec_id)
{
	mraa_result_t response;
	if(gyroSensor == NULL)
	{
		gyroSensor = new ENC_03R(response, m_pinX, m_pinY);
		if(response != MRAA_SUCCESS)
		{
			delete gyroSensor;
			gyroSensor = NULL;
			return RTC::RTC_ERROR;
		}
	}
	else
	{
		response = gyroSensor->setPinNum(m_pinX, m_pinY);
		if(response != MRAA_SUCCESS)
		{
			return RTC::RTC_ERROR;
		}
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_ENC_03R::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_ENC_03R::onExecute(RTC::UniqueId ec_id)
{
	if(gyroSensor)
	{
		double avx,avy;
		gyroSensor->getAngularVelocity(avx,avy);
		m_avx.data = avx;
		m_avy.data = avy;
		setTimestamp(m_avx);
		m_avxOut.write();
		setTimestamp(m_avy);
		m_avyOut.write();
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_ENC_03R::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_ENC_03R::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_ENC_03R::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_ENC_03R::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_ENC_03R::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void GyroSensor_ENC_03RInit(RTC::Manager* manager)
  {
    coil::Properties profile(gyrosensor_enc_03r_spec);
    manager->registerFactory(profile,
                             RTC::Create<GyroSensor_ENC_03R>,
                             RTC::Delete<GyroSensor_ENC_03R>);
  }
  
};


