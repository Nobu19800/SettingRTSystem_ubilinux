// -*- C++ -*-
/*!
 * @file  NineAxisSensor_LSM9DS0_I2C.h
 * @brief NineAxisSensor_LSM9DS0_I2C
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef NINEAXISSENSOR_LSM9DS0_I2C_H
#define NINEAXISSENSOR_LSM9DS0_I2C_H

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


#include "LSM9DS0_I2C.h"

/*!
 * @class NineAxisSensor_LSM9DS0_I2C
 * @brief NineAxisSensor_LSM9DS0_I2C
 *
 * LSM9DS0で加速度、地磁気、角速度を計測して出力するRTC
 *
 */
class NineAxisSensor_LSM9DS0_I2C
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  NineAxisSensor_LSM9DS0_I2C(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~NineAxisSensor_LSM9DS0_I2C();

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
   * I2Cのポート番号
   * - Name: I2C_channel I2C_channel
   * - DefaultValue: 1
   * - Constraint: (1,6)
   */
  int m_I2C_channel;
  /*!
   * 姿勢のオフセット
   * - Name: offset offset
   * - DefaultValue: 0
   * - Unit: rad
   * - Constraint: 0<=x<=6.28
   */
  double m_offset;
  /*!
   * 加速度センサの測定範囲
   * - Name: accScale accScale
   * - DefaultValue: 8G
   * - Constraint: (2G,4G,6G,8G,16G)
   */
  std::string m_accScale;
  /*!
   * 地磁気センサの測定範囲
   * - Name: magnScale magnScale
   * - DefaultValue: 8000mG
   * - Constraint: (2000mG,4000mG,8000mG,12000mG)
   */
  std::string m_magnScale;
  /*!
   * ジャイロセンサの測定範囲
   * - Name: gyroScale gyroScale
   * - DefaultValue: 500dps
   * - Constraint: (245dps,500dps,2000dps)
   */
  std::string m_gyroScale;
  /*!
   * 地磁気データX軸方向のオフセット
   * - Name: magnOffsetX magnOffsetX
   * - DefaultValue: 420
   */
  int m_magnOffsetX;
  /*!
   * 地磁気データY軸方向のオフセット
   * - Name: magnOffsetY magnOffsetY
   * - DefaultValue: -455
   */
  int m_magnOffsetY;
  /*!
   * 地磁気データZ軸方向のオフセット
   * - Name: magnOffsetZ magnOffsetZ
   * - DefaultValue: -155
   */
  int m_magnOffsetZ;

  std::string m_accmagAddr;
  std::string m_gyroAddr;
  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedAcceleration3D m_acc;
  /*!
   * 加速度センサの計測値
   * - Type: RTC::TimedAcceleration3D
   * - Unit: m/s^2
   */
  OutPort<RTC::TimedAcceleration3D> m_accOut;
  RTC::TimedDoubleSeq m_magn;
  /*!
   * 地磁気センサの計測値
   * - Type: RTC::TimedDoubleSeq
   */
  OutPort<RTC::TimedDoubleSeq> m_magnOut;
  RTC::TimedAngularVelocity3D m_gyro;
  /*!
   * ジャイロセンサーの計測値
   * - Type: RTC::TimedAngularVelocity3D
   * - Unit: rad/s
   */
  OutPort<RTC::TimedAngularVelocity3D> m_gyroOut;
  RTC::TimedDouble m_temp;
  /*!
   * 温度センサの計測値
   * - Type: RTC::TimedDouble
   * - Unit: 度
   */
  OutPort<RTC::TimedDouble> m_tempOut;
  RTC::TimedOrientation3D m_rot;
  /*!
   * センサ情報から計算した姿勢
   * - Type: RTC::TimedOrientation3D
   * - Unit: rad
   */
  OutPort<RTC::TimedOrientation3D> m_rotOut;
  
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
	LSM9DS0_I2C *accSensor;
	mraa::I2c* _i2c;
	i2c_smf *_smf;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void NineAxisSensor_LSM9DS0_I2CInit(RTC::Manager* manager);
};

#endif // NINEAXISSENSOR_LSM9DS0_I2C_H
