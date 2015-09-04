// -*- C++ -*-
/*!
 * @file  CrawlerControllerPWM2.cpp
 * @brief Crawler Controller Component
 * @date $Date$
 *
 * $Id$
 */
#include "math.h"
#include "CrawlerControllerPWM2.h"


// Module specification
// <rtc-template block="module_spec">
static const char* CrawlerControllerPWM2_spec[] =
  {
    "implementation_id", "CrawlerControllerPWM2",
    "type_name",         "CrawlerControllerPWM2",
    "description",       "Crawler Controller Component",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "TEST",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    ""
    "conf.default.motor0pwm0", "3",
    "conf.default.motor0pwm1", "5",
    "conf.default.motor1pwm0", "6",
    "conf.default.motor1pwm1", "9",
    
    "conf.default.gyroSensor", "1",
    "conf.default.gyroSensor_addr", "0x6A",
    "conf.default.rangeSensor0", "1",
    "conf.default.rangeSensor1", "1",
    "conf.default.rangeSensor2", "1",
    "conf.default.rangeSensor3", "1",
    "conf.default.rangeSensor0_Pin", "2",
    "conf.default.rangeSensor1_Pin", "3",
    "conf.default.rangeSensor2_Pin", "0",
    "conf.default.rangeSensor3_Pin", "1",
    "conf.default.LSM303DLHC", "1",
    "conf.default.I2C_channel", "1",
    //"conf.default.Acc_addr", "25",
    //"conf.default.Magn_addr", "30",
    "conf.default.bias", "1.0",
    "conf.default.frontDistance", "0.5",
    "conf.default.backDistance", "0.1",
    "conf.default.filter", "0.05",
    "conf.default.rotOffset", "3.64",
    "conf.default.rotCorVal", "15",
    // Widget
    "conf.__widget__.motor0pwm0", "text",
    "conf.__widget__.motor0pwm1", "text",
    "conf.__widget__.motor1pwm0", "text",
    "conf.__widget__.motor1pwm1", "text",
    "conf.__widget__.gyroSensor", "radio",
    "conf.__widget__.gyroSensor_addr", "radio",
    "conf.__widget__.rangeSensor0", "radio",
    "conf.__widget__.rangeSensor1", "radio",
    "conf.__widget__.rangeSensor2", "radio",
    "conf.__widget__.rangeSensor3", "radio",
    "conf.__widget__.rangeSensor0_Pin", "text",
    "conf.__widget__.rangeSensor1_Pin", "text",
    "conf.__widget__.rangeSensor2_Pin", "text",
    "conf.__widget__.rangeSensor3_Pin", "text",
    "conf.__widget__.LSM303DLHC", "radio",
     "conf.__widget__.I2C_channel", "radio",
//    "conf.__widget__.Acc_addr", "text",
//    "conf.__widget__.Magn_addr", "text",

    "conf.__widget__.bias", "text",
    "conf.__widget__.frontDistance", "text",
    "conf.__widget__.backDistance", "text",
    "conf.__widget__.filter", "text",
    "conf.__widget__.rotOffset", "text",
    "conf.__widget__.rotCorVal", "text",


    "conf.__constraints__.gyroSensor", "(0,1)",
    "conf.__constraints__.gyroSensor_addr", "(0x6A,0x6B)",
    "conf.__constraints__.rangeSensor0", "(0,1)",
    "conf.__constraints__.rangeSensor1", "(0,1)",
    "conf.__constraints__.rangeSensor2", "(0,1)",
    "conf.__constraints__.rangeSensor3", "(0,1)",
    "conf.__constraints__.LSM303DLHC", "(0,1)",
    "conf.__constraints__.I2C_channel", "(1,6)",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
CrawlerControllerPWM2::CrawlerControllerPWM2(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_in0In("in0", m_in0),
    m_in1In("in1", m_in1),
    m_gyroOut("gyro", m_gyro),
    m_range0Out("range0", m_range0),
    m_range1Out("range1", m_range1),
    m_range2Out("range2", m_range2),
    m_range3Out("range3", m_range3),
    m_accOut("acc", m_acc),
    m_magnOut("magn", m_magn),
    m_tempOut("temp", m_temp),
    m_posOut("pos", m_pos)

    // </rtc-template>
{
	controller0 = NULL;
	controller1 = NULL;
	gyroSensor = NULL;
	rangeSensor0 = NULL;
	rangeSensor1 = NULL;
	rangeSensor2 = NULL;
	rangeSensor3 = NULL;
	accSensor = NULL;
	_i2c = NULL;
	crawlerVol0 = 0;
	crawlerVol1 = 0;

	last_posx = 0;
	last_posy = 0;
}

/*!
 * @brief destructor
 */
CrawlerControllerPWM2::~CrawlerControllerPWM2()
{
}



RTC::ReturnCode_t CrawlerControllerPWM2::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in0", m_in0In);
  addInPort("in1", m_in1In);

  addOutPort("gyro", m_gyroOut);
  addOutPort("range0", m_range0Out);
  addOutPort("range1", m_range1Out);
  addOutPort("range2", m_range2Out);
  addOutPort("range3", m_range3Out);
  addOutPort("acc", m_accOut);
  addOutPort("magn", m_magnOut);
  addOutPort("temp", m_tempOut);
  addOutPort("pos", m_posOut);

  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("motor0pwm0", m_motor0pwm0, "3");
  bindParameter("motor0pwm1", m_motor0pwm1, "5");
  bindParameter("motor1pwm0", m_motor1pwm0, "6");
  bindParameter("motor1pwm1", m_motor1pwm1, "9");

  bindParameter("gyroSensor", m_gyroSensor, "1");
  bindParameter("gyroSensor_addr", m_gyroSensor_addr, "0x6A");
  bindParameter("rangeSensor0", m_rangeSensor0, "1");
  bindParameter("rangeSensor1", m_rangeSensor1, "1");
  bindParameter("rangeSensor2", m_rangeSensor2, "1");
  bindParameter("rangeSensor3", m_rangeSensor3, "1");
  bindParameter("rangeSensor0_Pin", m_rangeSensor0_Pin, "2");
  bindParameter("rangeSensor1_Pin", m_rangeSensor1_Pin, "3");
  bindParameter("rangeSensor2_Pin", m_rangeSensor2_Pin, "0");
  bindParameter("rangeSensor3_Pin", m_rangeSensor3_Pin, "1");
  bindParameter("LSM303DLHC", m_LSM303DLHC, "1");
//  bindParameter("Acc_addr", m_Acc_addr, "25");
//  bindParameter("Magn_addr", m_Magn_addr, "30");
  bindParameter("I2C_channel", m_I2C_channel, "1");

  bindParameter("bias", m_bias, "1.0");
  bindParameter("frontDistance", m_frontDistance, "0.5");
  bindParameter("backDistance", m_backDistance, "0.1");
  bindParameter("filter", m_filter, "0.05");
  bindParameter("rotOffset", m_rotOffset, "3.64");
  bindParameter("rotCorVal", m_rotCorVal, "15");

  _smf = new i2c_smf();

  last_rz = 0;
  // </rtc-template>
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CrawlerControllerPWM2::onFinalize()
{

  if(controller0)
	{
		delete controller0;
	}
	if(controller1)
	{
		delete controller1;
	}
	if(gyroSensor)
	{
		delete gyroSensor;
	}
	if(rangeSensor0)
	{
		delete rangeSensor0;
	}
	if(rangeSensor1)
	{
		delete rangeSensor1;
	}
	if(rangeSensor2)
	{
		delete rangeSensor2;
	}
	if(rangeSensor3)
	{
		delete rangeSensor3;
	}
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


/*
RTC::ReturnCode_t CrawlerControllerPWM2::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t CrawlerControllerPWM2::onShutdown(RTC::UniqueId ec_id)
{
	
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CrawlerControllerPWM2::onActivated(RTC::UniqueId ec_id)
{
	
	mraa_result_t response;
	if(_i2c == NULL)
	{
		_smf->sem_lock();
		_i2c = new mraa::I2c(m_I2C_channel);
		_smf->sem_unlock();
	}
	if(controller0 == NULL)
	{
		controller0 = new TA8428K(response, m_motor0pwm0, m_motor0pwm1);
		if(response != MRAA_SUCCESS)
		{
			delete controller0;
			controller0 = NULL;
			return RTC::RTC_ERROR;
		}
	}
	else
	{
		response = controller0->setPinNum(m_motor0pwm0, m_motor0pwm1);
		if(response != MRAA_SUCCESS)
		{
			return RTC::RTC_ERROR;
		}
	}
	if(controller1 == NULL)
	{
		controller1 = new TA8428K(response, m_motor1pwm0, m_motor1pwm1);
		if(response != MRAA_SUCCESS)
		{
			delete controller1;
			controller1 = NULL;
			return RTC::RTC_ERROR;
		}
	}
	else
	{
		response = controller1->setPinNum(m_motor1pwm0, m_motor1pwm1);
		if(response != MRAA_SUCCESS)
		{
			return RTC::RTC_ERROR;
		}
	}

	if(m_gyroSensor == 1)
	{

		uint8_t ga;
		if(m_gyroSensor_addr == "0x6A")ga = 0x6A;
		else ga = 0x6B;

		if(gyroSensor == NULL)
		{
			gyroSensor = new L3GD20_I2C(response, _i2c, _smf, ga);
			if(response != MRAA_SUCCESS)
			{
				delete gyroSensor;
				gyroSensor = NULL;
				return RTC::RTC_ERROR;
			}
		}
		else
		{
			response = gyroSensor->setAddr(ga);
			if(response != MRAA_SUCCESS)
			{
				return RTC::RTC_ERROR;
			}
		}
		
	}
	if(m_rangeSensor0 == 1)
	{
		if(rangeSensor0 == NULL)
		{
			rangeSensor0 = new GP2Y0A21YK(response, m_rangeSensor0_Pin);
			if(response != MRAA_SUCCESS)
			{
				delete rangeSensor0;
				rangeSensor0 = NULL;
				return RTC::RTC_ERROR;
			}
		}
		else
		{
			response = rangeSensor0->setPinNum(m_rangeSensor0_Pin);
			if(response != MRAA_SUCCESS)
			{
				return RTC::RTC_ERROR;
			}
		}
	}
	if(m_rangeSensor1 == 1)
	{
		if(rangeSensor1 == NULL)
		{
			rangeSensor1 = new GP2Y0A21YK(response, m_rangeSensor1_Pin);
			if(response != MRAA_SUCCESS)
			{
				delete rangeSensor1;
				rangeSensor1 = NULL;
				return RTC::RTC_ERROR;
			}
		}
		else
		{
			response = rangeSensor1->setPinNum(m_rangeSensor1_Pin);
			if(response != MRAA_SUCCESS)
			{
				return RTC::RTC_ERROR;
			}
		}
	}
	if(m_rangeSensor2 == 1)
	{
		if(rangeSensor2 == NULL)
		{
			rangeSensor2 = new GP2Y0A21YK(response, m_rangeSensor2_Pin);
			if(response != MRAA_SUCCESS)
			{
				delete rangeSensor2;
				rangeSensor2 = NULL;
				return RTC::RTC_ERROR;
			}
		}
		else
		{
			response = rangeSensor2->setPinNum(m_rangeSensor2_Pin);
			if(response != MRAA_SUCCESS)
			{
				return RTC::RTC_ERROR;
			}
		}
	}
	if(m_rangeSensor3 == 1)
	{
		if(rangeSensor3 == NULL)
		{
			rangeSensor3 = new GP2Y0A21YK(response, m_rangeSensor3_Pin);
			if(response != MRAA_SUCCESS)
			{
				delete rangeSensor3;
				rangeSensor3 = NULL;
				return RTC::RTC_ERROR;
			}
		}
		else
		{
			response = rangeSensor3->setPinNum(m_rangeSensor3_Pin);
			if(response != MRAA_SUCCESS)
			{
				return RTC::RTC_ERROR;
			}
		}
	}
	if(m_LSM303DLHC == 1)
	{
		if(accSensor == NULL)
		{
			accSensor = new LSM303DLHC(response, _i2c, _smf, LSM303DLHC_AccAddress, LSM303DLHC_MagAddress);
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
		}
	}

	last_bias0 = 0;
	last_bias1 = 0;

	lv_count = 0;

	//crawlerVol0 = 1;
	//crawlerVol1 = 1;

	//m_count = 0;
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CrawlerControllerPWM2::onDeactivated(RTC::UniqueId ec_id)
{
	controller0->setValue(0);
	controller1->setValue(0);
	crawlerVol0 = 0;
	crawlerVol1 = 0;
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CrawlerControllerPWM2::onExecute(RTC::UniqueId ec_id)
{


	if(m_in0In.isNew())
	{
		m_in0In.read();
		crawlerVol0 = m_in0.data;
	}
	if(m_in1In.isNew())
	{
		m_in1In.read();
		crawlerVol1 = m_in1.data;
		
	}
	
	const double lv = 0.01;
	
	if(sqrt(crawlerVol0*crawlerVol0) < lv && sqrt(crawlerVol1*crawlerVol1) < lv)
	{
		controller0->setValue(0);
		controller1->setValue(0);

		lv_count += 1;
		if(lv_count%20 == 0)
		{
			double rn0,rn1,rn2,rn3;
			writeRangeSensor(rn0,rn1,rn2,rn3);
			
			double avx,avy,avz;

			writeGyroSensor(avx,avy,avz);

			double ax,ay,az;

			double mx,my,mz;

			double rx,ry,rz;
			double temp;

			writeLSM303DLHC(0,ax,ay,az,mx,my,mz,rx,ry,rz,temp);
		}


		return RTC::RTC_OK;
	}

	double input_crawlerVol0 = crawlerVol0;
	double input_crawlerVol1 = crawlerVol1;

	double trans_speed = (input_crawlerVol0 + input_crawlerVol1)/2;
	double rot_speed = (input_crawlerVol0 - input_crawlerVol1)/2;

	if(m_rangeSensor0 == 1 && rangeSensor0 && m_rangeSensor1 == 1 && rangeSensor1 && m_rangeSensor2 == 1 && rangeSensor2 && m_rangeSensor3 == 1 && rangeSensor3)
	{
		
		double p = 0.1;
		double sqrt_ts = sqrt(trans_speed*trans_speed);
		double sqrt_rs = sqrt(rot_speed*rot_speed);

		Crawler_Direction dir = C_Stop;
		
		if(sqrt_ts < p && sqrt_rs < p)
		{
			dir = C_Stop;
		}
		else if(trans_speed > 0 && sqrt_rs < p)
		{
			dir = C_Forword;
		}
		else if(trans_speed < 0 && sqrt_rs < p)
		{
			dir = C_Back;
		}
		else if(sqrt_ts < p && rot_speed > 0 )
		{
			dir = C_Right;
		}
		else if(sqrt_ts < p && rot_speed < 0 )
		{
			dir = C_Left;
		}
		else if(trans_speed > 0 && rot_speed < 0 )
		{
			dir = C_Forword_Left;
		}
		else if(trans_speed > 0 && rot_speed > 0 )
		{
			dir = C_Forword_Right;
		}
		else if(trans_speed < 0 && rot_speed < 0 )
		{
			dir = C_Back_Left;
		}
		else if(trans_speed < 0 && rot_speed > 0 )
		{
			dir = C_Back_Right;
		}

		


		double bias0,bias1,bias2,bias3;

		writeRangeSensor(bias0,bias1,bias2,bias3);

		//std::cout << "loop" << std::endl;
		//std::cout << bias0 << "\t" << bias1 << std::endl;

		

		

		
		if(bias0 > m_frontDistance)
			bias0 = m_frontDistance;
		if(bias1 > m_frontDistance)
			bias1 = m_frontDistance;
		if(bias0 < m_backDistance)
			bias0 = m_backDistance;
		if(bias1 < m_backDistance)
			bias1 = m_backDistance;

		bias0 = (m_frontDistance-bias0)/(m_frontDistance-m_backDistance);
		bias1 = (m_frontDistance-bias1)/(m_frontDistance-m_backDistance);

		

		if(last_bias0 > bias0)
		{
			bias0 = (1-m_filter)*last_bias0 + m_filter*bias0;
		}
		if(last_bias1 > bias1)
		{
			bias1 = (1-m_filter)*last_bias1 + m_filter*bias1;
		}

		last_bias0 = bias0;
		last_bias1 = bias1;

		//std::cout << bias0 << "\t" << bias1 << std::endl;
		
		double trans_bias = 0;
		bool rot_type;
		if(bias0 < bias1)
		{
			trans_bias = bias1;
			rot_type = false;
		}
		else
		{
			trans_bias = bias0;
			rot_type = true;
		}

		

		

		if(dir == C_Forword || dir == C_Forword_Left || dir == C_Forword_Right)
		{
			trans_speed *= (1-trans_bias*trans_bias*trans_bias);
			if(trans_speed < 0)
				trans_speed = 0;
			
			if(rot_type)
				rot_speed -= trans_bias*trans_bias*trans_bias*m_bias;
			else
				rot_speed += trans_bias*trans_bias*trans_bias*m_bias;

			input_crawlerVol0 = trans_speed + rot_speed;
			input_crawlerVol1 = trans_speed - rot_speed;
		}
		
	}

	//std::cout << input_crawlerVol0 << "\t" << input_crawlerVol1 << std::endl;

	//std::cout << input_crawlerVol0 << "\t" << input_crawlerVol1 << std::endl;

	
	/*m_count += 1;
	if(m_count%50 == 0 || m_count%50 == 1 || m_count%50 == 2 || m_count%50 == 3 || m_count%50 == 4)
	{
		controller0->setValue(0);
		controller1->setValue(0);
	}
	else
	{
		controller0->setValue(input_crawlerVol0);
		controller1->setValue(input_crawlerVol1);
	}*/

	double avx,avy,avz;

	writeGyroSensor(avx,avy,avz);


	
	double ax,ay,az;

	double mx,my,mz;

	double rx,ry,rz;
	double temp;

	writeLSM303DLHC(trans_speed,ax,ay,az,mx,my,mz,rx,ry,rz,temp);

	double drz = 0;
	drz = rz - last_rz;
	last_rz = rz;
	
	const double pm = 0.01;
	
	double dfv = input_crawlerVol0 - input_crawlerVol1;
	if(sqrt(dfv*dfv) < pm)
	{
		input_crawlerVol0 += drz*m_rotCorVal;
		input_crawlerVol1 -= drz*m_rotCorVal;
	}
	
	controller0->setValue(input_crawlerVol0);
	controller1->setValue(input_crawlerVol1);
	
  return RTC::RTC_OK;
}

void CrawlerControllerPWM2::writeRangeSensor(double &rn0, double &rn1, double &rn2, double &rn3)
{
	rn0 = 0;
	rn1 = 0;
	rn2 = 0;
	rn3 = 0;

	if(m_rangeSensor0 == 1 && rangeSensor0)
	{
		rn0 = rangeSensor0->getDistance();
		m_range0.data = rn0;
		setTimestamp(m_range0);
		m_range0Out.write();
	}
	
	if(m_rangeSensor1 == 1 && rangeSensor1)
	{
		rn1 = rangeSensor1->getDistance();
		m_range1.data = rn1;
		setTimestamp(m_range1);
		m_range1Out.write();
	}

	if(m_rangeSensor2 == 1 && rangeSensor2)
	{
		rn2 = rangeSensor2->getDistance();
		m_range2.data = rn2;
		setTimestamp(m_range2);
		m_range2Out.write();
	}

	if(m_rangeSensor3 == 1 && rangeSensor3)
	{
		rn3 = rangeSensor3->getDistance();
		m_range3.data = rn3;
		setTimestamp(m_range3);
		m_range3Out.write();
	}

}

void CrawlerControllerPWM2::writeGyroSensor(double &avx, double &avy, double &avz)
{
	avx = 0;
	avy = 0;
	avz = 0;
	if(m_gyroSensor == 1 && gyroSensor)
	{
		
		gyroSensor->getGyro(avx,avy,avz);
		m_gyro.data.avx = avx;
		m_gyro.data.avy = avy;
		m_gyro.data.avz = avz;
		setTimestamp(m_gyro);
		m_gyroOut.write();
	}
}

void CrawlerControllerPWM2::writeLSM303DLHC(double trans_speed, double &ax, double &ay, double &az, double &mx, double &my, double &mz, double &rx, double &ry, double &rz, double &temp)
{

	ax = 0;
	ay = 0;
	az = 0;

	mx = 0;
	my = 0;
	mz = 0;

	rx = 0;
	ry = 0;
	rz = 0;

	temp = 0;


	if(m_LSM303DLHC == 1 && accSensor)
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

		m_temp.data = 0;//accSensor->getTemp();
		setTimestamp(m_temp);
		m_tempOut.write();

		

		
		accSensor->getOrientation(rx,ry,rz);
		const double r = 0.01;
		last_posx += trans_speed*r*sin(-(rz-m_rotOffset));
		last_posy += trans_speed*r*cos(-(rz-m_rotOffset));
		m_pos.data.position.x = last_posx;
		m_pos.data.position.y = last_posy;
		m_pos.data.heading = rz-m_rotOffset;
		setTimestamp(m_pos);
		m_posOut.write();

		
	}
}


/*
RTC::ReturnCode_t CrawlerControllerPWM2::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CrawlerControllerPWM2::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CrawlerControllerPWM2::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CrawlerControllerPWM2::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CrawlerControllerPWM2::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void CrawlerControllerPWM2Init(RTC::Manager* manager)
  {
    coil::Properties profile(CrawlerControllerPWM2_spec);
    manager->registerFactory(profile,
                             RTC::Create<CrawlerControllerPWM2>,
                             RTC::Delete<CrawlerControllerPWM2>);
  }
  
};


