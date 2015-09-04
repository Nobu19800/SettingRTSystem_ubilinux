/*!
 * @file  TA7291P.cpp
 * @brief ���[�^�[�h���C�oTA7291P�̐���֘A�̃N���X
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "TA7291P.h"


/**
*@brief ���[�^�[�h���C�oTA7291P�̐���֘A�̃N���X�̃R���X�g���N�^
* @param response ������������MRAA_SUCCESS�A����ȊO�͎��s
* @param pwm_pin PWM�s���ԍ�(TA7291P��Vref�ɐڑ�)
* @param in0_pin �f�W�^���s���ԍ�(TA7291P��IN1�ɐڑ�)
* @param in1_pin �f�W�^���s���ԍ�(TA7291P��IN2�ɐڑ�)
*/
TA7291P::TA7291P(mraa_result_t &response, int pwm_pin, int in0_pin, int in1_pin) {
	
	m_pwm_pin = pwm_pin;
	pwm = new mraa::Pwm(pwm_pin);
	if (pwm == NULL) {
        	response = MRAA_ERROR_UNSPECIFIED;
		return;
    	}
	pwm->enable(true);

	m_in0_pin = in0_pin;
	in0 = new mraa::Gpio(in0_pin);
	response = in0->dir(mraa::DIR_OUT);
	
	if (response != MRAA_SUCCESS) {
        	mraa::printError(response);
        	return;
    	}

	m_in1_pin = in1_pin;
	in1 = new mraa::Gpio(in1_pin);
	response = in1->dir(mraa::DIR_OUT);

	if (response != MRAA_SUCCESS) {
        	mraa::printError(response);
        	return;
    	}

	response = MRAA_SUCCESS;
}

/**
*@brief ���[�^�[�h���C�oTA7291P�̐���֘A�̃N���X�̃f�X�g���N�^
*/
TA7291P::~TA7291P() {
	pwm->write(0);
	pwm->enable(false);
	delete pwm;

	in0->write(0);
	delete in0;

	in1->write(0);
	delete in1;
}

/**
*@brief �s���̔ԍ��̍Đݒ�
* @param pwm_pin PWM�s���ԍ�(TA7291P��Vref�ɐڑ�)
* @param in0_pin �f�W�^���s���ԍ�(TA7291P��IN1�ɐڑ�)
* @param in1_pin �f�W�^���s���ԍ�(TA7291P��IN2�ɐڑ�)
* @return ������������MRAA_SUCCESS�A����ȊO�͎��s
*/
mraa_result_t TA7291P::setPinNum(int pwm_pin, int in0_pin, int in1_pin)
{
	if(m_pwm_pin != pwm_pin)
	{
		if(pwm)
		{
			pwm->write(0);
			pwm->enable(false);
			delete pwm;
		}
		pwm = new mraa::Pwm(pwm_pin);
		if (pwm == NULL) {
	        	return MRAA_ERROR_UNSPECIFIED;
	    	}
		pwm->enable(true);
	}
	m_pwm_pin = pwm_pin;

	if(m_in0_pin != in0_pin)
	{
		if(in0)
		{
			in0->write(0);
			delete in0;
		}
		in0 = new mraa::Gpio(in0_pin);
		mraa_result_t response = in0->dir(mraa::DIR_OUT);
		
		if (response != MRAA_SUCCESS) {
	        	in0 = NULL;
	        	return MRAA_ERROR_UNSPECIFIED;
	    	}
	}
	m_in0_pin = in0_pin;



	if(m_in1_pin != in1_pin)
	{
		if(in1)
		{
			in1->write(0);
			delete in1;
		}
		in1 = new mraa::Gpio(in1_pin);
		mraa_result_t response = in1->dir(mraa::DIR_OUT);
		
		if (response != MRAA_SUCCESS) {
	        	in1 = NULL;
	        	return MRAA_ERROR_UNSPECIFIED;
	    	}
	}
	m_in1_pin = in1_pin;

	return MRAA_SUCCESS;
}

/**
*@brief TA7291P�̏o�͂̃f���[�e�B�[���ݒ�
* @param vol �f���[�e�B�[��
*/
void TA7291P::setValue(double vol) {
	if(vol < 0)
	{
		in0->write(1);
		pwm->write(-vol);
		in1->write(0);
	}
	else
	{
		in0->write(0);
		pwm->write(vol);
		in1->write(1);
	}
}
