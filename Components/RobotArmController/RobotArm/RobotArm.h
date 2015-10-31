/*!
* @file  RobotArm.h
* @brief �T�C���X�}�[�g��4���R�x���{�b�g�A�[������N���X
*
*/


#ifndef ROBOTARM_H
#define ROBOTARM_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/LU>
#include <vector>

using namespace Eigen;



enum MoveType { Joint = 0, Point = 1, };

/**
* @class TargetPos
*@brief ���ʒu(�������͊֐ߊp�x)�̖ڕW�ʒu�A�����ʒu�A���B���ԓ����i�[����N���X
*/
class TargetPos
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	TargetPos();
	double end_time;
	double time;
	MoveType type;
	Vector3d start_pos;
	Vector3d target_pos;
	double start_joint_pos[4];
	double target_joint_pos[4];
	double target_theta;
	double start_theta; 

	/**
	*@brief �ڕW���ʒu��ݒ�
	* @param t ���B����(0�ȉ��ɐݒ肵���ꍇ�͏����ʒu�ƖڕW�ʒu�Ƃ̋������玩���I�Ɍv�Z)
	* @param t_p ���ʒu
	* @param the ���p��
	*/
	void setPoint(double t, Vector3d t_p, double the);
	/**
	*@brief �ڕW�֐ߊp�x��ݒ�
	* @param t ���B����(0�ȉ��ɐݒ肵���ꍇ�͏����֐ߊp�x�ƖڕW�֐ߊp�x�Ƃ̋������玩���I�Ɍv�Z)
	* @param t_p �֐ߊp�x
	*/
	void setJointPos(double t, double *t_p);
	/**
	*@brief �������ʒu��ݒ�
	* @param s_p �������ʒu
	* @param the �������p��
	* @param maxSpeedCartesianTrans ���̍ő呬�x
	* @param maxSpeedCartesianRot ���p���̍ő呬�x
	* @param minTime ���B���Ԃ̍ŏ��l
	*/
	void setStartPoint(Vector3d s_p, double the, double maxSpeedCartesianTrans, double maxSpeedCartesianRot, double minTime);
	/**
	*@brief �ڕW�֐ߊp�x��ݒ�
	* @param t ���B����
	* @param t_p �֐ߊp�x
	*/
	void setStartJointPos(double *s_p, double *maxSpeedJoint, double minTime);

	
};


