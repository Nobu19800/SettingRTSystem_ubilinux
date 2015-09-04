/*!
 * @file  KXR94_2050.cpp
 * @brief �����x�Z���TKXR94_2050�̐���֘A�̃N���X
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

#include "KXR94_2050.h"


/**
*@brief �����x�Z���TKXR94_2050�̐���֘A�̃N���X�̃R���X�g���N�^
* @param response ������������MRAA_SUCCESS�A����ȊO�͎��s
* @param pin_X �A�i���O�s���ԍ�(KXR94_2050�̃s��6�Ɛڑ�)
* @param pin_Y �A�i���O�s���ԍ�(KXR94_2050�̃s��7�Ɛڑ�)
* @param pin_Z �A�i���O�s���ԍ�(KXR94_2050�̃s��8�Ɛڑ�)
* @param voltage �d���d���l
* @param r IIR�t�B���^�̌W��
*/
KXR94_2050::KXR94_2050(mraa_result_t &response, int pin_X, int pin_Y, int pin_Z, double voltage, double r) {
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
	m_pin_Z = pin_Z;
	az = new mraa::Aio(pin_Z);
	if (az == NULL) {
        	response = MRAA_ERROR_UNSPECIFIED;
		return;
    	}

	_r = r;
	m_voltage = voltage;

	reset();

	response = MRAA_SUCCESS;

	
}

/**
*@brief �����x�Z���TKXR94_2050�̐���֘A�̃N���X�̃f�X�g���N�^
*/
KXR94_2050::~KXR94_2050() {
	
	if(ax)delete ax;
	if(ay)delete ay;
	if(az)delete az;
	
}

/**
*@brief �t�B���^�W���Đݒ�
* @param r �W��
*/
void KXR94_2050::setCoefficient(double r)
{
	_r = r;
}

/**
*@brief ������
*/
void KXR94_2050::reset()
{
	const double count = 10;
	double acx, acy, acz;
	last_x = 0;
	last_y = 0;
	last_z = 0;
	for(int i=0;i < count;i++)
	{
		getAccelerationData(acx,acy,acz);
		last_x += acx/count;
		last_y += acy/count;
		last_z += acz/count;
	}
}

/**
*@brief �d���d���l���Đݒ�
* @param voltage �d���d���l
*/
void KXR94_2050::setVoltage(double voltage)
{
	m_voltage = voltage;
	reset();
}

/**
*@brief �s���ԍ��Đݒ�
* @param pin_X �A�i���O�s���ԍ�(KXR94_2050�̃s��6�Ɛڑ�)
* @param pin_Y �A�i���O�s���ԍ�(KXR94_2050�̃s��7�Ɛڑ�)
* @param pin_Z �A�i���O�s���ԍ�(KXR94_2050�̃s��8�Ɛڑ�)
* @return ������������MRAA_SUCCESS�A����ȊO�͎��s
*/
mraa_result_t KXR94_2050::setPinNum(int pin_X, int pin_Y, int pin_Z)
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

	if(m_pin_Z != pin_Z)
	{
		if(az)
		{
			delete az;
		}
		az = new mraa::Aio(pin_Z);
		if (az == NULL) {
	        	return MRAA_ERROR_UNSPECIFIED;
	    	}
	}
	m_pin_Z = pin_Z;

	return MRAA_SUCCESS;
}

/**
*@brief �v�����������x�擾
* @param acx �����x(X)
* @param acy �����x(Y)
* @param acz �����x(Z)
*/
void KXR94_2050::getAccelerationData(double &acx, double &acy, double &acz) {
	float volx = ax->readFloat();
	float voly = ay->readFloat();
	float volz = az->readFloat();
	//std::cout << volx << "\t" << voly << "\t" << volz << std::endl;
	acx = voltage2acceleration(volx);
	acy = voltage2acceleration(voly);
	acz = voltage2acceleration(volz);
	
}

/**
*@brief �v�����������x�擾(�I�t�Z�b�g�L��)
* @param acx �����x(X)
* @param acy �����x(Y)
* @param acz �����x(Z)
*/
void KXR94_2050::getAcceleration(double &acx, double &acy, double &acz) {
	getAccelerationData(acx,acy,acz);
	
	
	last_x = (1-_r)*last_x + _r*acx;
	last_y = (1-_r)*last_y + _r*acy;
	last_z = (1-_r)*last_z + _r*acz;


}

/**
*@brief �d���l�������x�ɕϊ�
* @param dVolt �d���l(0�`1)
* @return �����x
*/
double KXR94_2050::voltage2acceleration(double dVolt) {
  
	const double Vol = 5.0;
	const double g = 9.8;
	const double s = 3.3/0.66;
  	double acc = (dVolt - 0.5*(m_voltage/Vol))*s*g*(Vol/m_voltage);

	return acc;
}