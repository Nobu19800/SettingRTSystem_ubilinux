// -*-C++-*-
/*!
 * @file  ManipulatorCommonInterface_MiddleLevelSVC_impl.h
 * @brief �T�C���X�}�[�g��4���R�x���{�b�g�A�[���p�����x�����[�V�����R�}���h
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
 * @brief �T�C���X�}�[�g��4���R�x���{�b�g�A�[���p�����x�����[�V�����R�}���h
 */
class ManipulatorCommonInterface_MiddleSVC_impl
 : public virtual POA_JARA_ARM::ManipulatorCommonInterface_Middle,
   public virtual PortableServer::RefCountServantBase
{
 private:

   //virtual ~ManipulatorCommonInterface_MiddleSVC_impl();

 public:
   	/*!
	* @brief �R���X�g���N�^
	* @param ra ���{�b�g�A�[������I�u�W�F�N�g
	*/
   ManipulatorCommonInterface_MiddleSVC_impl(RobotArm *ra);
   /*!
   * @brief �f�X�g���N�^
   */
   virtual ~ManipulatorCommonInterface_MiddleSVC_impl();

   /*!
   * @brief �O���b�p�����S�ɕ���
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *closeGripper();
   /*!
   * @brief �A�[�����W�n���烍�{�b�g���W�n�܂ł̃x�[�X�I�t�Z�b�g���擾����(������)
   * @param offset �I�t�Z�b�g��
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getBaseOffset(JARA_ARM::HgMatrix offset);
   /*!
   * @brief ���{�b�g���W�n�̈ʒu�t�B�[�h�o�b�N�����擾����
   * @param pos �ʒu�t�B�[�h�o�b�N���[�P��:mm�degree]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getFeedbackPosCartesian(JARA_ARM::CarPosWithElbow_out pos);
   /*!
   * @brief ������Ԃɂ����铮�쎞�̍ő呬�x���擾����(������)
   * @param speed �ő���i���x[�P��:mm/s]�A�ő��]���x[�P��:degree/s]����Ȃ�ő呬�x���
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getMaxSpeedCartesian(JARA_ARM::CartesianSpeed_out speed);
   /*!
   * @brief �֐ߋ�Ԃɂ����铮�쎞�̍ő呬�x���擾����(������)
   * @param speed �e���̍ő哮�쑬�x[�P��:degree/s]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getMaxSpeedJoint(JARA_ARM::DoubleSeq_out speed);
   /*!
   * @brief ���𓮍쎞�̍ő呬�x�܂ł̍ŏ��������Ԃ��擾����(������)
   * @param aclTime �ŏ���������[�P��:s]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getMinAccelTimeCartesian(CORBA::Double& aclTime);
   /*!
   * @brief �֐ߓ��쎞�̍ő呬�x�܂ł̍ŏ�����������Ԃ��擾����(������)
   * @param aclTime �ŏ���������[�P��:s]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getMinAccelTimeJoint(CORBA::Double& aclTime);
   /*!
   * @brief ���{�b�g���W�n�ł̃\�t�g���~�b�g�l���擾����(������)
   * @param xLimit X���̃\�t�g���~�b�g�l[�P��:mm]
   * @param yLimit Y���̃\�t�g���~�b�g�l[�P��:mm]
   * @param zLimit Z���̃\�t�g���~�b�g�l[�P��:mm]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getSoftLimitCartesian(JARA_ARM::LimitValue_out xLimit, JARA_ARM::LimitValue_out yLimit, JARA_ARM::LimitValue_out zLimit);
   /*!
   * @brief �O���b�p���w�肵���J�p�x�Ƃ���(������)
   * @param angleRatio �O���b�p�̊J�p�x����[%]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *moveGripper(JARA_ARM::ULONG angleRatio);
   /*!
   * @brief ���{�b�g���W�n�̐�Βl�Ŏw�肳�ꂽ�ڕW�ʒu�ɑ΂��������Ԃɂ����钼����Ԃœ��삷��
   * @param carPoint ��ΖڕW�ʒu�E�p��[�P��:mm�Adegree]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *moveLinearCartesianAbs(const JARA_ARM::CarPosWithElbow& carPoint);
   /*!
   * @brief ���{�b�g���W�n�̑��Βl�Ŏw�肳�ꂽ�ڕW�ʒu�ɑ΂��������Ԃɂ����钼����Ԃœ��삷��
   * @param carPoint ���ΖڕW�ʒu�E�p��[�P��:mm�Adegree]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *moveLinearCartesianRel(const JARA_ARM::CarPosWithElbow& carPoint);
   /*!
   * @brief ���{�b�g���W�n�̐�Βl�Ŏw�肳�ꂽ�ڕW�ʒu�ɑ΂���֐ߋ�Ԃɂ����钼����Ԃœ��삷��(������)
   * @param carPoint ��ΖڕW�ʒu�E�p��[�P��:mm�Adegree]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *movePTPCartesianAbs(const JARA_ARM::CarPosWithElbow& carPoint);
   /*!
   * @brief ���{�b�g���W�n�̑��Βl�Ŏw�肳�ꂽ�ڕW�ʒu�ɑ΂���֐ߋ�Ԃɂ����钼����Ԃœ��삷��(������)
   * @param carPoint ���ΖڕW�ʒu�E�p��[�P��:mm�Adegree]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *movePTPCartesianRel(const JARA_ARM::CarPosWithElbow& carPoint);
   /*!
   * @brief ��Ί֐ߍ��W�Ŏw�肳�ꂽ�ڕW�ʒu�ɑ΂���֐ߋ�Ԃɂ����钼����Ԃœ��삷��
   * @param jointPoints ��ΖڕW�ʒu[�P�� degree]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *movePTPJointAbs(const JARA_ARM::JointPos& jointPoints);
   /*!
   * @brief ���Ί֐ߍ��W�Ŏw�肳�ꂽ�ڕW�ʒu�ɑ΂���֐ߋ�Ԃɂ����钼����Ԃœ��삷��
   * @param jointPoints ���ΖڕW�ʒu[�P�� degree]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *movePTPJointRel(const JARA_ARM::JointPos& jointPoints);
   /*!
   * @brief �O���b�p�����S�ɊJ��
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *openGripper();
   /*!
   * @brief �}�j�s�����[�^�̑S�Ă̎����ꎞ��~����
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *pause();
   /*!
   * @brief �}�j�s�����[�^�̓�����ĊJ����
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *resume();
   /*!
   * @brief �}�j�s�����[�^�̓�����~����
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *stop();
   /*!
   * @brief ������Ԃɂ����铮�쎞�̉������Ԃ�ݒ肷��(������)
   * @param aclTime ��������[�P��:s]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setAccelTimeCartesian(CORBA::Double aclTime);
   /*!
   * @brief �֐ߋ�Ԃɂ����铮�쎞�̉������Ԃ�ݒ肷��(������)
   * @param aclTime ��������[�P��:s]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setAccelTimeJoint(CORBA::Double aclTime);
   /*!
   * @brief �I�t�Z�b�g�ʂ�ݒ肷��(������)
   * @param offset �I�t�Z�b�g��
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setBaseOffset(const JARA_ARM::HgMatrix offset);
   /*!
   * @brief ����_�̃t�����W�ʂ���̃I�t�Z�b�g�ʂ�ݒ肷��(������)
   * @param offset �I�t�Z�b�g��
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setControlPointOffset(const JARA_ARM::HgMatrix offset);
   /*!
   * @brief ������Ԃɂ����铮�쎞�̍ő哮�쑬�x��ݒ肷��
   * @param speed �ő���i���x[�P��:mm/s]�A�ő��]���x[�P��:degree/s]����Ȃ�ő呬�x���
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setMaxSpeedCartesian(const JARA_ARM::CartesianSpeed& speed);
   /*!
   * @brief �֐ߋ�Ԃɂ����铮�쎞�̍ő哮�쑬�x��ݒ肷��
   * @param speed �e���̍ő哮�쑬�x[�P��:degree/s]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setMaxSpeedJoint(const JARA_ARM::DoubleSeq& speed);
   /*!
   * @brief ������Ԃɂ����铮�쎞�̍ő呬�x�܂ł̍ŏ��������Ԃ�ݒ肷��(������)
   * @param aclTime �ŏ���������[�P��:s]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setMinAccelTimeCartesian(CORBA::Double aclTime);
   /*!
   * @brief �֐ߋ�Ԃɂ����铮�쎞�̍ő呬�x�܂ł̍ŏ��������Ԃ�ݒ肷��(������)
   * @param aclTime �ŏ���������[�P��:s]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setMinAccelTimeJoint(CORBA::Double aclTime);
   /*!
   * @brief ���{�b�g���W�n�ł̃\�t�g���~�b�g�l��ݒ肷��(������)
   * @param xLimit X���̃\�t�g���~�b�g�l[�P��:mm]
   * @param yLimit Y���̃\�t�g���~�b�g�l[�P��:mm]
   * @param zLimit Z���̃\�t�g���~�b�g�l[�P��:mm]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setSoftLimitCartesian(const JARA_ARM::LimitValue& xLimit, const JARA_ARM::LimitValue& yLimit, const JARA_ARM::LimitValue& zLimit);
   /*!
   * @brief ������Ԃɂ����铮�쎞�̑��x�����w�肷��(������)
   * @param spdRatio �ő呬�x�ɑ΂��銄���w��[�P��:%]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setSpeedCartesian(JARA_ARM::ULONG spdRatio);
   /*!
   * @brief �֐ߋ�Ԃɂ����铮�쎞�̑��x�����w�肷��(������)
   * @param spdRatio �ő呬�x�ɑ΂��銄���w��[�P��:%]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setSpeedJoint(JARA_ARM::ULONG spdRatio);
   /*!
   * @brief ���{�b�g���W�n�̐�Βl�Ŏw�肳�ꂽ���p�ʒu�E�ڕW�ʒu�ɑ΂��A������Ԃɂ�����~�ʕ�Ԃœ��삷��(������)
   * @param carPointR ��Β��p�ʒu�E�p��[�P��:m�Aradian]
   * @param carPointT ��ΖڕW�ʒu�E�p��[�P��:m�Aradian]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *moveCircularCartesianAbs(const JARA_ARM::CarPosWithElbow& carPointR, const JARA_ARM::CarPosWithElbow& carPointT);
   /*!
   * @brief ���{�b�g���W�n�̑��Βl�Ŏw�肳�ꂽ���p�ʒu�E�ڕW�ʒu�ɑ΂��A������Ԃɂ�����~�ʕ�Ԃœ��삷��
   * @param carPointR ���Β��p�ʒu�E�p��[�P��:m�Aradian]
   * @param carPointT ���ΖڕW�ʒu�E�p��[�P��:m�Aradian]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *moveCircularCartesianRel(const JARA_ARM::CarPosWithElbow& carPointR, const JARA_ARM::CarPosWithElbow& carPointT);
   /*!
   * @brief ���_���A���̈ʒu���֐ߍ��W�n�̐�Βl�Őݒ肷��
   * @param jointPoint ��Έʒu[�P��:radian or m]
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *setHome(const JARA_ARM::JointPos& jointPoint);
   /*!
   * @brief �֐ߍ��W�n�̐�Βl�Œ�`���ꂽ���_���A�ʒu���擾����
   * @param jointPoint ��Έʒu[�P��:radian or m
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *getHome(JARA_ARM::JointPos_out jointPoint);
   /*!
   * @brief �֐ߍ��W�n�̐�Βl�Ŏw�肳�ꂽ���_���A�ʒu�ɑ΂��A�֐ߋ�Ԃɂ����钼����Ԃœ��삷��
   * @return JARA_ARM::RETURN_ID
   */
   JARA_ARM::RETURN_ID *goHome();

private:
	RobotArm *m_robotArm;

};



#endif // MANIPULATORCOMMONINTERFACE_MIDDLELEVELSVC_IMPL_H