/**
* @class RobotArm
*@brief �T�C���X�}�[�g��4���R�x���{�b�g�A�[������N���X
*/
class RobotArm
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	RobotArm();
	/**
	*@brief ���ʒu�擾
	*@param the �֐ߊp�x
	* @return ���ʒu
	*/
	Vector3d calcKinematics(double *the);
	/**
	*@brief �֐ߊp�x�����
	* @param t1 �֐ߊp�x(�֐�1)
	* @param t2 �֐ߊp�x(�֐�2)
	* @param t3 �֐ߊp�x(�֐�3)
	* @param t4 �֐ߊp�x(�֐�4)
	*/
	void setAngle(double t1, double t2, double t3, double t4);
	/**
	*@brief ���R�r�s��擾
	*@param the �֐ߊp�x
	* @return ���R�r�s��
	*/
	Matrix3d calcJacobian(double *the);
	/**
	*@brief ��摬�x����֐ߊp���x���擾
	* @param v ��摬�x
	* @return �֐ߊp���x
	*/
	Vector3d calcJointVel(Vector3d v);
	/**
	*@brief �֐ߊp���x�̓��͂���֐ߊp�x���X�V
	* @param v1 �֐ߊp���x(�֐�1)
	* @param v2 �֐ߊp���x(�֐�2)
	* @param v3 �֐ߊp���x(�֐�3)
	* @param v4 �֐ߊp���x(�֐�4)
	*/
	void updatePos(double v1, double v2, double v3, double v4);
	/**
	*@brief �֐ߊp�x�̃z�[���|�W�V������ݒ�
	* @param o1 �֐ߊp���x(�֐�1)
	* @param o2 �֐ߊp���x(�֐�2)
	* @param o3 �֐ߊp���x(�֐�3)
	* @param o4 �֐ߊp���x(�֐�4)
	*/
	void setOffset(double o1, double o2, double o3, double o4);
	/**
	*@brief �ڕW�ʒu�̃��X�g��0�Ԗڂɏ����ʒu�A���B���Ԃ�ݒ�
	*/
	void setTargetPos();
	/**
	*@brief �X�V
	* @param st ���ݕ�
	*/
	void update(double st);
	/**
	*@brief �O���b�p�[���J��
	*/
	void openGripper();
	/**
	*@brief �O���b�p�[�����
	*/
	void closeGripper();
	/**
	*@brief �ڕW�ʒu�ǉ�
	* @param p �ڕW���ʒu
	* @param the �ڕW���p��
	* @param T ���B����
	*/
	void addTargetPos(Vector3d p, double the, double T);
	/**
	*@brief �ڕW�֐ߊp�x�ǉ�
	* @param p �ڕW�֐ߊp�x
	* @param T ���B����
	*/
	void addTargetJointPos(double *p, double T);


	double l[4],lh,lf;
	double m[4],mh,mf;
	double wi, wf;
	double hi, hf;
	double rh;
	Vector3d *jl;
	Vector3d jh;
	Vector3d jf;
	Vector3d *pl;
	Vector3d ph;
	Vector3d pf;
	double hw;

	double theta[4];
	double homeTheta[4];

	double dt;
	//double endTime;
	double time;
	//Vector3d targetPoint;
	//Vector3d startPoint;

	double offset[4];

	double Kp;
	double Kjp;

	double gripperPos;

	std::vector<TargetPos> targetPoints;
	TargetPos targetPoint;

	/**
	*@brief �x�[�X�I�t�Z�b�g�̐ݒ�
	* @param bo �x�[�X�I�t�Z�b�g
	*/
	void setBaseOffset(double *bo);
	/**
	*@brief ���ő呬�x�̐ݒ�
	* @param msc ���ő呬�x
	*/
	void setMaxSpeedCartesian(Vector3d msc);
	/**
	*@brief �֐ߍő�p���x�̐ݒ�
	* @param msj �֐ߍő�p���x
	*/
	void setMaxSpeedJoint(double *msj);
	/**
	*@brief ���̃\�t�g���~�b�g�l�̐ݒ�
	* @param usl �\�t�g���~�b�g�̍ő�l
	* @param lsl �\�t�g���~�b�g�̍ŏ��l
	*/
	void setSoftLimitCartesian(Vector3d usl, Vector3d lsl);
	/**
	*@brief �ꎞ��~
	*/
	void pause();
	/**
	*@brief �ĊJ
	*/
	void resume();
	/**
	*@brief ��~
	*/
	void stop();
	/**
	*@brief �֐߂̃\�t�g���~�b�g�l�̐ݒ�
	* @param usl �\�t�g���~�b�g�̍ő�l
	* @param lsl �\�t�g���~�b�g�̍ŏ��l
	*/
	void setSoftLimitJoint(double *usl, double *lsl);
	/**
	*@brief �z�[���|�W�V�����Ɉړ�
	*/
	void goHomePosition();
	/**
	*@brief �z�[���|�W�V�����̐ݒ�
	* @param jp �z�[���|�W�V����
	*/
	void setHomePosition(double *jp);
	/**
	*@brief �T�[�{���I���A�I�t�ɂ���
	* @param state true�ŃI���Afalse�ŃI�t
	*/
	void setSerbo(bool state);
	/**
	*@brief �֐߁A���ʒu���\�t�g���~�b�g�����𔻒肷��
	*@param the �֐ߊp�x
	*@return �͈͓��̏ꍇtrue
	*/
	bool judgeSoftLimitJoint(double *the);
	/**
	*@brief ���ʒu���\�t�g���~�b�g�����𔻒肷��
	*@param pos ���ʒu
	*@return �͈͓��̏ꍇtrue
	*/
	bool judgeSoftLimitPos(Vector3d pos);
	


	double baseOffset[12];
	Vector3d maxSpeedCartesian;
	double maxSpeedJoint[4];
	Vector3d softUpperLimitCartesian;
	Vector3d softLowerLimitCartesian;
	bool pauseFalg;
	bool stopFalg;
	Vector3d homePosition;
	double softUpperLimitJoint[4];
	double softLowerLimitJoint[4];
	double jointOffset[4];
	double motorAngle[4];
	bool serbo;
	std::string manifactur;
	std::string type;
	int axisNum;
	int cmdCycle;
	bool isGripper;

	//double speedPoint;
	//double speedJointPos;

	/**
	*@brief ���̊֐�(�֐�4)�̊֐ߊp�x�ݒ�
	* @param hjp �֐ߊp�x
	*/
	void setHandJointPosition(double hjp);
	/**
	*@brief �����̎��ʒu�ݒ�
	* @param j1 �֐ߊp�x(�֐�1)
	* @param j1 �֐ߊp�x(�֐�2)
	* @param j1 �֐ߊp�x(�֐�3)
	* @param j1 �֐ߊp�x(�֐�4)
	*/
	void setStartPos(double j1, double j2, double j3, double j4);
	/**
	*@brief �J�n
	*/
	void start();
	/**
	*@brief ���[�^�[�̊p�x���擾
	* @return ���[�^�[�̊p�x
	*/
	double* getMotorPosition();
	/**
	*@brief �ڕW�֐ߊp���x���v�Z
	* @param target_theta �ڕW�֐ߊp�x
	* @param start_theta �����֐ߊp�x
	* @param end_time ���B����
	* @param time ���݂̎���
	* @param angle ���݂̊֐ߊp�x
	* @return �ڕW�֐ߊp���x
	*/
	double calcVel(double target_theta, double start_theta, double end_time, double time, double angle);

	double MaxSpeedJoint[4], MaxSpeedCartesianTrans, MaxSpeedCartesianRot;
	double MinTime;
};



#endif