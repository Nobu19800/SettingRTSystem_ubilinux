// -*- C++ -*-
/*!
 * @file  NineAxisSensor_LSM9DS0_I2C.cpp
 * @brief NineAxisSensor_LSM9DS0_I2C
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "NineAxisSensor_LSM9DS0_I2C.h"

// Module specification
// <rtc-template block="module_spec">
static const char* nineaxissensor_lsm9ds0_i2c_spec[] =
  {
    "implementation_id", "NineAxisSensor_LSM9DS0_I2C",
    "type_name",         "NineAxisSensor_LSM9DS0_I2C",
    "description",       "NineAxisSensor_LSM9DS0_I2C",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Device",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.I2C_channel", "1",
    "conf.default.offset", "0",
    "conf.default.accScale", "8G",
    "conf.default.magnScale", "8000mG",
    "conf.default.gyroScale", "500dps",
    "conf.default.magnOffsetX", "420",
    "conf.default.magnOffsetY", "-455",
    "conf.default.magnOffsetZ", "-155",
    "conf.default.accmagAddr", "0x1D",
    "conf.default.gyroAddr", "0x6B",
    // Widget
    "conf.__widget__.I2C_channel", "radio",
    "conf.__widget__.offset", "text",
    "conf.__widget__.accScale", "radio",
    "conf.__widget__.magnScale", "radio",
    "conf.__widget__.gyroScale", "radio",
    "conf.__widget__.magnOffsetX", "text",
    "conf.__widget__.magnOffsetY", "text",
    "conf.__widget__.magnOffsetZ", "text",
    "conf.__widget__.accmagAddr", "radio",
    "conf.__widget__.gyroAddr", "radio",
    // Constraints
    "conf.__constraints__.I2C_channel", "(1,6)",
    "conf.__constraints__.offset", "0<=x<=6.28",
    "conf.__constraints__.accScale", "(2G,4G,6G,8G,16G)",
    "conf.__constraints__.magnScale", "(2000mG,4000mG,8000mG,12000mG)",
    "conf.__constraints__.gyroScale", "(245dps,500dps,2000dps)",
    "conf.__constraints__.accmagAddr", "(0x1D,0x1E)",
    "conf.__constraints__.gyroAddr", "(0x6A,0x6B)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
NineAxisSensor_LSM9DS0_I2C::NineAxisSensor_LSM9DS0_I2C(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_accOut("acc", m_acc),
    m_magnOut("magn", m_magn),
    m_gyroOut("gyro", m_gyro),
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
NineAxisSensor_LSM9DS0_I2C::~NineAxisSensor_LSM9DS0_I2C()
{
}



RTC::ReturnCode_t NineAxisSensor_LSM9DS0_I2C::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("acc", m_accOut);
  addOutPort("magn", m_magnOut);
  addOutPort("gyro", m_gyroOut);
  addOutPort("temp", m_tempOut);
  addOutPort("rot", m_rotOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("I2C_channel", m_I2C_channel, "1");
  bindParameter("offset", m_offset, "0");
  bindParameter("accScale", m_accScale, "8G");
  bindParameter("magnScale", m_magnScale, "8000mG");
  bindParameter("gyroScale", m_gyroScale, "500dps");
  bindParameter("magnOffsetX", m_magnOffsetX, "420");
  bindParameter("magnOffsetY", m_magnOffsetY, "-455");
  bindParameter("magnOffsetZ", m_magnOffsetZ, "-155");
  bindParameter("accmagAddr", m_accmagAddr, "0x1D");
  bindParameter("gyroAddr", m_gyroAddr, "0x6B");
  // </rtc-template>
  _smf = new i2c_smf();
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t NineAxisSensor_LSM9DS0_I2C::onFinalize()
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


RTC::ReturnCode_t NineAxisSensor_LSM9DS0_I2C::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t NineAxisSensor_LSM9DS0_I2C::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t NineAxisSensor_LSM9DS0_I2C::onActivated(RTC::UniqueId ec_id)
{
	uint8_t ascale;
	if(m_accScale == "2G")ascale = 0x00;
	else if(m_accScale == "4G")ascale = 0x01;
	else if(m_accScale == "6G")ascale = 0x02;
	else if(m_accScale == "8G")ascale = 0x03;
	else ascale = 0x04;

	uint8_t mscale;
	if(m_magnScale == "2000mG")mscale = 0x00;
	else if(m_magnScale == "4000mG")mscale = 0x01;
	else if(m_magnScale == "8000mG")mscale = 0x02;
	else mscale = 0x03;

	uint8_t gscale;
	if(m_gyroScale == "245dps")gscale = 0x00;
	else if(m_gyroScale == "500dps")gscale = 0x01;
	else gscale = 0x02;

	uint8_t aaddress;
	if(m_accmagAddr == "0x1D")aaddress = 0x1D;
	else aaddress = 0x1E;

	uint8_t gaddress;
	if(m_gyroAddr == "0x6A")gaddress = 0x6A;
	else gaddress = 0x6B;

	mraa_result_t response;
	if(_i2c == NULL)
	{
		_smf->sem_lock();
		_i2c = new mraa::I2c(m_I2C_channel);
		_smf->sem_unlock();
	}
	if(accSensor == NULL)
	{
		accSensor = new LSM9DS0_I2C(response, _i2c, _smf, aaddress, gaddress, ascale, mscale, gscale, m_magnOffsetX, m_magnOffsetY, m_magnOffsetZ);
		if(response != MRAA_SUCCESS)
		{
			delete accSensor;
			accSensor = NULL;
			return RTC::RTC_ERROR;
		}
	}
	else
	{
		response = accSensor->setAccMagAddr(aaddress);
		if(response != MRAA_SUCCESS)
		{
			return RTC::RTC_ERROR;
		}
		response = accSensor->setGyroAddr(gaddress);
		if(response != MRAA_SUCCESS)
		{
			return RTC::RTC_ERROR;
		}
		accSensor->setAccScale(ascale);
		accSensor->setMagnScale(mscale);
		accSensor->setGyroScale(gscale);
		accSensor->setOffset(m_magnOffsetX, m_magnOffsetY, m_magnOffsetZ);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t NineAxisSensor_LSM9DS0_I2C::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t NineAxisSensor_LSM9DS0_I2C::onExecute(RTC::UniqueId ec_id)
{
	double ax = 0;
	double ay = 0;
	double az = 0;

	double mx = 0;
	double my = 0;
	double mz = 0;

	double avx = 0;
	double avy = 0;
	double avz = 0;

	double rx = 0;
	double ry = 0;
	double rz = 0;

	//double temp = 0;

	if(accSensor)
	{
		std::cout << "test" << std::endl;
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



		accSensor->getGyro(avx,avy,avz);
		m_gyro.data.avx = avx;
		m_gyro.data.avy = avy;
		m_gyro.data.avz = avz;
		setTimestamp(m_gyro);
		m_gyroOut.write();



		m_temp.data = accSensor->getTemp();
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


RTC::ReturnCode_t NineAxisSensor_LSM9DS0_I2C::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t NineAxisSensor_LSM9DS0_I2C::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t NineAxisSensor_LSM9DS0_I2C::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t NineAxisSensor_LSM9DS0_I2C::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t NineAxisSensor_LSM9DS0_I2C::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void NineAxisSensor_LSM9DS0_I2CInit(RTC::Manager* manager)
  {
    coil::Properties profile(nineaxissensor_lsm9ds0_i2c_spec);
    manager->registerFactory(profile,
                             RTC::Create<NineAxisSensor_LSM9DS0_I2C>,
                             RTC::Delete<NineAxisSensor_LSM9DS0_I2C>);
  }
  
};


