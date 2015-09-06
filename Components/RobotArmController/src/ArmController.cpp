// -*- C++ -*-
/*!
 * @file  armcontroller.cpp
 * @brief Control Manipulator With Edison
 * @date $Date$
 *
 * $Id$
 */

#include "ArmController.h"

// Module specification
// <rtc-template block="module_spec">
static const char* ArmController_spec[] =
  {
    "implementation_id", "ArmController",
    "type_name",         "ArmController",
    "description",       "Control Manipulator With Edison",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Manipulator",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.init_angle1", "0",
    "conf.default.init_angle2", "1.5",
    "conf.default.init_angel3", "-0.5",
    "conf.default.init_angel4", "0",
    "conf.default.init_gripperPos", "0",
    // Widget
    "conf.__widget__.init_angle1", "text",
    "conf.__widget__.init_angle2", "text",
    "conf.__widget__.init_angle3", "text",
    "conf.__widget__.init_angle4", "text",
    "conf.__widget__.init_gripperPos", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ArmController::ArmController(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_jposOut("jpos", m_jpos),
    m_mposOut("mpos", m_mpos),
    m_ManipulatorCommonInterface_CommonPort("ManipulatorCommonInterface_Common"),
    m_ManipulatorCommonInterface_MiddlePort("ManipulatorCommonInterface_Middle")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
ArmController::~ArmController()
{
}



RTC::ReturnCode_t ArmController::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("jpos", m_jposOut);
  addOutPort("mpos", m_mposOut);

  m_ra = new RobotArm();
  //m_ra->setOffset(0, PI/2*0.999, 0, 0);
  

  m_ManipulatorCommonInterface_Common = new ManipulatorCommonInterface_CommonSVC_impl(m_ra);
  m_ManipulatorCommonInterface_Middle = new ManipulatorCommonInterface_MiddleSVC_impl(m_ra);
  
  // Set service provider to Ports
  m_ManipulatorCommonInterface_CommonPort.registerProvider("ManipulatorCommonInterface_Common", "JARA_ARM::ManipulatorCommonInterface_Common", (*m_ManipulatorCommonInterface_Common));
  m_ManipulatorCommonInterface_MiddlePort.registerProvider("ManipulatorCommonInterface_Middle", "JARA_ARM::ManipulatorCommonInterface_Middle", (*m_ManipulatorCommonInterface_Middle));
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  addPort(m_ManipulatorCommonInterface_CommonPort);
  addPort(m_ManipulatorCommonInterface_MiddlePort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("init_angle1", m_init_angle1, "0");
  bindParameter("init_angle2", m_init_angle2, "1.5");
  bindParameter("init_angle3", m_init_angle3, "-0.5");
  bindParameter("init_angle4", m_init_angle4, "0");
  bindParameter("init_gripperPos", m_init_gripperPos, "0");
  
  // </rtc-template>
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ArmController::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ArmController::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t ArmController::onShutdown(RTC::UniqueId ec_id)
{
  

  return RTC::RTC_OK;
}


RTC::ReturnCode_t ArmController::onActivated(RTC::UniqueId ec_id)
{
  
  //m_ra->setOffset(m_init_angle1, m_init_angle2, m_init_angle3, m_init_angle4);
  

  m_ra->setStartPos(m_init_angle1, m_init_angle2, m_init_angle3, m_init_angle4);

  return RTC::RTC_OK;
}


RTC::ReturnCode_t ArmController::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ArmController::onExecute(RTC::UniqueId ec_id)
{
  
  if(m_ra->stopFalg)
  {
	//return RTC::RTC_ERROR;
	  return RTC::RTC_OK;
  }

  RTC::ExecutionContextList_var ecs = get_owned_contexts();
  double trate = ecs[0]->get_rate();
  m_ra->update(1/trate);
  
  

  m_jpos.data.length(m_ra->axisNum);
  for(int i=0;i < m_ra->axisNum;i++)
	m_jpos.data[i] = m_ra->theta[i];
  setTimestamp(m_jpos);
  m_jposOut.write();

  double *mp = m_ra->getMotorPosition();
  m_mpos.data.length(m_ra->axisNum);
  for(int i=0;i < m_ra->axisNum;i++)
	m_mpos.data[i] = mp[i];
  setTimestamp(m_mpos);
  m_mposOut.write();

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ArmController::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t ArmController::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ArmController::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ArmController::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ArmController::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void ArmControllerInit(RTC::Manager* manager)
  {
    coil::Properties profile(ArmController_spec);
    manager->registerFactory(profile,
                             RTC::Create<ArmController>,
                             RTC::Delete<ArmController>);
  }
  
};


