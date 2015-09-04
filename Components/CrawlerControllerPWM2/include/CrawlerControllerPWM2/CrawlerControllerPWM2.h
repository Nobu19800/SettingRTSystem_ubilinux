// -*- C++ -*-
/*!
 * @file  CrawlerControllerPWM2.h
 * @brief Crawler Controller Component
 * @date  $Date$
 *
 * $Id$
 */

#ifndef CrawlerControllerPWM2_H
#define CrawlerControllerPWM2_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include "TA8428K.h"
#include "L3GD20_I2C.h"
#include "GP2Y0A21YK.h"
#include "LSM303DLHC.h"


enum Crawler_Direction { C_Forword, C_Forword_Left, C_Forword_Right, C_Left, C_Right, C_Back, C_Back_Left, C_Back_Right, C_Stop };

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

using namespace RTC;

/*!
 * @class CrawlerControllerPWM2
 * @brief Crawler Controller Component
 *
 */
class CrawlerControllerPWM2
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  CrawlerControllerPWM2(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~CrawlerControllerPWM2();
  void writeRangeSensor(double &rn0, double &rn1, double &rn2, double &rn3);
  void writeGyroSensor(double &avx, double &avy, double &avz);
  void writeLSM303DLHC(double trans_speed, double &ax, double &ay, double &az, double &mx, double &my, double &mz, double &rx, double &ry, double &rz, double &temp);
  

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
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

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
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

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
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

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
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
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
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

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
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * 
   * - Name:  motor0pwm0
   * - DefaultValue: 3
   */
  int m_motor0pwm0;
  /*!
   * 
   * - Name:  motor0pwm1
   * - DefaultValue: 5
   */
  int m_motor0pwm1;
  /*!
   * 
   * - Name:  motor1pwm0
   * - DefaultValue: 6
   */
  int m_motor1pwm0;
  /*!
   * 
   * - Name:  motor1pwm1
   * - DefaultValue: 9
   */
  int m_motor1pwm1;

  int m_gyroSensor;
  std::string m_gyroSensor_addr;
  int m_rangeSensor0;
  int m_rangeSensor1;
  int m_rangeSensor2;
  int m_rangeSensor3;
  int m_rangeSensor0_Pin;
  int m_rangeSensor1_Pin;
  int m_rangeSensor2_Pin;
  int m_rangeSensor3_Pin;
  int m_LSM303DLHC;
  //int m_Acc_addr;
  //int m_Magn_addr;
  int m_I2C_channel;

  double m_bias;
  double m_frontDistance;
  double m_backDistance;
  double m_filter;
  
  double m_rotOffset;
  double m_rotCorVal;
  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  TimedDouble m_in0;
  /*!
   */
  InPort<TimedDouble> m_in0In;
  TimedDouble m_in1;
  /*!
   */
  InPort<TimedDouble> m_in1In;


	TimedAngularVelocity3D m_gyro;
	OutPort<TimedAngularVelocity3D> m_gyroOut;
	TimedDouble m_range0;
	OutPort<TimedDouble> m_range0Out;
	TimedDouble m_range1;
	OutPort<TimedDouble> m_range1Out;
	TimedDouble m_range2;
	OutPort<TimedDouble> m_range2Out;
	TimedDouble m_range3;
	OutPort<TimedDouble> m_range3Out;
	TimedAcceleration3D m_acc;
	OutPort<TimedAcceleration3D> m_accOut;
	TimedDoubleSeq m_magn;
	OutPort<TimedDoubleSeq> m_magnOut;
	TimedDouble m_temp;
	OutPort<TimedDouble> m_tempOut;
	TimedPose2D m_pos;
	OutPort<TimedPose2D> m_posOut;
	
	
  
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
	TA8428K *controller0;
	TA8428K *controller1;

	L3GD20_I2C *gyroSensor;
	GP2Y0A21YK *rangeSensor0;
	GP2Y0A21YK *rangeSensor1;
	GP2Y0A21YK *rangeSensor2;
	GP2Y0A21YK *rangeSensor3;
	LSM303DLHC *accSensor;
	mraa::I2c* _i2c;

	double crawlerVol0;
	double crawlerVol1;

	double last_bias0;
	double last_bias1;

	double last_posx;
	double last_posy;

	i2c_smf *_smf;

	double last_rz;

	int lv_count;

	//int m_count;
	
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void CrawlerControllerPWM2Init(RTC::Manager* manager);
};

#endif // CrawlerControllerPWM2_H
