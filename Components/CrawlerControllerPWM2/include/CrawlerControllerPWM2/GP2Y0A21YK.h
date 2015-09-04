/*!
 * @file  GP2Y0A21YK.h
 * @brief �����Z���TGP2Y0A21YK�̐���֘A�̃N���X
 *
 */

#ifndef GP2Y0A21YK_H
#define GP2Y0A21YK_H

#include <stdio.h>
#include <mraa.hpp>



/**
 * @class GP2Y0A21YK
*@brief �����Z���TGP2Y0A21YK�̐���֘A�̃N���X
*/
class GP2Y0A21YK
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param response ������������MRAA_SUCCESS�A����ȊO�͎��s
	* @param pin �A�i���O�s���ԍ�(GP2Y0A21YK�̒ʐM���Ɛڑ�)
	* @param r IIR�t�B���^�̌W��
	*/
	GP2Y0A21YK(mraa_result_t &response, int pin = 0, double r = 0.2);
	/**
	*@brief �f�X�g���N�^
	*/
	~GP2Y0A21YK();
	/**
	*@brief �v�����������擾
	* @return ����
	*/
	double getDistance();
	/**
	*@brief �v�����������擾(�t�B���^�����L��)
	* @return ����
	*/
	double getDistanceData();
	/**
	*@brief �d���l���狗���ɕϊ�
	* @param dVolt �d���l
	* @return ����
	*/
	double voltage2distance(double dVolt);
	/**
	*@brief �A�i���O�s���Đݒ�
	* @param pin �s���ԍ�
	* @return ������MRAA_SUCCESS�A����ȊO�͎��s
	*/
	mraa_result_t setPinNum(int pin = 0);
	/**
	*@brief �t�B���^�W���Đݒ�
	* @param r �W��
	*/
	void setCoefficient(double r = 0.2);
	
private:
	mraa::Aio* a;
	double lastDistance;
	double _r;
	int m_pin;
};





#endif