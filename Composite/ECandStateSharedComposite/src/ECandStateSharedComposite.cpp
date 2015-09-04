// -*- C++ -*-
/*!
 * @file  ECandStateSharedComposite.cpp
 * @brief EC and State Shared Composite Component
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "ECandStateSharedComposite.h"



/*!
* @brief 非アクティブ化を行うスレッドのコンストラクタ
* @param rtc RTC
* @param ec 実行コンテキスト
*/
DeactiveTask::DeactiveTask(::SDOPackage::SDOList_var sdos, ::RTC::ExecutionContext_ptr ec)
{
	m_sdos = sdos;
	m_ec = ec;
};

/*!
* @brief スレッド実行関数
* @return
*/
int DeactiveTask::svc()
{
	for (::CORBA::ULong i(0), len(m_sdos->length()); i < len; ++i)
	{
		::RTC::RTObject_var rtc(::RTC::RTObject::_narrow(m_sdos[i]));
		m_ec->deactivate_component(rtc.in());
	}
	return 0;
}

// Module specification
// <rtc-template block="module_spec">
static const char* ecandstatesharedcomposite_spec[] =
  {
    "implementation_id", "ECandStateSharedComposite",
    "type_name",         "ECandStateSharedComposite",
    "description",       "EC and State Shared Composite Component",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "composite.PeriodicECShared",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
	"conf.default.members", "",
	"conf.default.exported_ports", "",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ECandStateSharedComposite::ECandStateSharedComposite(RTC::Manager* manager)
    // <rtc-template block="initializer">
	: RTC::PeriodicECSharedComposite(manager)

    // </rtc-template>
{
	d_task = NULL;
}

/*!
 * @brief destructor
 */
ECandStateSharedComposite::~ECandStateSharedComposite()
{
}



/*RTC::ReturnCode_t ECandStateSharedComposite::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}*/

/*
RTC::ReturnCode_t ECandStateSharedComposite::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ECandStateSharedComposite::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ECandStateSharedComposite::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ECandStateSharedComposite::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t ECandStateSharedComposite::onDeactivated(RTC::UniqueId ec_id)
{
	RTC_TRACE(("onDeactivated(%d)", ec_id));
	::RTC::ExecutionContextList_var ecs(get_owned_contexts());
	::SDOPackage::SDOList_var sdos(m_org->get_members());
	if (d_task)
	{
		delete d_task;
	}
	d_task = new DeactiveTask(sdos, ecs[0]);
	d_task->activate();
	
	return ::RTC::RTC_OK;
}


RTC::ReturnCode_t ECandStateSharedComposite::onExecute(RTC::UniqueId ec_id)
{
	RTC_TRACE(("onExecute(%d)", ec_id));
	::RTC::ExecutionContextList_var ecs(get_owned_contexts());
	::SDOPackage::SDOList_var sdos(m_org->get_members());

	for (::CORBA::ULong i(0), len(sdos->length()); i < len; ++i)
	{
		::RTC::RTObject_var rtc(::RTC::RTObject::_narrow(sdos[i]));
		//std::cout << rtc.in()->get_sdo_id() << "\t" << ecs[0]->get_component_state(rtc.in()) << std::endl;
		if (ecs[0]->get_component_state(rtc.in()) == RTC::ERROR_STATE)
		{
			return RTC::RTC_ERROR;
		}
	}
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ECandStateSharedComposite::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ECandStateSharedComposite::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ECandStateSharedComposite::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ECandStateSharedComposite::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ECandStateSharedComposite::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void ECandStateSharedCompositeInit(RTC::Manager* manager)
  {
    coil::Properties profile(ecandstatesharedcomposite_spec);
    manager->registerFactory(profile,
                             RTC::Create<ECandStateSharedComposite>,
                             RTC::Delete<ECandStateSharedComposite>);
  }
  
};


