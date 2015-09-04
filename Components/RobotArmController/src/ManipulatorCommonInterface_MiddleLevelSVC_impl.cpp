// -*-C++-*-
/*!
 * @file  ManipulatorCommonInterface_MiddleLevelSVC_impl.cpp
 * @brief サインスマート製4自由度ロボットアーム用中レベルモーションコマンド
 *
 */

#include "ManipulatorCommonInterface_MiddleLevelSVC_impl.h"
#include "defreturnid.h"

/*!
* @brief サインスマート製4自由度ロボットアーム用中レベルモーションコマンドのコンストラクタ
* @param ra ロボットアーム制御オブジェクト
*/
ManipulatorCommonInterface_MiddleSVC_impl::ManipulatorCommonInterface_MiddleSVC_impl(RobotArm *ra)
{
	m_robotArm = ra;
  
}


/*!
* @brief サインスマート製4自由度ロボットアーム用中レベルモーションコマンドのデストラクタ
*/
ManipulatorCommonInterface_MiddleSVC_impl::~ManipulatorCommonInterface_MiddleSVC_impl()
{

}


/*!
* @brief グリッパを完全に閉じる
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::closeGripper()
{
	m_robotArm->closeGripper();

	RETURNID_OK;
}

/*!
* @brief アーム座標系からロボット座標系までのベースオフセットを取得する(未実装)
* @param offset オフセット量
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::getBaseOffset(JARA_ARM::HgMatrix offset)
{
	RETURNID_OK;
}

/*!
* @brief ロボット座標系の位置フィードバック情報を取得する
* @param pos 位置フィードバック情報[単位:mm､degree]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::getFeedbackPosCartesian(JARA_ARM::CarPosWithElbow_out pos)
{
	
	JARA_ARM::CarPosWithElbow_var cpos_var = new JARA_ARM::CarPosWithElbow;
	
	Vector3d p = m_robotArm->calcKinematics();
	cpos_var->carPos[0][0] = cos(m_robotArm->theta[3]);
	cpos_var->carPos[0][1] = -sin(m_robotArm->theta[3]);
	cpos_var->carPos[1][0] = sin(m_robotArm->theta[3]);
	cpos_var->carPos[1][1] = cos(m_robotArm->theta[3]);
	cpos_var->carPos[2][2] = 1;
	cpos_var->carPos[0][3] = p(0);
	cpos_var->carPos[1][3] = p(1);
	cpos_var->carPos[2][3] = p(2);
	pos = cpos_var._retn();
	RETURNID_OK;
}

/*!
* @brief 直交空間における動作時の最大速度を取得する(未実装)
* @param speed 最大並進速度[単位:mm/s]、最大回転速度[単位:degree/s]からなる最大速度情報
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::getMaxSpeedCartesian(JARA_ARM::CartesianSpeed_out speed)
{
	RETURNID_OK;
}

/*!
* @brief 関節空間における動作時の最大速度を取得する(未実装)
* @param speed 各軸の最大動作速度[単位:degree/s]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::getMaxSpeedJoint(JARA_ARM::DoubleSeq_out speed)
{
	speed = new JARA_ARM::DoubleSeq;
	RETURNID_OK;
}


/*!
* @brief 直交動作時の最大速度までの最小加速時間を取得する(未実装)
* @param aclTime 最小加速時間[単位:s]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::getMinAccelTimeCartesian(CORBA::Double& aclTime)
{
	RETURNID_OK;
}

/*!
* @brief 関節動作時の最大速度までの最小動作加速時間を取得する(未実装)
* @param aclTime 最小加速時間[単位:s]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::getMinAccelTimeJoint(CORBA::Double& aclTime)
{
	RETURNID_OK;
}

/*!
* @brief ロボット座標系でのソフトリミット値を取得する(未実装)
* @param xLimit X軸のソフトリミット値[単位:mm]
* @param yLimit Y軸のソフトリミット値[単位:mm]
* @param zLimit Z軸のソフトリミット値[単位:mm]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::getSoftLimitCartesian(JARA_ARM::LimitValue_out xLimit, JARA_ARM::LimitValue_out yLimit, JARA_ARM::LimitValue_out zLimit)
{
	RETURNID_OK;
}

/*!
* @brief グリッパを指定した開閉角度とする(未実装)
* @param angleRatio グリッパの開閉角度割合[%]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::moveGripper(JARA_ARM::ULONG angleRatio)
{
	RETURNID_OK;
}

/*!
* @brief ロボット座標系の絶対値で指定された目標位置に対し､直交空間における直線補間で動作する
* @param carPoint 絶対目標位置・姿勢[単位:mm、degree]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::moveLinearCartesianAbs(const JARA_ARM::CarPosWithElbow& carPoint)
{
	
	m_robotArm->addTargetPos(Vector3d(carPoint.carPos[0][3], carPoint.carPos[1][3], carPoint.carPos[2][3]), atan2(carPoint.carPos[1][0],carPoint.carPos[0][0]), -1);
	RETURNID_OK;
}

/*!
* @brief ロボット座標系の相対値で指定された目標位置に対し､直交空間における直線補間で動作する
* @param carPoint 相対目標位置・姿勢[単位:mm、degree]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::moveLinearCartesianRel(const JARA_ARM::CarPosWithElbow& carPoint)
{
	Vector3d pos = m_robotArm->calcKinematics();
	
	m_robotArm->addTargetPos(Vector3d(carPoint.carPos[0][3]+pos(0), carPoint.carPos[1][3]+pos(1), carPoint.carPos[2][3]+pos(2)), atan2(carPoint.carPos[1][0],carPoint.carPos[0][0])+m_robotArm->theta[3], -1);
	RETURNID_OK;
}

/*!
* @brief ロボット座標系の絶対値で指定された目標位置に対し､関節空間における直線補間で動作する(未実装)
* @param carPoint 絶対目標位置・姿勢[単位:mm、degree]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::movePTPCartesianAbs(const JARA_ARM::CarPosWithElbow& carPoint)
{
	RETURNID_OK;
}

/*!
* @brief ロボット座標系の相対値で指定された目標位置に対し､関節空間における直線補間で動作する(未実装)
* @param carPoint 相対目標位置・姿勢[単位:mm、degree]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::movePTPCartesianRel(const JARA_ARM::CarPosWithElbow& carPoint)
{
	RETURNID_OK;
}

/*!
* @brief 絶対関節座標で指定された目標位置に対し､関節空間における直線補間で動作する
* @param jointPoints 絶対目標位置[単位 degree]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::movePTPJointAbs(const JARA_ARM::JointPos& jointPoints)
{
	
	double tp[4] = {jointPoints[0], jointPoints[1], jointPoints[2], jointPoints[3]};
	m_robotArm->addTargetJointPos(tp, -1);
	RETURNID_OK;
}

/*!
* @brief 相対関節座標で指定された目標位置に対し､関節空間における直線補間で動作する
* @param jointPoints 相対目標位置[単位 degree]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::movePTPJointRel(const JARA_ARM::JointPos& jointPoints)
{
	
	double tp[4] = {jointPoints[0]+m_robotArm->theta[0], jointPoints[1]+m_robotArm->theta[1], jointPoints[2]+m_robotArm->theta[2], jointPoints[3]+m_robotArm->theta[3]};
	m_robotArm->addTargetJointPos(tp, -1);
	
	RETURNID_OK;
}

/*!
* @brief グリッパを完全に開く
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::openGripper()
{
	m_robotArm->openGripper();
	RETURNID_OK;
}

/*!
* @brief マニピュレータの全ての軸を一時停止する
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::pause()
{
	m_robotArm->pause();
	RETURNID_OK;
}

/*!
* @brief マニピュレータの動作を再開する
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::resume()
{
	m_robotArm->resume();
	RETURNID_OK;
}

/*!
* @brief マニピュレータの動作を停止する
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::stop()
{
	m_robotArm->stop();
	RETURNID_OK;
}

/*!
* @brief 直交空間における動作時の加速時間を設定する(未実装)
* @param aclTime 加速時間[単位:s]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setAccelTimeCartesian(CORBA::Double aclTime)
{
	RETURNID_OK;
}

/*!
* @brief 関節空間における動作時の加速時間を設定する(未実装)
* @param aclTime 加速時間[単位:s]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setAccelTimeJoint(CORBA::Double aclTime)
{
	RETURNID_OK;
}

/*!
* @brief オフセット量を設定する(未実装)
* @param offset オフセット量
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setBaseOffset(const JARA_ARM::HgMatrix offset)
{
	RETURNID_OK;
}

/*!
* @brief 制御点のフランジ面からのオフセット量を設定する(未実装)
* @param offset オフセット量
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setControlPointOffset(const JARA_ARM::HgMatrix offset)
{
	RETURNID_OK;
}

/*!
* @brief 直交空間における動作時の最大動作速度を設定する
* @param speed 最大並進速度[単位:mm/s]、最大回転速度[単位:degree/s]からなる最大速度情報
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setMaxSpeedCartesian(const JARA_ARM::CartesianSpeed& speed)
{
	
	m_robotArm->MaxSpeedCartesianTrans = speed.translation;
	m_robotArm->MaxSpeedCartesianRot = speed.rotation;
	RETURNID_OK;
}

/*!
* @brief 関節空間における動作時の最大動作速度を設定する
* @param speed 各軸の最大動作速度[単位:degree/s]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setMaxSpeedJoint(const JARA_ARM::DoubleSeq& speed)
{
	
	for(int i=0;i < 4;i++)
	{
		m_robotArm->MaxSpeedJoint[i] = speed[i];
	}
	RETURNID_OK;
}

/*!
* @brief 直交空間における動作時の最大速度までの最小加速時間を設定する(未実装)
* @param aclTime 最小加速時間[単位:s]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setMinAccelTimeCartesian(CORBA::Double aclTime)
{
	RETURNID_OK;
}

/*!
* @brief 関節空間における動作時の最大速度までの最小加速時間を設定する(未実装)
* @param aclTime 最小加速時間[単位:s]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setMinAccelTimeJoint(CORBA::Double aclTime)
{
	RETURNID_OK;
}

/*!
* @brief ロボット座標系でのソフトリミット値を設定する(未実装)
* @param xLimit X軸のソフトリミット値[単位:mm]
* @param yLimit Y軸のソフトリミット値[単位:mm]
* @param zLimit Z軸のソフトリミット値[単位:mm]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setSoftLimitCartesian(const JARA_ARM::LimitValue& xLimit, const JARA_ARM::LimitValue& yLimit, const JARA_ARM::LimitValue& zLimit)
{
	RETURNID_OK;
}

/*!
* @brief 直交空間における動作時の速度を％指定する(未実装)
* @param spdRatio 最大速度に対する割合指定[単位:%]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setSpeedCartesian(JARA_ARM::ULONG spdRatio)
{
	RETURNID_OK;
}

/*!
* @brief 関節空間における動作時の速度を％指定する(未実装)
* @param spdRatio 最大速度に対する割合指定[単位:%]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setSpeedJoint(JARA_ARM::ULONG spdRatio)
{
	RETURNID_OK;
}

/*!
* @brief ロボット座標系の絶対値で指定された中継位置・目標位置に対し、直交空間における円弧補間で動作する(未実装)
* @param carPointR 絶対中継位置・姿勢[単位:m、radian]
* @param carPointT 絶対目標位置・姿勢[単位:m、radian]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::moveCircularCartesianAbs(const JARA_ARM::CarPosWithElbow& carPointR, const JARA_ARM::CarPosWithElbow& carPointT)
{
	RETURNID_OK;
}

/*!
* @brief ロボット座標系の相対値で指定された中継位置・目標位置に対し、直交空間における円弧補間で動作する(未実装)
* @param carPointR 相対中継位置・姿勢[単位:m、radian]
* @param carPointT 相対目標位置・姿勢[単位:m、radian]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::moveCircularCartesianRel(const JARA_ARM::CarPosWithElbow& carPointR, const JARA_ARM::CarPosWithElbow& carPointT)
{
	RETURNID_OK;
}

/*!
* @brief 原点復帰時の位置を関節座標系の絶対値で設定する
* @param jointPoint 絶対位置[単位:radian or m]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setHome(const JARA_ARM::JointPos& jointPoint)
{
	if(jointPoint.length() > 2)
	{
		double jpos[3] = {jointPoint[0], jointPoint[1], jointPoint[2]};
		m_robotArm->setHomePosition(jpos);
	}

	RETURNID_OK;
}

/*!
* @brief 関節座標系の絶対値で定義された原点復帰位置を取得する
* @param jointPoint 絶対位置[単位:radian or m
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::getHome(JARA_ARM::JointPos_out jointPoint)
{
	jointPoint = new JARA_ARM::JointPos;
	(*jointPoint).length(m_robotArm->axisNum);
	for(int i=0;i < m_robotArm->axisNum;i++)
		(*jointPoint)[i] = m_robotArm->homePosition(i);
	RETURNID_OK;
}

/*!
* @brief 関節座標系の絶対値で指定された原点復帰位置に対し、関節空間における直線補間で動作する
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::goHome()
{
	m_robotArm->goHomePosition();
	RETURNID_OK;
}



// End of example implementational code



