// -*- C++ -*-
/*!
 * @file  MyFirstComponent.cpp
 * @brief ${rtcParam.description}
 * @date $Date$
 *
 * $Id$
 */

#include "MyFirstComponent.h"

// Module specification
// <rtc-template block="module_spec">
static const char* myfirstcomponent_spec[] =
  {
    "implementation_id", "MyFirstComponent",
    "type_name",         "MyFirstComponent",
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
MyFirstComponent::MyFirstComponent(RTC::Manager* manager)
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
MyFirstComponent::~MyFirstComponent()
{
}



RTC::ReturnCode_t MyFirstComponent::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in", m_inIn);
  
  // Set OutPort buffer
  addOutPort("out", m_outOut);
  
  // Set service provider to Ports
  m_servicePort.registerProvider("moveService", "MoveService", m_moveService);
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  addPort(m_servicePort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t MyFirstComponent::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyFirstComponent::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyFirstComponent::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyFirstComponent::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyFirstComponent::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t MyFirstComponent::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t MyFirstComponent::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyFirstComponent::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyFirstComponent::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyFirstComponent::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyFirstComponent::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void MyFirstComponentInit(RTC::Manager* manager)
  {
    coil::Properties profile(myfirstcomponent_spec);
    manager->registerFactory(profile,
                             RTC::Create<MyFirstComponent>,
                             RTC::Delete<MyFirstComponent>);
  }
  
};


