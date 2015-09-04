// -*- C++ -*-
/*!
 * @file  ADC_MCP3002.h
 * @brief ADC_MCP3002
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef ADC_MCP3002_H
#define ADC_MCP3002_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>



// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="port_stub_h">
// </rtc-template>

using namespace RTC;

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>



#include "MCP3002.h"

class ADC_MCP3002Comp;


template <class T>
bool getValueInString(std::string str, std::vector<T> &ans)
{
	coil::eraseBlank(str);
	ans.clear();
	coil::vstring va = coil::split(str, ",");
	if(va.size() == 0)
	{
		return false;
	}
	for (coil::vstring::iterator it = va.begin(); it != va.end(); ++it)
	{
		T value;
		bool result = coil::stringTo<T>(value, (*it).c_str());
		if(result)
		{
			ans.push_back(value);
		}
		else
		{
			return false;
		}
	}
	
	return true;
};

/*!
 * @class ADC_MCP3002
 * @brief ADC_MCP3002
 *
 * MCP3002によりAD変換をする
 *
 */
class ADC_MCP3002
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  ADC_MCP3002(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~ADC_MCP3002();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * チップ選択をするピン番号
   * - Name: cs_pin cs_pin
   * - DefaultValue: 4
   */
  int m_cs_pin;
  /*!
   * A/D変換した電圧値を取得するMCP3002のチャンネル番号
   * チェックしなかったチャンネルはデータを出力しません
   * - Name: channel channel
   * - DefaultValue: 0
   * - Constraint: (0,1)
   */
  std::string m_channel;
  /*!
   * 電源電圧値
   * - Name: voltage voltage
   * - DefaultValue: 5
   * - Unit: V
   */
  double m_voltage;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
	MCP3002 *ADC;
	mraa::Spi* _spi;
	i2c_smf *_smf;
	std::vector<ADC_MCP3002Comp *> adc_ports;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


class ADC_MCP3002Comp
{
public:
	ADC_MCP3002Comp(ADC_MCP3002 *rtc, int num);
	~ADC_MCP3002Comp();
	void setActive(bool a);
	void writeValue(MCP3002 *mcp,double v);
	TimedDouble *Out;
	RTC::OutPort<TimedDouble> *outOut;
	int m_num;
	RTC::DataFlowComponentBase *m_rtc;
	bool act;

};


extern "C"
{
  DLL_EXPORT void ADC_MCP3002Init(RTC::Manager* manager);
};

#endif // ADC_MCP3002_H
