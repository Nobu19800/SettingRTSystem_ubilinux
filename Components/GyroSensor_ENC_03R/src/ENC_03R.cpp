/*!
 * @file  ENC_03R.cpp
 * @brief ENC_03R���ڏ��^���d�U���W���C�����W���[���̐���֘A�̃N���X
 *
 */

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include "ENC_03R.h"


/**
*@brief ENC_03R���ڏ��^���d�U���W���C�����W���[���̐���֘A�̃N���X�̃R���X�g���N�^
* @param response ������������MRAA_SUCCESS�A����ȊO�͎��s
* @param pin_X �A�i���O�s���ԍ�(���^���d�U���W���C�����W���[���̃s��1�Ɛڑ�)
* @param pin_Y �A�i���O�s���ԍ�(���^���d�U���W���C�����W���[���̃s��2�Ɛڑ�)
* @param r IIR�t�B���^�̌W��
*/
ENC_03R::ENC_03R(mraa_result_t &response, int pin_X, int pin_Y, double r) {
	m_pin_X = pin_X;
	ax = new mraa::Aio(pin_X);
	if (ax == NULL) {
        	response = MRAA_ERROR_UNSPECIFIED;
		return;
    	}
	m_pin_Y = pin_Y;
	ay = new mraa::Aio(pin_Y);
	if (ay == NULL) {
        	response = MRAA_ERROR_UNSPECIFIED;
		return;
    	}


	_r = r;



	reset();

	response = MRAA_SUCCESS;

	
}

/**
*@brief ENC_03R���ڏ��^���d�U���W���C�����W���[���̐���֘A�̃N���X�̃f�X�g���N�^
*/
ENC_03R::~ENC_03R() {
	
	if(ax)delete ax;
	if(ay)delete ay;

	
}

/**
*@brief �t�B���^�W���Đݒ�
* @param r �W��
*/
void ENC_03R::setCoefficient(double r)
{
	_r = r;
}

/**
*@brief ������
*/
void ENC_03R::reset()
{
	m_offsetX = 0;
	m_offsetY = 0;

	const double count = 10;
	double avx, avy;
	last_x = 0;
	last_y = 0;

	for(int i=0;i < count;i++)
	{
		getAngularVelocityData(avx,avy);
		last_x += avx/count;
		last_y += avy/count;
	}
	m_offsetX = last_x;
	m_offsetY = last_y;
}


/**
*@brief �s���ԍ��̍Đݒ�
* @param pin_X �A�i���O�s���ԍ�(���^���d�U���W���C�����W���[���̃s��1�Ɛڑ�)
* @param pin_Y �A�i���O�s���ԍ�(���^���d�U���W���C�����W���[���̃s��2�Ɛڑ�)
* @return ������MRAA_SUCCESS�A����ȊO�͎��s
*/
mraa_result_t ENC_03R::setPinNum(int pin_X, int pin_Y)
{
	if(m_pin_X != pin_X)
	{
		if(ax)
		{
			delete ax;
		}
		ax = new mraa::Aio(pin_X);
		if (ax == NULL) {
	        	return MRAA_ERROR_UNSPECIFIED;
	    	}
	}
	m_pin_X = pin_X;

	if(m_pin_Y != pin_Y)
	{
		if(ay)
		{
			delete ay;
		}
		ay = new mraa::Aio(pin_Y);
		if (ay == NULL) {
	        	return MRAA_ERROR_UNSPECIFIED;
	    	}
	}
	m_pin_Y = pin_Y;

	

	return MRAA_SUCCESS;
}

/**
*@brief �v�������p���x�擾(�I�t�Z�b�g�L��)
* @param avx �p���x(X)
* @param avy �p���x(Y)
*/
void ENC_03R::getAngularVelocityData(double &avx, double &avy) {
	float volx = ax->readFloat();
	float voly = ay->readFloat();

	//std::cout << volx << "\t" << voly << "\t" << volz << std::endl;
	avx = voltage2angularvelocity(volx,m_offsetX);
	avy = voltage2angularvelocity(voly,m_offsetY);

	
}

/**
*@brief �v�������p���x�擾
* @param avx �p���x(X)
* @param avy �p���x(Y)
*/
void ENC_03R::getAngularVelocity(double &avx, double &avy) {
	getAngularVelocityData(avx,avy);
	
	
	last_x = (1-_r)*last_x + _r*avx;
	last_y = (1-_r)*last_y + _r*avy;



}

/**
*@brief �d���l���p���x�ɕϊ�
* @param dVolt �d���l
* @param offset �I�t�Z�b�g
* @return �p���x
*/
double ENC_03R::voltage2angularvelocity(double dVolt, double offset) {
  
	const double Vol = 5.0;
	const double SENS   = 0.67/1000.0*M_PI/180;
  	double av = dVolt*Vol/SENS - offset;

	return av;
}