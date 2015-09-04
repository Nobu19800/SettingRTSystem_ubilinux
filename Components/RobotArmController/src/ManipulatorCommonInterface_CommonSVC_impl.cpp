// -*-C++-*-
/*!
 * @file  ManipulatorCommonInterface_CommonSVC_impl.cpp
 * @brief サインスマート製4自由度ロボットアーム用低レベルモーションコマンド
 *
 */

#include "ManipulatorCommonInterface_CommonSVC_impl.h"
#include "defreturnid.h"

/*!
* @brief サインスマート製4自由度ロボットアーム用低レベルモーションコマンドのコンストラクタ
* @param ra ロボットアーム制御オブジェクト
*/
ManipulatorCommonInterface_CommonSVC_impl::ManipulatorCommonInterface_CommonSVC_impl(RobotArm *ra)
{
  m_robotArm = ra;
}

/*!
* @brief サインスマート製4自由度ロボットアーム用低レベルモーションコマンドのデストラクタ
*/
ManipulatorCommonInterface_CommonSVC_impl::~ManipulatorCommonInterface_CommonSVC_impl()
{

}


/*!
* @brief アラームクリア
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::clearAlarms()
{
	RETURNID_OK;
}
/*!
* @brief アラーム情報の取得
* @param alarms アラーム情報の配列
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::getActiveAlarm(JARA_ARM::AlarmSeq_out alarms)
{
	alarms = new JARA_ARM::AlarmSeq;
	RETURNID_OK;
}
/*!
* @brief 関節座標系の位置フィードバック情報の取得
* @param pos 位置フィードバック情報(シーケンス型)
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::getFeedbackPosJoint(JARA_ARM::JointPos_out pos)
{
	pos = new JARA_ARM::JointPos;
	pos->length(m_robotArm->axisNum);
	for(int i=0;i < m_robotArm->axisNum;i++)
	{
		(*pos)[i] = m_robotArm->theta[i];
	}

	RETURNID_OK;
}
/*!
* @brief マニピュレータ情報の取得
* @param mInfo マニピュレータ情報
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::getManipInfo(JARA_ARM::ManipInfo_out mInfo)
{
	mInfo = new JARA_ARM::ManipInfo;
	mInfo->manufactur = m_robotArm->manifactur.c_str();
	mInfo->type = m_robotArm->type.c_str();
	mInfo->axisNum = m_robotArm->axisNum;
	mInfo->cmdCycle = m_robotArm->cmdCycle;
	mInfo->isGripper = m_robotArm->isGripper;

	RETURNID_OK;
}
/*!
* @brief 関節座標系のソフトリミット値を取得
* @param softLimit 各軸のソフトリミット値[単位:degree]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::getSoftLimitJoint(JARA_ARM::LimitSeq_out softLimit)
{
	softLimit = new JARA_ARM::LimitSeq;
	softLimit->length(m_robotArm->axisNum);
	for(int i=0;i < m_robotArm->axisNum;i++)
	{
		(*softLimit)[i].lower = m_robotArm->softUpperLimitJoint[i];
		(*softLimit)[i].upper = m_robotArm->softLowerLimitJoint[i];
	}

	RETURNID_OK;
}
/*!
* @brief ユニットの状態取得
* @param state ユニットの状態を表すビットコード
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::getState(JARA_ARM::ULONG& state)
{
	state = 0;
	RETURNID_OK;
}
/*!
* @brief 全軸サーボ OFF
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::servoOFF()
{
	m_robotArm->setSerbo(false);
	RETURNID_OK;
}
/*!
* @brief 全軸サーボ ON
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::servoON()
{
	m_robotArm->setSerbo(true);
	RETURNID_OK;
}
/*!
* @brief 関節座標系のソフトリミット値設定
* @param softLimit 各軸のソフトリミット値[単位:degree]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::setSoftLimitJoint(const JARA_ARM::LimitSeq &softLimit)
{
	for(int i=0;i<softLimit.length()&&i<m_robotArm->axisNum;i++){
		m_robotArm->softUpperLimitJoint[i] = softLimit[i].lower;
		m_robotArm->softLowerLimitJoint[i] = softLimit[i].upper;
	}
	RETURNID_OK;
}

