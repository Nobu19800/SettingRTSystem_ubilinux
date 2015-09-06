// -*-C++-*-
/*!
 * @file  ManipulatorCommonInterface_CommonSVC_impl.h
 * @brief �T�C���X�}�[�g��4���R�x���{�b�g�A�[���p�჌�x�����[�V�����R�}���h
 * �R�����g���̓��{�b�g�A�[������@�\���ʃC���^�t�F�[�X�d�l�������p���܂���
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
 * @brief �T�C���X�}�[�g��4���R�x���{�b�g�A�[���p�჌�x�����[�V�����R�}���h
 */
class ManipulatorCommonInterface_CommonSVC_impl
 : public virtual POA_JARA_ARM::ManipulatorCommonInterface_Common,
   public virtual PortableServer::RefCountServantBase
{
 private:

   //virtual ~ManipulatorCommonInterface_CommonSVC_impl();

 public:
  /*!
   * @brief �R���X�g���N�^
   * @param ra ���{�b�g�A�[������I�u�W�F�N�g
   */
   ManipulatorCommonInterface_CommonSVC_impl(RobotArm *ra);
  /*!
   * @brief �f�X�g���N�^
   */
   virtual ~ManipulatorCommonInterface_CommonSVC_impl();

   /*!
   * @brief �A���[���N���A
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *clearAlarms();
   /*!
   * @brief �A���[�����̎擾
   * @param alarms �A���[�����̔z��
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getActiveAlarm(JARA_ARM::AlarmSeq_out alarms);
   /*!
   * @brief �֐ߍ��W�n�̈ʒu�t�B�[�h�o�b�N���̎擾
   * @param pos �ʒu�t�B�[�h�o�b�N���(�V�[�P���X�^)
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getFeedbackPosJoint(JARA_ARM::JointPos_out pos);
   /*!
   * @brief �}�j�s�����[�^���̎擾
   * @param mInfo �}�j�s�����[�^���
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getManipInfo(JARA_ARM::ManipInfo_out mInfo);
   /*!
   * @brief �֐ߍ��W�n�̃\�t�g���~�b�g�l���擾
   * @param softLimit �e���̃\�t�g���~�b�g�l[�P��:degree]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getSoftLimitJoint(JARA_ARM::LimitSeq_out softLimit);
   /*!
   * @brief ���j�b�g�̏�Ԏ擾
   * @param state ���j�b�g�̏�Ԃ�\���r�b�g�R�[�h
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getState(JARA_ARM::ULONG& state);
   /*!
   * @brief �S���T�[�{ OFF
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *servoOFF();
   /*!
   * @brief �S���T�[�{ ON
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *servoON();
   /*!
   * @brief �֐ߍ��W�n�̃\�t�g���~�b�g�l�ݒ�
   * @param softLimit �e���̃\�t�g���~�b�g�l[�P��:degree]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setSoftLimitJoint(const JARA_ARM::LimitSeq &softLimit);

private:
   RobotArm *m_robotArm;
   std::vector<JARA_ARM::Alarm> alarmList;

};



#endif // MANIPULATORCOMMONINTERFACE_COMMONSVC_IMPL_H


