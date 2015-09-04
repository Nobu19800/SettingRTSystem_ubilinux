/*!
 * @file  TA8428K.h
 * @brief ���[�^�[�h���C�oTA8428K�̐���֘A�̃N���X
 *
 */

#ifndef TA8428K_H
#define TA8428K_H

#include <stdio.h>
#include <mraa.hpp>



/**
 * @class TA8428K
*@brief ���[�^�[�h���C�oTA8428K�̐���֘A�̃N���X
*/
class TA8428K
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param response ������������MRAA_SUCCESS�A����ȊO�͎��s
	* @param pwm_pin0 PWM�s���̔ԍ�(TA8428K��IN1�ɐڑ�)
	* @param pwm_pin1 PWM�s���̔ԍ�(TA8428K��IN2�ɐڑ�)
	*/
	TA8428K(mraa_result_t &response, int pwm_pin0 = 3, int pwm_pin1 = 5);
	/**
	*@brief �f�X�g���N�^
	*/
	~TA8428K();
	/**
	*@brief TA8428K�̏o�͂̃f���[�e�B�[���ݒ�
	* @param vol �f���[�e�B�[��
	*/
	void setValue(double vol);
	/**
	*@brief PWM�s���̔ԍ��̍Đݒ�
	* @param pwm_pin0 PWM�s���̔ԍ�(TA8428K��IN1�ɐڑ�)
	* @param pwm_pin1 PWM�s���̔ԍ�(TA8428K��IN2�ɐڑ�)
	* @return ������������MRAA_SUCCESS�A����ȊO�͎��s
	*/
	mraa_result_t setPinNum(int pwm_pin0 = 3, int pwm_pin1 = 5);
private:
	mraa::Pwm* pwm0;
	mraa::Pwm* pwm1;
	int m_pin0;
	int m_pin1;
};





#endif