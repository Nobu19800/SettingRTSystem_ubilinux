// -*-C++-*-
/*!
 * @file  ManipulatorCommonInterface_CommonSVC_impl.cpp
 * @brief �T�C���X�}�[�g��4���R�x���{�b�g�A�[���p�჌�x�����[�V�����R�}���h
 *
 */

#include "ManipulatorCommonInterface_CommonSVC_impl.h"
#include "defreturnid.h"

/*!
* @brief �T�C���X�}�[�g��4���R�x���{�b�g�A�[���p�჌�x�����[�V�����R�}���h�̃R���X�g���N�^
* @param ra ���{�b�g�A�[������I�u�W�F�N�g
*/
ManipulatorCommonInterface_CommonSVC_impl::ManipulatorCommonInterface_CommonSVC_impl(RobotArm *ra)
{
  m_robotArm = ra;
}

/*!
* @brief �T�C���X�}�[�g��4���R�x���{�b�g�A�[���p�჌�x�����[�V�����R�}���h�̃f�X�g���N�^
*/
ManipulatorCommonInterface_CommonSVC_impl::~ManipulatorCommonInterface_CommonSVC_impl()
{

}


/*!
* @brief �A���[���N���A
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::clearAlarms()
{
	alarmList.clear();
	RETURNID_OK;
}
/*!
* @brief �A���[�����̎擾
* @param alarms �A���[�����̔z��
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::getActiveAlarm(JARA_ARM::AlarmSeq_out alarms)
{
	alarms = new JARA_ARM::AlarmSeq;
	alarms->length(alarmList.size());
	for (int i = 0; i < alarmList.size(); i++)
	{
		(*alarms)[i].code = alarmList[i].code;
		(*alarms)[i].type = alarmList[i].type;
		(*alarms)[i].description = alarmList[i].description;
	}
	RETURNID_OK;
}
/*!
* @brief �֐ߍ��W�n�̈ʒu�t�B�[�h�o�b�N���̎擾
* @param pos �ʒu�t�B�[�h�o�b�N���(�V�[�P���X�^)
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
* @brief �}�j�s�����[�^���̎擾
* @param mInfo �}�j�s�����[�^���
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
* @brief �֐ߍ��W�n�̃\�t�g���~�b�g�l���擾
* @param softLimit �e���̃\�t�g���~�b�g�l[�P��:rad]
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
* @brief ���j�b�g�̏�Ԏ擾
* @param state ���j�b�g�̏�Ԃ�\���r�b�g�R�[�h
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::getState(JARA_ARM::ULONG& state)
{
	state = 0x00;
	if (m_robotArm->serbo)
	{
		state += JARA_ARM::CONST_BINARY_00000001;
	}
	if (!m_robotArm->stopFalg)
	{
		state += JARA_ARM::CONST_BINARY_00000010;
	}
	if (alarmList.size() > 0)
	{
		state += JARA_ARM::CONST_BINARY_00000100;
	}
	if (m_robotArm->pauseFalg > 0)
	{
		state += 0x10;
	}
	RETURNID_OK;
}
/*!
* @brief �S���T�[�{ OFF
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::servoOFF()
{
	m_robotArm->setSerbo(false);
	RETURNID_OK;
}
/*!
* @brief �S���T�[�{ ON
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_CommonSVC_impl::servoON()
{
	m_robotArm->setSerbo(true);
	RETURNID_OK;
}
/*!
* @brief �֐ߍ��W�n�̃\�t�g���~�b�g�l�ݒ�
* @param softLimit �e���̃\�t�g���~�b�g�l[�P��:rad]
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

