// -*- C++ -*-
/*!
 * @file  rtcdControl.cpp
 * @brief RTCD操作のRTC
 * @date $Date$
 *
 * $Id$
 */

#include "rtcdControl.h"

// Module specification
// <rtc-template block="module_spec">
static const char* rtcdcontrol_spec[] =
  {
    "implementation_id", "rtcdControl",
    "type_name",         "rtcdControl",
    "description",       "rtcdControl",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "TEST",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>


/*!
* @brief RTCD操作のRTCのコンストラクタ
* @param manager マネージャオブジェクト
*/
rtcdControl::rtcdControl(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager)

    // </rtc-template>
{
	
	m_rtcControl_cppPort = new RTC::CorbaPort("rtcControl_cpp");
	m_rtcControl_cpp = new RTCDataInterfaceSVC_impl(manager);
}


/*!
* @brief  RTCD操作のRTCのデストラクタ
*/
rtcdControl::~rtcdControl()
{
}




/**
*@brief 初期化処理用コールバック関数
* @return RTC::ReturnCode_t
*/
RTC::ReturnCode_t rtcdControl::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
	
	m_rtcControl_cppPort->registerProvider("rtcControl_cpp", "rtcControl::RTCDataInterface", (*m_rtcControl_cpp));
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  addPort((*m_rtcControl_cppPort));
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t rtcdControl::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t rtcdControl::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t rtcdControl::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/**
*@brief 活性化時のコールバック関数
* @param ec_id target ExecutionContext Id
* @return
*/
RTC::ReturnCode_t rtcdControl::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/**
*@brief 不活性化時のコールバック関数
* @param ec_id target ExecutionContext Id
* @return RTC::ReturnCode_t
*/
RTC::ReturnCode_t rtcdControl::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/**
*@brief 周期処理用コールバック関数
* @param ec_id target ExecutionContext Id
* @return RTC::ReturnCode_t
*/
RTC::ReturnCode_t rtcdControl::onExecute(RTC::UniqueId ec_id)
{
	/*rtcControl::rtcPathSeq *paths;
	m_rtcControl_cpp->getRTC(paths);
	for (int i = 0; i < (*paths).length(); i++)
	{
		std::cout << (*paths)[i] << std::endl;

	}*/
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t rtcdControl::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t rtcdControl::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t rtcdControl::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t rtcdControl::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t rtcdControl::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void rtcdControlInit(RTC::Manager* manager)
  {
    coil::Properties profile(rtcdcontrol_spec);
    manager->registerFactory(profile,
                             RTC::Create<rtcdControl>,
                             RTC::Delete<rtcdControl>);
  }
  
};


