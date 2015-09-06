// -*-C++-*-
/*!
 * @file  ManipulatorCommonInterface_CommonSVC_impl.h
 * @brief サインスマート製4自由度ロボットアーム用低レベルモーションコマンド
 * コメント文はロボットアーム制御機能共通インタフェース仕様書か引用しました
 *
 */

#include "ManipulatorCommonInterface_DataTypesSkel.h"
#include "BasicDataTypeSkel.h"

#include "ManipulatorCommonInterface_CommonSkel.h"

#include "RobotArm.h"

#ifndef MANIPULATORCOMMONINTERFACE_COMMONSVC_IMPL_H
#define MANIPULATORCOMMONINTERFACE_COMMONSVC_IMPL_H
 


/*!
 * @class ManipulatorCommonInterface_CommonSVC_impl
 * @brief サインスマート製4自由度ロボットアーム用低レベルモーションコマンド
 */
class ManipulatorCommonInterface_CommonSVC_impl
 : public virtual POA_JARA_ARM::ManipulatorCommonInterface_Common,
   public virtual PortableServer::RefCountServantBase
{
 private:

   //virtual ~ManipulatorCommonInterface_CommonSVC_impl();

 public:
  /*!
   * @brief コンストラクタ
   * @param ra ロボットアーム制御オブジェクト
   */
   ManipulatorCommonInterface_CommonSVC_impl(RobotArm *ra);
  /*!
   * @brief デストラクタ
   */
   virtual ~ManipulatorCommonInterface_CommonSVC_impl();

   /*!
   * @brief アラームクリア
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *clearAlarms();
   /*!
   * @brief アラーム情報の取得
   * @param alarms アラーム情報の配列
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getActiveAlarm(JARA_ARM::AlarmSeq_out alarms);
   /*!
   * @brief 関節座標系の位置フィードバック情報の取得
   * @param pos 位置フィードバック情報(シーケンス型)
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getFeedbackPosJoint(JARA_ARM::JointPos_out pos);
   /*!
   * @brief マニピュレータ情報の取得
   * @param mInfo マニピュレータ情報
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getManipInfo(JARA_ARM::ManipInfo_out mInfo);
   /*!
   * @brief 関節座標系のソフトリミット値を取得
   * @param softLimit 各軸のソフトリミット値[単位:degree]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getSoftLimitJoint(JARA_ARM::LimitSeq_out softLimit);
   /*!
   * @brief ユニットの状態取得
   * @param state ユニットの状態を表すビットコード
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getState(JARA_ARM::ULONG& state);
   /*!
   * @brief 全軸サーボ OFF
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *servoOFF();
   /*!
   * @brief 全軸サーボ ON
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *servoON();
   /*!
   * @brief 関節座標系のソフトリミット値設定
   * @param softLimit 各軸のソフトリミット値[単位:degree]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setSoftLimitJoint(const JARA_ARM::LimitSeq &softLimit);

private:
   RobotArm *m_robotArm;
   std::vector<JARA_ARM::Alarm> alarmList;

};



#endif // MANIPULATORCOMMONINTERFACE_COMMONSVC_IMPL_H


