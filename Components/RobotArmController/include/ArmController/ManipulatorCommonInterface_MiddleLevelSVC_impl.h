// -*-C++-*-
/*!
 * @file  ManipulatorCommonInterface_MiddleLevelSVC_impl.h
 * @brief サインスマート製4自由度ロボットアーム用中レベルモーションコマンド
 *
 */

#include "ManipulatorCommonInterface_DataTypesSkel.h"
#include "BasicDataTypeSkel.h"

#include "ManipulatorCommonInterface_MiddleLevelSkel.h"

#ifndef MANIPULATORCOMMONINTERFACE_MIDDLELEVELSVC_IMPL_H
#define MANIPULATORCOMMONINTERFACE_MIDDLELEVELSVC_IMPL_H

#include "RobotArm.h"


 
/*!
 * @class ManipulatorCommonInterface_MiddleSVC_impl
 * @brief サインスマート製4自由度ロボットアーム用中レベルモーションコマンド
 */
class ManipulatorCommonInterface_MiddleSVC_impl
 : public virtual POA_JARA_ARM::ManipulatorCommonInterface_Middle,
   public virtual PortableServer::RefCountServantBase
{
 private:

   //virtual ~ManipulatorCommonInterface_MiddleSVC_impl();

 public:
   	/*!
	* @brief コンストラクタ
	* @param ra ロボットアーム制御オブジェクト
	*/
   ManipulatorCommonInterface_MiddleSVC_impl(RobotArm *ra);
   /*!
   * @brief デストラクタ
   */
   virtual ~ManipulatorCommonInterface_MiddleSVC_impl();

   /*!
   * @brief グリッパを完全に閉じる
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *closeGripper();
   /*!
   * @brief アーム座標系からロボット座標系までのベースオフセットを取得する(未実装)
   * @param offset オフセット量
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getBaseOffset(JARA_ARM::HgMatrix offset);
   /*!
   * @brief ロボット座標系の位置フィードバック情報を取得する
   * @param pos 位置フィードバック情報[単位:mm､degree]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getFeedbackPosCartesian(JARA_ARM::CarPosWithElbow_out pos);
   /*!
   * @brief 直交空間における動作時の最大速度を取得する(未実装)
   * @param speed 最大並進速度[単位:mm/s]、最大回転速度[単位:degree/s]からなる最大速度情報
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getMaxSpeedCartesian(JARA_ARM::CartesianSpeed_out speed);
   /*!
   * @brief 関節空間における動作時の最大速度を取得する(未実装)
   * @param speed 各軸の最大動作速度[単位:degree/s]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getMaxSpeedJoint(JARA_ARM::DoubleSeq_out speed);
   /*!
   * @brief 直交動作時の最大速度までの最小加速時間を取得する(未実装)
   * @param aclTime 最小加速時間[単位:s]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getMinAccelTimeCartesian(CORBA::Double& aclTime);
   /*!
   * @brief 関節動作時の最大速度までの最小動作加速時間を取得する(未実装)
   * @param aclTime 最小加速時間[単位:s]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getMinAccelTimeJoint(CORBA::Double& aclTime);
   /*!
   * @brief ロボット座標系でのソフトリミット値を取得する(未実装)
   * @param xLimit X軸のソフトリミット値[単位:mm]
   * @param yLimit Y軸のソフトリミット値[単位:mm]
   * @param zLimit Z軸のソフトリミット値[単位:mm]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getSoftLimitCartesian(JARA_ARM::LimitValue_out xLimit, JARA_ARM::LimitValue_out yLimit, JARA_ARM::LimitValue_out zLimit);
   /*!
   * @brief グリッパを指定した開閉角度とする(未実装)
   * @param angleRatio グリッパの開閉角度割合[%]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *moveGripper(JARA_ARM::ULONG angleRatio);
   /*!
   * @brief ロボット座標系の絶対値で指定された目標位置に対し､直交空間における直線補間で動作する
   * @param carPoint 絶対目標位置・姿勢[単位:mm、degree]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *moveLinearCartesianAbs(const JARA_ARM::CarPosWithElbow& carPoint);
   /*!
   * @brief ロボット座標系の相対値で指定された目標位置に対し､直交空間における直線補間で動作する
   * @param carPoint 相対目標位置・姿勢[単位:mm、degree]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *moveLinearCartesianRel(const JARA_ARM::CarPosWithElbow& carPoint);
   /*!
   * @brief ロボット座標系の絶対値で指定された目標位置に対し､関節空間における直線補間で動作する(未実装)
   * @param carPoint 絶対目標位置・姿勢[単位:mm、degree]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *movePTPCartesianAbs(const JARA_ARM::CarPosWithElbow& carPoint);
   /*!
   * @brief ロボット座標系の相対値で指定された目標位置に対し､関節空間における直線補間で動作する(未実装)
   * @param carPoint 相対目標位置・姿勢[単位:mm、degree]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *movePTPCartesianRel(const JARA_ARM::CarPosWithElbow& carPoint);
   /*!
   * @brief 絶対関節座標で指定された目標位置に対し､関節空間における直線補間で動作する
   * @param jointPoints 絶対目標位置[単位 degree]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *movePTPJointAbs(const JARA_ARM::JointPos& jointPoints);
   /*!
   * @brief 相対関節座標で指定された目標位置に対し､関節空間における直線補間で動作する
   * @param jointPoints 相対目標位置[単位 degree]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *movePTPJointRel(const JARA_ARM::JointPos& jointPoints);
   /*!
   * @brief グリッパを完全に開く
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *openGripper();
   /*!
   * @brief マニピュレータの全ての軸を一時停止する
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *pause();
   /*!
   * @brief マニピュレータの動作を再開する
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *resume();
   /*!
   * @brief マニピュレータの動作を停止する
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *stop();
   /*!
   * @brief 直交空間における動作時の加速時間を設定する(未実装)
   * @param aclTime 加速時間[単位:s]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setAccelTimeCartesian(CORBA::Double aclTime);
   /*!
   * @brief 関節空間における動作時の加速時間を設定する(未実装)
   * @param aclTime 加速時間[単位:s]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setAccelTimeJoint(CORBA::Double aclTime);
   /*!
   * @brief オフセット量を設定する(未実装)
   * @param offset オフセット量
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setBaseOffset(const JARA_ARM::HgMatrix offset);
   /*!
   * @brief 制御点のフランジ面からのオフセット量を設定する(未実装)
   * @param offset オフセット量
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setControlPointOffset(const JARA_ARM::HgMatrix offset);
   /*!
   * @brief 直交空間における動作時の最大動作速度を設定する
   * @param speed 最大並進速度[単位:mm/s]、最大回転速度[単位:degree/s]からなる最大速度情報
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setMaxSpeedCartesian(const JARA_ARM::CartesianSpeed& speed);
   /*!
   * @brief 関節空間における動作時の最大動作速度を設定する
   * @param speed 各軸の最大動作速度[単位:degree/s]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setMaxSpeedJoint(const JARA_ARM::DoubleSeq& speed);
   /*!
   * @brief 直交空間における動作時の最大速度までの最小加速時間を設定する(未実装)
   * @param aclTime 最小加速時間[単位:s]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setMinAccelTimeCartesian(CORBA::Double aclTime);
   /*!
   * @brief 関節空間における動作時の最大速度までの最小加速時間を設定する(未実装)
   * @param aclTime 最小加速時間[単位:s]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setMinAccelTimeJoint(CORBA::Double aclTime);
   /*!
   * @brief ロボット座標系でのソフトリミット値を設定する(未実装)
   * @param xLimit X軸のソフトリミット値[単位:mm]
   * @param yLimit Y軸のソフトリミット値[単位:mm]
   * @param zLimit Z軸のソフトリミット値[単位:mm]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setSoftLimitCartesian(const JARA_ARM::LimitValue& xLimit, const JARA_ARM::LimitValue& yLimit, const JARA_ARM::LimitValue& zLimit);
   /*!
   * @brief 直交空間における動作時の速度を％指定する(未実装)
   * @param spdRatio 最大速度に対する割合指定[単位:%]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setSpeedCartesian(JARA_ARM::ULONG spdRatio);
   /*!
   * @brief 関節空間における動作時の速度を％指定する(未実装)
   * @param spdRatio 最大速度に対する割合指定[単位:%]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setSpeedJoint(JARA_ARM::ULONG spdRatio);
   /*!
   * @brief ロボット座標系の絶対値で指定された中継位置・目標位置に対し、直交空間における円弧補間で動作する(未実装)
   * @param carPointR 絶対中継位置・姿勢[単位:m、radian]
   * @param carPointT 絶対目標位置・姿勢[単位:m、radian]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *moveCircularCartesianAbs(const JARA_ARM::CarPosWithElbow& carPointR, const JARA_ARM::CarPosWithElbow& carPointT);
   /*!
   * @brief ロボット座標系の相対値で指定された中継位置・目標位置に対し、直交空間における円弧補間で動作する
   * @param carPointR 相対中継位置・姿勢[単位:m、radian]
   * @param carPointT 相対目標位置・姿勢[単位:m、radian]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *moveCircularCartesianRel(const JARA_ARM::CarPosWithElbow& carPointR, const JARA_ARM::CarPosWithElbow& carPointT);
   /*!
   * @brief 原点復帰時の位置を関節座標系の絶対値で設定する
   * @param jointPoint 絶対位置[単位:radian or m]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setHome(const JARA_ARM::JointPos& jointPoint);
   /*!
   * @brief 関節座標系の絶対値で定義された原点復帰位置を取得する
   * @param jointPoint 絶対位置[単位:radian or m
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getHome(JARA_ARM::JointPos_out jointPoint);
   /*!
   * @brief 関節座標系の絶対値で指定された原点復帰位置に対し、関節空間における直線補間で動作する
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *goHome();

private:
	RobotArm *m_robotArm;

};



#endif // MANIPULATORCOMMONINTERFACE_MIDDLELEVELSVC_IMPL_H


