// -*- C++ -*-
/*!
 * @file  MySecondComponent.cpp
 * @brief ${rtcParam.description}
 * @date $Date$
 *
 * $Id$
 */

#include "MySecondComponent.h"

// Module specification
// <rtc-template block="module_spec">
static const char* mysecondcomponent_spec[] =
  {
    "implementation_id", "MySecondComponent",
    "type_name",         "MySecondComponent",
    "description",       "${rtcParam.description}",
    "version",           "1.0",
    "vendor",            "Vendor",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "0",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
MySecondComponent::MySecondComponent(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inIn("in", m_in),
    m_outOut("out", m_out),
    m_servicePort("service")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
MySecondComponent::~MySecondComponent()
{
}



RTC::ReturnCode_t MySecondComponent::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in", m_inIn);
  
  // Set OutPort buffer
  addOutPort("out", m_outOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  m_servicePort.registerConsumer("moveService", "MoveService", m_moveService);
  
  // Set CORBA Service Ports
  addPort(m_servicePort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t MySecondComponent::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MySecondComponent::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MySecondComponent::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MySecondComponent::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MySecondComponent::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t MySecondComponent::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t MySecondComponent::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MySecondComponent::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MySecondComponent::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MySecondComponent::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MySecondComponent::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void MySecondComponentInit(RTC::Manager* manager)
  {
    coil::Properties profile(mysecondcomponent_spec);
    manager->registerFactory(profile,
                             RTC::Create<MySecondComponent>,
                             RTC::Delete<MySecondComponent>);
  }
  
};


