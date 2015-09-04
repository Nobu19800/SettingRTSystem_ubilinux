// -*- C++ -*-
/*!
 * @file  rtcdControl.cpp
 * @brief RTCD�����RTC
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
* @brief RTCD�����RTC�̃R���X�g���N�^
* @param manager �}�l�[�W���I�u�W�F�N�g
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
* @brief  RTCD�����RTC�̃f�X�g���N�^
*/
rtcdControl::~rtcdControl()
{
}




/**
*@brief �����������p�R�[���o�b�N�֐�
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
*@brief ���������̃R�[���o�b�N�֐�
* @param ec_id target ExecutionContext Id
* @return
*/
RTC::ReturnCode_t rtcdControl::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/**
*@brief �s���������̃R�[���o�b�N�֐�
* @param ec_id target ExecutionContext Id
* @return RTC::ReturnCode_t
*/
RTC::ReturnCode_t rtcdControl::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/**
*@brief ���������p�R�[���o�b�N�֐�
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


