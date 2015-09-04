/*!
 * @file  TA7291P.h
 * @brief ���[�^�[�h���C�oTA7291P�̐���֘A�̃N���X
 *
 */

#ifndef TA7291P_H
#define TA7291P_H

#include <stdio.h>
#include <mraa.hpp>



/**
 * @class TA7291P
*@brief ���[�^�[�h���C�oTA7291P�̐���֘A�̃N���X
*/
class TA7291P
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param response ������������MRAA_SUCCESS�A����ȊO�͎��s
	* @param pwm_pin PWM�s���ԍ�(TA7291P��Vref�ɐڑ�)
	* @param in0_pin �f�W�^���s���ԍ�(TA7291P��IN1�ɐڑ�)
	* @param in1_pin �f�W�^���s���ԍ�(TA7291P��IN2�ɐڑ�)
	*/
	TA7291P(mraa_result_t &response, int pwm_pin = 3, int in0_pin = 2, int in1_pin = 4);
	/**
	*@brief �f�X�g���N�^
	*/
	~TA7291P();
	/**
	*@brief TA7291P�̏o�͂̃f���[�e�B�[���ݒ�
	* @param vol �f���[�e�B�[��
	*/
	void setValue(double vol);
	/**
	*@brief �s���̔ԍ��̍Đݒ�
	* @param pwm_pin PWM�s���ԍ�(TA7291P��Vref�ɐڑ�)
	* @param in0_pin �f�W�^���s���ԍ�(TA7291P��IN1�ɐڑ�)
	* @param in1_pin �f�W�^���s���ԍ�(TA7291P��IN2�ɐڑ�)
	* @return ������������MRAA_SUCCESS�A����ȊO�͎��s
	*/
	mraa_result_t setPinNum(int pwm_pin = 3, int in0_pin = 2, int in1_pin = 4);
	
private:
	mraa::Pwm* pwm;
	mraa::Gpio* in0;
	mraa::Gpio* in1;
	int m_pwm_pin;
	int m_in0_pin;
	int m_in1_pin;
};





#endif