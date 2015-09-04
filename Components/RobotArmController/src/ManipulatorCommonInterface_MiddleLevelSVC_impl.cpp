// -*-C++-*-
/*!
 * @file  ManipulatorCommonInterface_MiddleLevelSVC_impl.cpp
 * @brief �T�C���X�}�[�g��4���R�x���{�b�g�A�[���p�����x�����[�V�����R�}���h
 *
 */

#include "ManipulatorCommonInterface_MiddleLevelSVC_impl.h"
#include "defreturnid.h"

/*!
* @brief �T�C���X�}�[�g��4���R�x���{�b�g�A�[���p�����x�����[�V�����R�}���h�̃R���X�g���N�^
* @param ra ���{�b�g�A�[������I�u�W�F�N�g
*/
ManipulatorCommonInterface_MiddleSVC_impl::ManipulatorCommonInterface_MiddleSVC_impl(RobotArm *ra)
{
	m_robotArm = ra;
  
}


/*!
* @brief �T�C���X�}�[�g��4���R�x���{�b�g�A�[���p�����x�����[�V�����R�}���h�̃f�X�g���N�^
*/
ManipulatorCommonInterface_MiddleSVC_impl::~ManipulatorCommonInterface_MiddleSVC_impl()
{

}


/*!
* @brief �O���b�p�����S�ɕ���
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::closeGripper()
{
	m_robotArm->closeGripper();

	RETURNID_OK;
}

/*!
* @brief �A�[�����W�n���烍�{�b�g���W�n�܂ł̃x�[�X�I�t�Z�b�g���擾����(������)
* @param offset �I�t�Z�b�g��
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::getBaseOffset(JARA_ARM::HgMatrix offset)
{
	RETURNID_OK;
}

/*!
* @brief ���{�b�g���W�n�̈ʒu�t�B�[�h�o�b�N�����擾����
* @param pos �ʒu�t�B�[�h�o�b�N���[�P��:mm�degree]
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
* @brief ������Ԃɂ����铮�쎞�̍ő呬�x���擾����(������)
* @param speed �ő���i���x[�P��:mm/s]�A�ő��]���x[�P��:degree/s]����Ȃ�ő呬�x���
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::getMaxSpeedCartesian(JARA_ARM::CartesianSpeed_out speed)
{
	RETURNID_OK;
}

/*!
* @brief �֐ߋ�Ԃɂ����铮�쎞�̍ő呬�x���擾����(������)
* @param speed �e���̍ő哮�쑬�x[�P��:degree/s]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::getMaxSpeedJoint(JARA_ARM::DoubleSeq_out speed)
{
	speed = new JARA_ARM::DoubleSeq;
	RETURNID_OK;
}


/*!
* @brief ���𓮍쎞�̍ő呬�x�܂ł̍ŏ��������Ԃ��擾����(������)
* @param aclTime �ŏ���������[�P��:s]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::getMinAccelTimeCartesian(CORBA::Double& aclTime)
{
	RETURNID_OK;
}

/*!
* @brief �֐ߓ��쎞�̍ő呬�x�܂ł̍ŏ�����������Ԃ��擾����(������)
* @param aclTime �ŏ���������[�P��:s]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::getMinAccelTimeJoint(CORBA::Double& aclTime)
{
	RETURNID_OK;
}

/*!
* @brief ���{�b�g���W�n�ł̃\�t�g���~�b�g�l���擾����(������)
* @param xLimit X���̃\�t�g���~�b�g�l[�P��:mm]
* @param yLimit Y���̃\�t�g���~�b�g�l[�P��:mm]
* @param zLimit Z���̃\�t�g���~�b�g�l[�P��:mm]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::getSoftLimitCartesian(JARA_ARM::LimitValue_out xLimit, JARA_ARM::LimitValue_out yLimit, JARA_ARM::LimitValue_out zLimit)
{
	RETURNID_OK;
}

/*!
* @brief �O���b�p���w�肵���J�p�x�Ƃ���(������)
* @param angleRatio �O���b�p�̊J�p�x����[%]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::moveGripper(JARA_ARM::ULONG angleRatio)
{
	RETURNID_OK;
}

/*!
* @brief ���{�b�g���W�n�̐�Βl�Ŏw�肳�ꂽ�ڕW�ʒu�ɑ΂��������Ԃɂ����钼����Ԃœ��삷��
* @param carPoint ��ΖڕW�ʒu�E�p��[�P��:mm�Adegree]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::moveLinearCartesianAbs(const JARA_ARM::CarPosWithElbow& carPoint)
{
	
	m_robotArm->addTargetPos(Vector3d(carPoint.carPos[0][3], carPoint.carPos[1][3], carPoint.carPos[2][3]), atan2(carPoint.carPos[1][0],carPoint.carPos[0][0]), -1);
	RETURNID_OK;
}

/*!
* @brief ���{�b�g���W�n�̑��Βl�Ŏw�肳�ꂽ�ڕW�ʒu�ɑ΂��������Ԃɂ����钼����Ԃœ��삷��
* @param carPoint ���ΖڕW�ʒu�E�p��[�P��:mm�Adegree]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::moveLinearCartesianRel(const JARA_ARM::CarPosWithElbow& carPoint)
{
	Vector3d pos = m_robotArm->calcKinematics();
	
	m_robotArm->addTargetPos(Vector3d(carPoint.carPos[0][3]+pos(0), carPoint.carPos[1][3]+pos(1), carPoint.carPos[2][3]+pos(2)), atan2(carPoint.carPos[1][0],carPoint.carPos[0][0])+m_robotArm->theta[3], -1);
	RETURNID_OK;
}

/*!
* @brief ���{�b�g���W�n�̐�Βl�Ŏw�肳�ꂽ�ڕW�ʒu�ɑ΂���֐ߋ�Ԃɂ����钼����Ԃœ��삷��(������)
* @param carPoint ��ΖڕW�ʒu�E�p��[�P��:mm�Adegree]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::movePTPCartesianAbs(const JARA_ARM::CarPosWithElbow& carPoint)
{
	RETURNID_OK;
}

/*!
* @brief ���{�b�g���W�n�̑��Βl�Ŏw�肳�ꂽ�ڕW�ʒu�ɑ΂���֐ߋ�Ԃɂ����钼����Ԃœ��삷��(������)
* @param carPoint ���ΖڕW�ʒu�E�p��[�P��:mm�Adegree]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::movePTPCartesianRel(const JARA_ARM::CarPosWithElbow& carPoint)
{
	RETURNID_OK;
}

/*!
* @brief ��Ί֐ߍ��W�Ŏw�肳�ꂽ�ڕW�ʒu�ɑ΂���֐ߋ�Ԃɂ����钼����Ԃœ��삷��
* @param jointPoints ��ΖڕW�ʒu[�P�� degree]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::movePTPJointAbs(const JARA_ARM::JointPos& jointPoints)
{
	
	double tp[4] = {jointPoints[0], jointPoints[1], jointPoints[2], jointPoints[3]};
	m_robotArm->addTargetJointPos(tp, -1);
	RETURNID_OK;
}

/*!
* @brief ���Ί֐ߍ��W�Ŏw�肳�ꂽ�ڕW�ʒu�ɑ΂���֐ߋ�Ԃɂ����钼����Ԃœ��삷��
* @param jointPoints ���ΖڕW�ʒu[�P�� degree]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::movePTPJointRel(const JARA_ARM::JointPos& jointPoints)
{
	
	double tp[4] = {jointPoints[0]+m_robotArm->theta[0], jointPoints[1]+m_robotArm->theta[1], jointPoints[2]+m_robotArm->theta[2], jointPoints[3]+m_robotArm->theta[3]};
	m_robotArm->addTargetJointPos(tp, -1);
	
	RETURNID_OK;
}

/*!
* @brief �O���b�p�����S�ɊJ��
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::openGripper()
{
	m_robotArm->openGripper();
	RETURNID_OK;
}

/*!
* @brief �}�j�s�����[�^�̑S�Ă̎����ꎞ��~����
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::pause()
{
	m_robotArm->pause();
	RETURNID_OK;
}

/*!
* @brief �}�j�s�����[�^�̓�����ĊJ����
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::resume()
{
	m_robotArm->resume();
	RETURNID_OK;
}

/*!
* @brief �}�j�s�����[�^�̓�����~����
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::stop()
{
	m_robotArm->stop();
	RETURNID_OK;
}

/*!
* @brief ������Ԃɂ����铮�쎞�̉������Ԃ�ݒ肷��(������)
* @param aclTime ��������[�P��:s]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setAccelTimeCartesian(CORBA::Double aclTime)
{
	RETURNID_OK;
}

/*!
* @brief �֐ߋ�Ԃɂ����铮�쎞�̉������Ԃ�ݒ肷��(������)
* @param aclTime ��������[�P��:s]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setAccelTimeJoint(CORBA::Double aclTime)
{
	RETURNID_OK;
}

/*!
* @brief �I�t�Z�b�g�ʂ�ݒ肷��(������)
* @param offset �I�t�Z�b�g��
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setBaseOffset(const JARA_ARM::HgMatrix offset)
{
	RETURNID_OK;
}

/*!
* @brief ����_�̃t�����W�ʂ���̃I�t�Z�b�g�ʂ�ݒ肷��(������)
* @param offset �I�t�Z�b�g��
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setControlPointOffset(const JARA_ARM::HgMatrix offset)
{
	RETURNID_OK;
}

/*!
* @brief ������Ԃɂ����铮�쎞�̍ő哮�쑬�x��ݒ肷��
* @param speed �ő���i���x[�P��:mm/s]�A�ő��]���x[�P��:degree/s]����Ȃ�ő呬�x���
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setMaxSpeedCartesian(const JARA_ARM::CartesianSpeed& speed)
{
	
	m_robotArm->MaxSpeedCartesianTrans = speed.translation;
	m_robotArm->MaxSpeedCartesianRot = speed.rotation;
	RETURNID_OK;
}

/*!
* @brief �֐ߋ�Ԃɂ����铮�쎞�̍ő哮�쑬�x��ݒ肷��
* @param speed �e���̍ő哮�쑬�x[�P��:degree/s]
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
* @brief ������Ԃɂ����铮�쎞�̍ő呬�x�܂ł̍ŏ��������Ԃ�ݒ肷��(������)
* @param aclTime �ŏ���������[�P��:s]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setMinAccelTimeCartesian(CORBA::Double aclTime)
{
	RETURNID_OK;
}

/*!
* @brief �֐ߋ�Ԃɂ����铮�쎞�̍ő呬�x�܂ł̍ŏ��������Ԃ�ݒ肷��(������)
* @param aclTime �ŏ���������[�P��:s]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setMinAccelTimeJoint(CORBA::Double aclTime)
{
	RETURNID_OK;
}

/*!
* @brief ���{�b�g���W�n�ł̃\�t�g���~�b�g�l��ݒ肷��(������)
* @param xLimit X���̃\�t�g���~�b�g�l[�P��:mm]
* @param yLimit Y���̃\�t�g���~�b�g�l[�P��:mm]
* @param zLimit Z���̃\�t�g���~�b�g�l[�P��:mm]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setSoftLimitCartesian(const JARA_ARM::LimitValue& xLimit, const JARA_ARM::LimitValue& yLimit, const JARA_ARM::LimitValue& zLimit)
{
	RETURNID_OK;
}

/*!
* @brief ������Ԃɂ����铮�쎞�̑��x�����w�肷��(������)
* @param spdRatio �ő呬�x�ɑ΂��銄���w��[�P��:%]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setSpeedCartesian(JARA_ARM::ULONG spdRatio)
{
	RETURNID_OK;
}

/*!
* @brief �֐ߋ�Ԃɂ����铮�쎞�̑��x�����w�肷��(������)
* @param spdRatio �ő呬�x�ɑ΂��銄���w��[�P��:%]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::setSpeedJoint(JARA_ARM::ULONG spdRatio)
{
	RETURNID_OK;
}

/*!
* @brief ���{�b�g���W�n�̐�Βl�Ŏw�肳�ꂽ���p�ʒu�E�ڕW�ʒu�ɑ΂��A������Ԃɂ�����~�ʕ�Ԃœ��삷��(������)
* @param carPointR ��Β��p�ʒu�E�p��[�P��:m�Aradian]
* @param carPointT ��ΖڕW�ʒu�E�p��[�P��:m�Aradian]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::moveCircularCartesianAbs(const JARA_ARM::CarPosWithElbow& carPointR, const JARA_ARM::CarPosWithElbow& carPointT)
{
	RETURNID_OK;
}

/*!
* @brief ���{�b�g���W�n�̑��Βl�Ŏw�肳�ꂽ���p�ʒu�E�ڕW�ʒu�ɑ΂��A������Ԃɂ�����~�ʕ�Ԃœ��삷��(������)
* @param carPointR ���Β��p�ʒu�E�p��[�P��:m�Aradian]
* @param carPointT ���ΖڕW�ʒu�E�p��[�P��:m�Aradian]
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::moveCircularCartesianRel(const JARA_ARM::CarPosWithElbow& carPointR, const JARA_ARM::CarPosWithElbow& carPointT)
{
	RETURNID_OK;
}

/*!
* @brief ���_���A���̈ʒu���֐ߍ��W�n�̐�Βl�Őݒ肷��
* @param jointPoint ��Έʒu[�P��:radian or m]
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
* @brief �֐ߍ��W�n�̐�Βl�Œ�`���ꂽ���_���A�ʒu���擾����
* @param jointPoint ��Έʒu[�P��:radian or m
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
* @brief �֐ߍ��W�n�̐�Βl�Ŏw�肳�ꂽ���_���A�ʒu�ɑ΂��A�֐ߋ�Ԃɂ����钼����Ԃœ��삷��
* @return JARA_ARM::RETURN_ID
*/
JARA_ARM::RETURN_ID *ManipulatorCommonInterface_MiddleSVC_impl::goHome()
{
	m_robotArm->goHomePosition();
	RETURNID_OK;
}



// End of example implementational code



