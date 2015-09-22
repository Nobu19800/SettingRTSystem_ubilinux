// -*- C++ -*-
/*!
 * @file  CrawlerController.h
 * @brief Crawler Controller
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef CRAWLERCONTROLLER_H
#define CRAWLERCONTROLLER_H

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

#include "Crawler.h"
#include "CalcOrientation.h"

/*!
 * @class CrawlerController
 * @brief Crawler Controller
 *
 * クローラー制御RTコンポーネント
 *
 */
class CrawlerController
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  CrawlerController(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~CrawlerController();

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
   * 1の時はジャイロセンサを使用する
   * - Name: gyroSensor gyroSensor
   * - DefaultValue: 1
   */
  int m_gyroSensor;
  /*!
   * 1の時は前方に取り付けた距離センサを使用する
   * - Name: FrontRangeSensor FrontRangeSensor
   * - DefaultValue: 1
   * - Constraint: (0,1)
   */
  int m_FrontRangeSensor;
  /*!
   * 1の時は後方に取り付けた距離センサを使用する
   * - Name: BackRangeSensor BackRangeSensor
   * - DefaultValue: 1
   * - Constraint: (0,1)
   */
  int m_BackRangeSensor;
  /*!
   * 1の時は加速度センサを使用する
   * - Name: AccelerationSensor AccelerationSensor
   * - DefaultValue: 1
   * - Constraint: (0,1)
   */
  int m_AccelerationSensor;
  /*!
   * 1の時は地磁気センサを使用する
   * - Name: MagneticSensor MagneticSensor
   * - DefaultValue: 1
   * - Constraint: (0,1)
   */
  int m_MagneticSensor;
  /*!
   * 障害物が近づいた場合にどの程度旋回を行うか？値が大きくなるほど
   * 旋回しやすくなります。
   * - Name: bias bias
   * - DefaultValue: 1.0
   */
  double m_bias;
  /*!
   * 回避運動を開始する障害物までの最長距離
   * - Name: frontDistance frontDistance
   * - DefaultValue: 0.5
   */
  double m_frontDistance;
  /*!
   * 回避運動を開始する障害物までの最短距離。この値より近い距離に障
   * 害物があっても回避運動を行いません
   * - Name: backDistance backDistance
   * - DefaultValue: 0.1
   */
  double m_backDistance;
  /*!
   * この値が大きいほど余分な回避運動が小さくなります。
   * - Name: filter filter
   * - DefaultValue: 0.05
   */
  double m_filter;
  /*!
   * センサの計測値から計算した姿勢角へのオフセット
   * - Name: rotOffset rotOffset
   * - DefaultValue: 0.5
   */
  double m_rotOffset;
  /*!
   * 直進する際に真っ直ぐに動くように計測した姿勢の変化した方向に抗
   * う方向に回転する補正をかけるようにしています。このパラメータは
   * 姿勢の変化量にかける係数です。
   * - Name: rotCorVal rotCorVal
   * - DefaultValue: 15
   */
  double m_rotCorVal;
  /*!
   * 地磁気センサの計測値でのIIRフィルタの係数
   * - Name: mr mr
   * - DefaultValue: 0.2
   * - Constraint: 0<=x<=1.0
   */
  double m_mr;
  /*!
   * 加速度センサの計測値でのIIRフィルタの係数
   * - Name: ar ar
   * - DefaultValue: 0.2
   * - Constraint: 0<=x<=1.0
   */
  double m_ar;
  /*!
   * ジャイロセンサの計測値でのIIRフィルタの係数
   * - Name: gr gr
   * - DefaultValue: 1.0
   * - Constraint: 0<=x<=1.0
   */
  double m_gr;
  /*!
   * 相補フィルタの係数
   * - Name: r r
   * - DefaultValue: 0.8
   * - Constraint: 0<=x<=1.0
   */
  double m_r;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedAcceleration3D m_acc;
  /*!
   * 加速度センサの計測値
   * - Type: RTC::TimedAcceleration3D
   * - Unit: m/s^2
   */
  InPort<RTC::TimedAcceleration3D> m_accIn;
  RTC::TimedDoubleSeq m_magn;
  /*!
   * 地磁気センサの計測値
   * - Type: RTC::TimedDoubleSeq
   * - Unit: mG
   */
  InPort<RTC::TimedDoubleSeq> m_magnIn;
  RTC::TimedAngularVelocity3D m_gyro;
  /*!
   * 角速度センサの計測値
   * - Type: RTC::TimedAngularVelocity3D
   * - Unit: rad/s
   */
  InPort<RTC::TimedAngularVelocity3D> m_gyroIn;
  RTC::TimedDouble m_range0;
  /*!
   * 距離センサ(右前)の計測値
   * - Type: RTC::TimedDouble
   * - Unit: m
   */
  InPort<RTC::TimedDouble> m_range0In;
  RTC::TimedDouble m_range1;
  /*!
   * 距離センサ(左前)の計測値
   * - Type: RTC::TimedDouble
   * - Unit: m
   */
  InPort<RTC::TimedDouble> m_range1In;
  RTC::TimedDouble m_range2;
  /*!
   * 距離センサ(右後)の計測値
   * - Type: RTC::TimedDouble
   * - Unit: m
   */
  InPort<RTC::TimedDouble> m_range2In;
  RTC::TimedDouble m_range3;
  /*!
   * 距離センサ(左後)の計測値
   * - Type: RTC::TimedDouble
   * - Unit: m
   */
  InPort<RTC::TimedDouble> m_range3In;
  RTC::TimedDouble m_in0;
  /*!
   * 左モーターへ入力する電圧のPWMデューティー比
   * 距離センサによる回避運動をする場合はこの入力値を補正する
   * - Type: RTC::TimedDouble
   */
  InPort<RTC::TimedDouble> m_in0In;
  RTC::TimedDouble m_in1;
  /*!
   * 右モーターへ入力する電圧のPWMデューティー比
   * 距離センサによる回避運動をする場合はこの入力値を補正する
   * - Type: RTC::TimedDouble
   */
  InPort<RTC::TimedDouble> m_in1In;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedPose2D m_pos;
  /*!
   * センサ情報から計算した現在位置、姿勢(位置の計測は実装できてい
   * ないので左右モーターの電圧が正の場合は前進、負の場合は後退する
   * ようにしてある)
   * - Type: RTC::TimedPose2D
   * - Unit: m,rad
   */
  OutPort<RTC::TimedPose2D> m_posOut;

  RTC::TimedDouble m_out0;
  /*!
   * 左モーターへ入力する電圧のPWMデューティー比
   * - Type: RTC::TimedDouble
   */
  OutPort<RTC::TimedDouble> m_out0Out;

  RTC::TimedDouble m_out1;
  /*!
   * 左モーターへ入力する電圧のPWMデューティー比
   * - Type: RTC::TimedDouble
   */
  OutPort<RTC::TimedDouble> m_out1Out;


  
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
	Crawler *m_crawler;
	CalcOrientation *m_calc;
	double last_posx, last_posy;
	coil::TimeValue first_time;
	double last_time;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void CrawlerControllerInit(RTC::Manager* manager);
};

#endif // CRAWLERCONTROLLER_H
