// -*- C++ -*-
/*!
 * @file  adafruitpwmservodriveredison.cpp
 * @brief Adafruit PWM ServoDriver Component
 * @date $Date$
 *
 * $Id$
 */

#include "AdafruitPWMServoDriverEdison.h"

//#define SERVOMIN  160
//#define SERVOMAX  420
//#define PI 3.141592

// Module specification
// <rtc-template block="module_spec">
static const char* AdafruitPWMServoDriverEdison_spec[] =
  {
    "implementation_id", "AdafruitPWMServoDriverEdison",
    "type_name",         "AdafruitPWMServoDriverEdison",
    "description",       "Adafruit PWM ServoDriver Component",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Manipulator",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.I2C_address", "64",
    "conf.default.I2C_channel", "1",
    "conf.default.servo_max", "420",
    "conf.default.servo_min", "160",
    "conf.default.angle_max", "3.141592",
    // Widget
    "conf.__widget__.I2C_address", "spin",
    "conf.__widget__.I2C_channel", "radio",
    "conf.__widget__.servo_max", "spin",
    "conf.__widget__.servo_min", "spin",
    // Constraints
    "conf.__constraints__.I2C_address", "64<=x<=128",
    "conf.__constraints__.I2C_channel", "(1,6)",
    "conf.__constraints__.servo_max", "0<x<4096",
    "conf.__constraints__.servo_min", "0<x<4096",
    "conf.__constraints__.angle_max", "0<=x<=6.283",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
AdafruitPWMServoDriverEdison::AdafruitPWMServoDriverEdison(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inIn("in", m_in)
    //m_outOut("out", m_out)

    // </rtc-template>
{
	_pwm = NULL;
	_i2c = NULL;
	
}

/*!
 * @brief destructor
 */
AdafruitPWMServoDriverEdison::~AdafruitPWMServoDriverEdison()
{
}



RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in", m_inIn);
  
  // Set OutPort buffer
  //addOutPort("out", m_outOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("I2C_address", m_I2C_address, "64");
  bindParameter("I2C_channel", m_I2C_channel, "1");
  bindParameter("servo_max", m_servo_max, "420");
  bindParameter("servo_min", m_servo_min, "160");
  bindParameter("angle_max", m_angle_max, "3.141592");
  _smf = new i2c_smf();
  // </rtc-template>
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onFinalize()
{
	if(_pwm)
	{
		delete _pwm;
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


/*
RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onShutdown(RTC::UniqueId ec_id)
{
	

  return RTC::RTC_OK;
}


RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onActivated(RTC::UniqueId ec_id)
{
	if(_i2c == NULL)
	{
		_smf->sem_lock();
		_i2c = new mraa::I2c(m_I2C_channel);
		_smf->sem_unlock();
	}
	if(_pwm == NULL)
	{
		_pwm = new  PCA9685(_i2c, _smf, m_I2C_address);
		
	}
	else
	{
		_pwm->setAddr(m_I2C_address);
	}
	_pwm->begin();
	_pwm->setPWMFreq(50);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onExecute(RTC::UniqueId ec_id)
{
  if(m_inIn.isNew())
  {
	m_inIn.read();
	
	for(int i=0;i < m_in.data.length();i++)
	{
		uint16_t pulselen = m_servo_min + (m_servo_max - m_servo_min)*m_in.data[i]/m_angle_max;
		_pwm->setPWM(i,0,pulselen);
	}
	
  }
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AdafruitPWMServoDriverEdison::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void AdafruitPWMServoDriverEdisonInit(RTC::Manager* manager)
  {
    coil::Properties profile(AdafruitPWMServoDriverEdison_spec);
    manager->registerFactory(profile,
                             RTC::Create<AdafruitPWMServoDriverEdison>,
                             RTC::Delete<AdafruitPWMServoDriverEdison>);
  }
  
};


