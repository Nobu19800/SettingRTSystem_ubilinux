// -*- C++ -*-
/*!
 * @file  AccAndMagnSensor_LSM303DLHC.cpp
 * @brief AccAndMagnSensor_LSM303DLHC
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "AccAndMagnSensor_LSM303DLHC.h"

// Module specification
// <rtc-template block="module_spec">
static const char* accandmagnsensor_lsm303dlhc_spec[] =
  {
    "implementation_id", "AccAndMagnSensor_LSM303DLHC",
    "type_name",         "AccAndMagnSensor_LSM303DLHC",
    "description",       "AccAndMagnSensor_LSM303DLHC",
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
    //"conf.default.Acc_addr", "25",
    //"conf.default.Magn_addr", "30",
    "conf.default.offset", "0",
    "conf.default.accScale", "16G",
    "conf.default.magnScale", "2500mG",
    "conf.default.magnOffsetX", "935",
    "conf.default.magnOffsetY", "320",
    "conf.default.magnOffsetZ", "730",
    // Widget
    "conf.__widget__.I2C_channel", "radio",
    //"conf.__widget__.Acc_addr", "text",
    //"conf.__widget__.Magn_addr", "text",
    "conf.__widget__.offset", "text",
    "conf.__widget__.accScale", "radio",
    "conf.__widget__.magnScale", "radio",
    "conf.__widget__.magnOffsetX", "text",
    "conf.__widget__.magnOffsetY", "text",
    "conf.__widget__.magnOffsetZ", "text",
    // Constraints
    "conf.__constraints__.I2C_channel", "(1,6)",
    "conf.__constraints__.offset", "0<=x<=6.28",
    "conf.__constraints__.accScale", "(2G,4G,8G,16G)",
    "conf.__constraints__.magnScale", "(1300mG,1900mG,2500mG,4000mG,4700mG,5600mG,8100mG)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
AccAndMagnSensor_LSM303DLHC::AccAndMagnSensor_LSM303DLHC(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_accOut("acc", m_acc),
    m_magnOut("magn", m_magn),
    m_tempOut("temp", m_temp),
    m_rotOut("rot", m_rot)

    // </rtc-template>
{
	accSensor = NULL;
	_i2c = NULL;
}

/*!
 * @brief destructor
 */
AccAndMagnSensor_LSM303DLHC::~AccAndMagnSensor_LSM303DLHC()
{
}



RTC::ReturnCode_t AccAndMagnSensor_LSM303DLHC::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("acc", m_accOut);
  addOutPort("magn", m_magnOut);
  addOutPort("temp", m_tempOut);
  addOutPort("rot", m_rotOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("I2C_channel", m_I2C_channel, "1");
  //bindParameter("Acc_addr", m_Acc_addr, "25");
  //bindParameter("Magn_addr", m_Magn_addr, "30");
  bindParameter("offset", m_offset, "0");
  bindParameter("accScale", m_accScale, "16G");
  bindParameter("magnScale", m_magnScale, "2500mG");
  bindParameter("magnOffsetX", m_magnOffsetX, "935");
  bindParameter("magnOffsetY", m_magnOffsetY, "320");
  bindParameter("magnOffsetZ", m_magnOffsetZ, "730");
  // </rtc-template>

  _smf = new i2c_smf();
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccAndMagnSensor_LSM303DLHC::onFinalize()
{
	if(accSensor)
	{
		delete accSensor;
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


RTC::ReturnCode_t AccAndMagnSensor_LSM303DLHC::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccAndMagnSensor_LSM303DLHC::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccAndMagnSensor_LSM303DLHC::onActivated(RTC::UniqueId ec_id)
{
	uint8_t ascale;
	if(m_accScale == "2G")ascale = 0x00;
	else if(m_accScale == "4G")ascale = 0x01;
	else if(m_accScale == "8G")ascale = 0x02;
	else ascale = 0x03;

	uint8_t mscale;
	if(m_magnScale == "1300mG")mscale = 0x00;
	else if(m_magnScale == "1900mG")mscale = 0x01;
	else if(m_magnScale == "2500mG")mscale = 0x02;
	else if(m_magnScale == "4000mG")mscale = 0x03;
	else if(m_magnScale == "4700mG")mscale = 0x04;
	else if(m_magnScale == "5600mG")mscale = 0x05;
	else mscale = 0x06;

	mraa_result_t response;
	if(_i2c == NULL)
	{
		_smf->sem_lock();
		_i2c = new mraa::I2c(m_I2C_channel);
		_smf->sem_unlock();
	}
	if(accSensor == NULL)
	{
		accSensor = new LSM303DLHC(response, _i2c, _smf, LSM303DLHC_AccAddress, LSM303DLHC_MagAddress, ascale, mscale, m_magnOffsetX, m_magnOffsetY, m_magnOffsetZ);
		if(response != MRAA_SUCCESS)
		{
			delete accSensor;
			accSensor = NULL;
			return RTC::RTC_ERROR;
		}
	}
	else
	{
		response = accSensor->setAccAddr(LSM303DLHC_AccAddress);
		if(response != MRAA_SUCCESS)
		{
			return RTC::RTC_ERROR;
		}
		response = accSensor->setMagnAddr(LSM303DLHC_MagAddress);
		if(response != MRAA_SUCCESS)
		{
			return RTC::RTC_ERROR;
		}
		accSensor->setAccScale(ascale);
		accSensor->setMagnScale(mscale);
		accSensor->setOffset(m_magnOffsetX, m_magnOffsetY, m_magnOffsetZ);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccAndMagnSensor_LSM303DLHC::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccAndMagnSensor_LSM303DLHC::onExecute(RTC::UniqueId ec_id)
{
	double ax = 0;
	double ay = 0;
	double az = 0;

	double mx = 0;
	double my = 0;
	double mz = 0;

	double rx = 0;
	double ry = 0;
	double rz = 0;

	double temp = 0;

	if(accSensor)
	{
		
		accSensor->getAcc(ax,ay,az);
		m_acc.data.ax = ax;
		m_acc.data.ay = ay;
		m_acc.data.az = az;
		setTimestamp(m_acc);
		m_accOut.write();

		

		
		accSensor->getMagn(mx,my,mz);
		m_magn.data.length(3);
		m_magn.data[0] = mx;
		m_magn.data[1] = my;
		m_magn.data[2] = mz;
		setTimestamp(m_magn);
		m_magnOut.write();

		m_temp.data = temp;//accSensor->getTemp();
		setTimestamp(m_temp);
		m_tempOut.write();

		

		
		accSensor->getOrientation(rx,ry,rz);
		m_rot.data.r = rx;
		m_rot.data.p = ry;
		m_rot.data.y = rz - m_offset;
		setTimestamp(m_rot);

		m_rotOut.write();

		
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccAndMagnSensor_LSM303DLHC::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccAndMagnSensor_LSM303DLHC::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccAndMagnSensor_LSM303DLHC::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccAndMagnSensor_LSM303DLHC::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccAndMagnSensor_LSM303DLHC::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void AccAndMagnSensor_LSM303DLHCInit(RTC::Manager* manager)
  {
    coil::Properties profile(accandmagnsensor_lsm303dlhc_spec);
    manager->registerFactory(profile,
                             RTC::Create<AccAndMagnSensor_LSM303DLHC>,
                             RTC::Delete<AccAndMagnSensor_LSM303DLHC>);
  }
  
};


