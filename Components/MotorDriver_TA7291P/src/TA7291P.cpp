/*!
 * @file  TA7291P.cpp
 * @brief モータードライバTA7291Pの制御関連のクラス
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "TA7291P.h"


/**
*@brief モータードライバTA7291Pの制御関連のクラスのコンストラクタ
* @param response 初期化成功でMRAA_SUCCESS、それ以外は失敗
* @param pwm_pin PWMピン番号(TA7291PのVrefに接続)
* @param in0_pin デジタルピン番号(TA7291PのIN1に接続)
* @param in1_pin デジタルピン番号(TA7291PのIN2に接続)
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
*@brief モータードライバTA7291Pの制御関連のクラスのデストラクタ
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
*@brief ピンの番号の再設定
* @param pwm_pin PWMピン番号(TA7291PのVrefに接続)
* @param in0_pin デジタルピン番号(TA7291PのIN1に接続)
* @param in1_pin デジタルピン番号(TA7291PのIN2に接続)
* @return 初期化成功でMRAA_SUCCESS、それ以外は失敗
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
*@brief TA7291Pの出力のデューティー比を設定
* @param vol デューティー比
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
