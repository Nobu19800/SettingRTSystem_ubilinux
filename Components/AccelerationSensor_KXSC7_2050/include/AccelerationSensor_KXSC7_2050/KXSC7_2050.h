/*!
 * @file  GP2Y0A21YK.h
 * @brief �����x�Z���TKXSC7_2050�̐���֘A�̃N���X
 *
 */

#ifndef KXSC7_2050_H
#define KXSC7_2050_H

#include <stdio.h>
#include <mraa.hpp>



/**
 * @class KXSC7_2050
*@brief �����x�Z���TKXSC7_2050�̐���֘A�̃N���X
*/
class KXSC7_2050
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param response ������������MRAA_SUCCESS�A����ȊO�͎��s
	* @param pin_X �A�i���O�s���ԍ�(KXSC7_2050�̃s��5�Ɛڑ�)
	* @param pin_Y �A�i���O�s���ԍ�(KXSC7_2050�̃s��6�Ɛڑ�)
	* @param pin_Z �A�i���O�s���ԍ�(KXSC7_2050�̃s��7�Ɛڑ�)
	* @param voltage �d���d���l
	* @param r IIR�t�B���^�̌W��
	*/
	KXSC7_2050(mraa_result_t &response, int pin_X = 0, int pin_Y = 1, int pin_Z = 2, double voltage = 3.3, double r = 0.2);
	/**
	*@brief �f�X�g���N�^
	*/
	~KXSC7_2050();
	/**
	*@brief �s���ԍ��Đݒ�
	* @param pin_X �A�i���O�s���ԍ�(KXSC7_2050�̃s��5�Ɛڑ�)
	* @param pin_Y �A�i���O�s���ԍ�(KXSC7_2050�̃s��6�Ɛڑ�)
	* @param pin_Z �A�i���O�s���ԍ�(KXSC7_2050�̃s��7�Ɛڑ�)
	* @return ������������MRAA_SUCCESS�A����ȊO�͎��s
	*/
	mraa_result_t setPinNum(int pin_X = 0, int pin_Y = 1, int pin_Z = 2);
	/**
	*@brief �t�B���^�W���Đݒ�
	* @param r �W��
	*/
	void setCoefficient(double r = 0.2);
	/**
	*@brief �v�����������x�擾(�I�t�Z�b�g�L��)
	* @param acx �����x(X)
	* @param acy �����x(Y)
	* @param acz �����x(Z)
	*/
	void getAcceleration(double &acx, double &acy, double &acz);
	/**
	*@brief �v�����������x�擾
	* @param acx �����x(X)
	* @param acy �����x(Y)
	* @param acz �����x(Z)
	*/
	void getAccelerationData(double &acx, double &acy, double &acz);
	/**
	*@brief �d���l�������x�ɕϊ�
	* @param dVolt �d���l(0�`1)
	* @return �����x
	*/
	double voltage2acceleration(double dVolt);
	/**
	*@brief �d���d���l���Đݒ�
	* @param voltage �d���d���l
	*/
	void setVoltage(double voltage = 3.3);
	/**
	*@brief ������
	*/
	void reset();
	
private:
	mraa::Aio* ax;
	mraa::Aio* ay;
	mraa::Aio* az;


	double _r;

	double last_x, last_y, last_z;
	
	int m_pin_X, m_pin_Y, m_pin_Z;
	double m_voltage;

};





#endif