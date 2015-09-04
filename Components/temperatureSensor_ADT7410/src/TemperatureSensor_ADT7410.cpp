// -*- C++ -*-
/*!
 * @file  TemperatureSensor_ADT7410.cpp
 * @brief TemperatureSensor_ADT7410
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "TemperatureSensor_ADT7410.h"

// Module specification
// <rtc-template block="module_spec">
static const char* temperaturesensor_adt7410_spec[] =
  {
    "implementation_id", "TemperatureSensor_ADT7410",
    "type_name",         "TemperatureSensor_ADT7410",
    "description",       "TemperatureSensor_ADT7410",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Sensor",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.addr", "0x48",
    "conf.default.I2C_channel", "1",
    // Widget
    "conf.__widget__.addr", "radio",
    "conf.__widget__.I2C_channel", "radio",
    // Constraints
    "conf.__constraints__.addr", "(0x48,0x49,0x4A,0x4B)",
    "conf.__constraints__.I2C_channel", "(1,6)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
TemperatureSensor_ADT7410::TemperatureSensor_ADT7410(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_outOut("out", m_out)

    // </rtc-template>
{
	tempSensor = NULL;
	_i2c = NULL;
}

/*!
 * @brief destructor
 */
TemperatureSensor_ADT7410::~TemperatureSensor_ADT7410()
{
}



RTC::ReturnCode_t TemperatureSensor_ADT7410::onInitialize()
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
  bindParameter("addr", m_addr, "72");
  bindParameter("I2C_channel", m_I2C_channel, "1");
  // </rtc-template>
  _smf = new i2c_smf();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TemperatureSensor_ADT7410::onFinalize()
{
	if(tempSensor)
	{
		delete tempSensor;
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


RTC::ReturnCode_t TemperatureSensor_ADT7410::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TemperatureSensor_ADT7410::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TemperatureSensor_ADT7410::onActivated(RTC::UniqueId ec_id)
{
	uint8_t addr;
	if(m_addr == "0x48")addr = 0x48;
	else if(m_addr == "0x49")addr = 0x49;
	else if(m_addr == "0x4A")addr = 0x4A;
	else addr = 0x4B;


	if(_i2c == NULL)
	{
		_smf->sem_lock();
		_i2c = new mraa::I2c(m_I2C_channel);
		_smf->sem_unlock();
	}
	if(tempSensor == NULL)
	{
		
		tempSensor = new ADT7410(_i2c, _smf, addr);
	}
	else
	{
		tempSensor->setAddr(addr);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TemperatureSensor_ADT7410::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TemperatureSensor_ADT7410::onExecute(RTC::UniqueId ec_id)
{

	if(tempSensor)
	{
		m_out.data = tempSensor->getTempData();
		setTimestamp(m_out);
		m_outOut.write();
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TemperatureSensor_ADT7410::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TemperatureSensor_ADT7410::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TemperatureSensor_ADT7410::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TemperatureSensor_ADT7410::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TemperatureSensor_ADT7410::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void TemperatureSensor_ADT7410Init(RTC::Manager* manager)
  {
    coil::Properties profile(temperaturesensor_adt7410_spec);
    manager->registerFactory(profile,
                             RTC::Create<TemperatureSensor_ADT7410>,
                             RTC::Delete<TemperatureSensor_ADT7410>);
  }
  
};


