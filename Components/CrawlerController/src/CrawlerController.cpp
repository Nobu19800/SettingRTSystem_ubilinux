// -*- C++ -*-
/*!
 * @file  CrawlerController.cpp
 * @brief Crawler Controller
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include <math.h>
#include <fstream>
#include "CrawlerController.h"


//std::ofstream ofs("test.txt");


// Module specification
// <rtc-template block="module_spec">
static const char* crawlercontroller_spec[] =
  {
    "implementation_id", "CrawlerController",
    "type_name",         "CrawlerController",
    "description",       "Crawler Controller",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Crawler",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.gyroSensor", "0",
    "conf.default.FrontRangeSensor", "1",
    "conf.default.BackRangeSensor", "1",
    "conf.default.AccelerationSensor", "1",
    "conf.default.MagneticSensor", "1",
    "conf.default.bias", "2.0",
    "conf.default.frontDistance", "0.5",
    "conf.default.backDistance", "0.1",
    "conf.default.filter", "0.05",
    "conf.default.rotOffset", "3.64",
    "conf.default.rotCorVal", "0.3",
    "conf.default.mr", "0.2",
    "conf.default.ar", "0.2",
    "conf.default.gr", "1.0",
    "conf.default.r", "0.8",
    // Widget
    "conf.__widget__.gyroSensor", "radio",
    "conf.__widget__.FrontRangeSensor", "radio",
    "conf.__widget__.BackRangeSensor", "radio",
    "conf.__widget__.AccelerationSensor", "radio",
    "conf.__widget__.MagneticSensor", "radio",
    "conf.__widget__.bias", "text",
    "conf.__widget__.frontDistance", "text",
    "conf.__widget__.backDistance", "text",
    "conf.__widget__.filter", "text",
    "conf.__widget__.rotOffset", "text",
    "conf.__widget__.rotCorVal", "text",
    "conf.__widget__.mr", "text",
    "conf.__widget__.ar", "text",
    "conf.__widget__.gr", "text",
    "conf.__widget__.r", "text",
    // Constraints
    "conf.__constraints__.gyroSensor", "(0,1)",
    "conf.__constraints__.FrontRangeSensor", "(0,1)",
    "conf.__constraints__.BackRangeSensor", "(0,1)",
    "conf.__constraints__.AccelerationSensor", "(0,1)",
    "conf.__constraints__.MagneticSensor", "(0,1)",
    "conf.__constraints__.mr", "0<=x<=1.0",
    "conf.__constraints__.ar", "0<=x<=1.0",
    "conf.__constraints__.gr", "0<=x<=1.0",
    "conf.__constraints__.r", "0<=x<=1.0",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
CrawlerController::CrawlerController(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_accIn("acc", m_acc),
    m_magnIn("magn", m_magn),
    m_gyroIn("gyro", m_gyro),
    m_range0In("range0", m_range0),
    m_range1In("range1", m_range1),
    m_range2In("range2", m_range2),
    m_range3In("range3", m_range3),
    m_in0In("in0", m_in0),
    m_in1In("in1", m_in1),
    m_posOut("pos", m_pos),
	m_out0Out("out0", m_out0),
	m_out1Out("out1", m_out1)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
CrawlerController::~CrawlerController()
{
}



RTC::ReturnCode_t CrawlerController::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("acc", m_accIn);
  addInPort("magn", m_magnIn);
  addInPort("gyro", m_gyroIn);
  addInPort("range0", m_range0In);
  addInPort("range1", m_range1In);
  addInPort("range2", m_range2In);
  addInPort("range3", m_range3In);
  addInPort("in0", m_in0In);
  addInPort("in1", m_in1In);
  
  // Set OutPort buffer
  addOutPort("pos", m_posOut);
  addOutPort("out0", m_out0Out);
  addOutPort("out1", m_out1Out);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("gyroSensor", m_gyroSensor, "0");
  bindParameter("FrontRangeSensor", m_FrontRangeSensor, "1");
  bindParameter("BackRangeSensor", m_BackRangeSensor, "1");
  bindParameter("AccelerationSensor", m_AccelerationSensor, "1");
  bindParameter("MagneticSensor", m_MagneticSensor, "1");
  bindParameter("bias", m_bias, "2.0");
  bindParameter("frontDistance", m_frontDistance, "0.5");
  bindParameter("backDistance", m_backDistance, "0.1");
  bindParameter("filter", m_filter, "0.05");
  bindParameter("rotOffset", m_rotOffset, "3.64");
  bindParameter("rotCorVal", m_rotCorVal, "0.3");
  bindParameter("mr", m_mr, "0.2");
  bindParameter("ar", m_ar, "0.2");
  bindParameter("gr", m_gr, "1.0");
  bindParameter("r", m_r, "0.8");
  // </rtc-template>
  m_crawler = new Crawler();
  m_calc = new CalcOrientation();
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CrawlerController::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CrawlerController::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CrawlerController::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CrawlerController::onActivated(RTC::UniqueId ec_id)
{
	m_crawler->setParam(m_FrontRangeSensor,m_BackRangeSensor,m_bias,m_frontDistance,m_backDistance,m_filter,m_rotCorVal);
	m_calc->setParam(m_ar,m_mr,m_gr,m_r);
	m_crawler->reset();
	m_calc->reset();
	last_posx = 0;
	last_posy = 0;

	first_time = coil::TimeValue(coil::gettimeofday());

  return RTC::RTC_OK;
}


RTC::ReturnCode_t CrawlerController::onDeactivated(RTC::UniqueId ec_id)
{
	m_out0.data = 0;
	m_out0Out.write();

	m_out1.data = 0;
	m_out1Out.write();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CrawlerController::onExecute(RTC::UniqueId ec_id)
{
	//return RTC::RTC_ERROR;
	/*coil::TimeValue t0(coil::gettimeofday());
	double now_time = (double)(t0-first_time);
	ofs << now_time - last_time << std::endl;
	last_time = now_time;*/
	if(m_in0In.isNew() && m_in1In.isNew())
	{
		double in0, in1;
		m_in0In.read();
		in0 = m_in0.data;

		m_in1In.read();
		in1 = m_in1.data;

		m_crawler->setVol(in0,in1);
	}
	
	bool startFlag = true;
	
	if(m_FrontRangeSensor == 1)
	{
		if(m_range0In.isNew())
		{

		}
		else
		{
			startFlag = false;
		}

		if(m_range1In.isNew())
		{

		}
		else
		{
			startFlag = false;
		}
	}
	if(m_BackRangeSensor == 1)
	{
		if(m_range2In.isNew())
		{

		}
		else
		{
			startFlag = false;
		}

		if(m_range3In.isNew())
		{

		}
		else
		{
			startFlag = false;
		}
	}

	
	if(m_AccelerationSensor == 1)
	{
		
		if(m_accIn.isNew())
		{

		}
		else
		{
			startFlag = false;
		}
	}
	if(m_MagneticSensor == 1)
	{
		
		if(m_magnIn.isNew())
		{

		}
		else
		{
			startFlag = false;
		}
	}
	
	if(m_gyroSensor == 1)
	{
		if(m_gyroIn.isNew())
		{

		}
		else
		{
			startFlag = false;
		}
	}
	

	if(startFlag)
	{
		double rn0 = 10;
		double rn1 = 10;
		double rn2 = 10;
		double rn3 = 10;
		double accX, accY, accZ;
		double magnX, magnY, magnZ;
		double avX, avY, avZ;
		if(m_FrontRangeSensor == 1)
		{
			
			m_range0In.read();
			rn0 = m_range0.data;

			m_range1In.read();
			rn1 = m_range1.data;
			
		}
		if(m_BackRangeSensor == 1)
		{
			
			m_range2In.read();
			rn2 = m_range2.data;
			
			m_range3In.read();
			rn3 = m_range3.data;
		}

		if(m_AccelerationSensor == 1)
		{
			m_accIn.read();
			accX = m_acc.data.ax;
			accY = m_acc.data.ay;
			accZ = m_acc.data.az;
		}
	
		if(m_MagneticSensor == 1)
		{
		
			m_magnIn.read();
			
			magnX = m_magn.data[0];
			magnY = m_magn.data[1];
			magnZ = m_magn.data[2];
	
		}
	
		if(m_gyroSensor == 1)
		{
			m_gyroIn.read();
			avX = m_gyro.data.avx;
			avY = m_gyro.data.avy;
			avZ = m_gyro.data.avz;

		
		}
		double rx = 0;
		double ry = 0;
		double rz = 0;
		if(m_AccelerationSensor == 1 && m_MagneticSensor == 1 && m_gyroSensor != 1)
		{
			m_calc->calc(accX,accY,accZ,magnX,magnY,magnZ,rx,ry,rz);
		}
		else if(m_AccelerationSensor == 1 && m_MagneticSensor == 1 && m_gyroSensor == 1)
		{
			m_calc->calc(accX,accY,accZ,magnX,magnY,magnZ,avX,avY,avZ,rx,ry,rz);
		}
		double input_crawlerVol0,input_crawlerVol1;
		double trans_speed = m_crawler->calc(input_crawlerVol0, input_crawlerVol1, rn0, rn1, rn2, rn3, rz);

		m_out0.data = input_crawlerVol0;
		setTimestamp(m_out0);
		m_out0Out.write();

		m_out1.data = input_crawlerVol1;
		setTimestamp(m_out1);
		m_out1Out.write();

		const double r = 0.01;
		last_posx += trans_speed*r*sin(-(rz - m_rotOffset));
		last_posy += trans_speed*r*cos(-(rz - m_rotOffset));
		m_pos.data.position.x = last_posx;
		m_pos.data.position.y = last_posy;
		m_pos.data.heading = rz - m_rotOffset;
		setTimestamp(m_pos);
		m_posOut.write();

		//std::cout << m_out0.data << "\t" << m_out1.data << "\t" << m_pos.data.position.x << "\t" << m_pos.data.position.y << "\t" << m_pos.data.heading << std::endl;
	}
	
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CrawlerController::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CrawlerController::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CrawlerController::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CrawlerController::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CrawlerController::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void CrawlerControllerInit(RTC::Manager* manager)
  {
    coil::Properties profile(crawlercontroller_spec);
    manager->registerFactory(profile,
                             RTC::Create<CrawlerController>,
                             RTC::Delete<CrawlerController>);
  }
  
};


