// -*- C++ -*-
/*!
 * @file  GyroSensor_L3GD20_I2C.cpp
 * @brief GyroSensor_L3GD20_I2C
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "GyroSensor_L3GD20_I2C.h"

// Module specification
// <rtc-template block="module_spec">
static const char* gyrosensor_l3gd20_i2c_spec[] =
  {
    "implementation_id", "GyroSensor_L3GD20_I2C",
    "type_name",         "GyroSensor_L3GD20_I2C",
    "description",       "GyroSensor_L3GD20_I2C",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Sensor",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.I2C_channel", "1",
    "conf.default.addr", "0x6A",
    "conf.default.scale", "250dps",
    // Widget
    "conf.__widget__.I2C_channel", "radio",
    "conf.__widget__.addr", "radio",
    "conf.__widget__.scale", "radio",
    // Constraints
    "conf.__constraints__.I2C_channel", "(1,6)",
    "conf.__constraints__.addr", "(0x6A,0x6B)",
    "conf.__constraints__.scale", "(250dps,500dps,2000dps)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
GyroSensor_L3GD20_I2C::GyroSensor_L3GD20_I2C(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_gyroOut("gyro", m_gyro)

    // </rtc-template>
{
	gyroSensor = NULL;
	_i2c = NULL;
}

/*!
 * @brief destructor
 */
GyroSensor_L3GD20_I2C::~GyroSensor_L3GD20_I2C()
{
}



RTC::ReturnCode_t GyroSensor_L3GD20_I2C::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("gyro", m_gyroOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("I2C_channel", m_I2C_channel, "1");
  bindParameter("addr", m_addr, "0x6A");
  bindParameter("scale", m_scale, "250dps");
  // </rtc-template>
  _smf = new i2c_smf();
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_L3GD20_I2C::onFinalize()
{
	if(gyroSensor)
	{
		delete gyroSensor;
	}
	if(_i2c)
	{
		_smf->sem_lock();
		delete _i2c;
		_smf->sem_unlock();
	}

	delete _smf;
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_L3GD20_I2C::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_L3GD20_I2C::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_L3GD20_I2C::onActivated(RTC::UniqueId ec_id)
{
	uint8_t s;
	if(m_scale == "250dps")s = 0x00;
	else if(m_scale == "500dps")s = 0x01;
	else s = 0x02;


	uint8_t a;
	if(m_addr == "0x6A")a = 0x6A;
	else a = 0x6B;

	mraa_result_t response;

	if(_i2c == NULL)
	{
		_smf->sem_lock();
		_i2c = new mraa::I2c(m_I2C_channel);
		_smf->sem_unlock();
	}
	if(gyroSensor == NULL)
	{
		
		gyroSensor = new L3GD20_I2C(response, _i2c, _smf, a, s);
		if(response != MRAA_SUCCESS)
		{
			delete gyroSensor;
			gyroSensor = NULL;
			return RTC::RTC_ERROR;
		}
	}
	else
	{
		response = gyroSensor->setAddr(a);
		if(response != MRAA_SUCCESS)
		{
			return RTC::RTC_ERROR;
		}
		gyroSensor->setScale(s);
	}

	
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_L3GD20_I2C::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_L3GD20_I2C::onExecute(RTC::UniqueId ec_id)
{
	double avx = 0;
	double avy = 0;
	double avz = 0;

	if(gyroSensor)
	{
		
		gyroSensor->getGyro(avx,avy,avz);
		m_gyro.data.avx = avx;
		m_gyro.data.avy = avy;
		m_gyro.data.avz = avz;
		setTimestamp(m_gyro);
		
		m_gyroOut.write();
	}

  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_L3GD20_I2C::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_L3GD20_I2C::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_L3GD20_I2C::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_L3GD20_I2C::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GyroSensor_L3GD20_I2C::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void GyroSensor_L3GD20_I2CInit(RTC::Manager* manager)
  {
    coil::Properties profile(gyrosensor_l3gd20_i2c_spec);
    manager->registerFactory(profile,
                             RTC::Create<GyroSensor_L3GD20_I2C>,
                             RTC::Delete<GyroSensor_L3GD20_I2C>);
  }
  
};


