/*!
 * @file  ENC_03R.h
 * @brief ENC_03R���ڏ��^���d�U���W���C�����W���[���̐���֘A�̃N���X
 *
 */

#ifndef ENC_03R_H
#define ENC_03R_H

#include <stdio.h>
#include <mraa.hpp>



/**
 * @class ENC_03R
*@brief ENC_03R���ڏ��^���d�U���W���C�����W���[���̐���֘A�̃N���X
*/
class ENC_03R
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param response ������������MRAA_SUCCESS�A����ȊO�͎��s
	* @param pin_X �A�i���O�s���ԍ�(���^���d�U���W���C�����W���[���̃s��1�Ɛڑ�)
	* @param pin_Y �A�i���O�s���ԍ�(���^���d�U���W���C�����W���[���̃s��2�Ɛڑ�)
	* @param r IIR�t�B���^�̌W��
	*/
	ENC_03R(mraa_result_t &response, int pin_X = 0, int pin_Y = 1, double r = 0.2);
	/**
	*@brief �f�X�g���N�^
	*/
	~ENC_03R();
	/**
	*@brief �s���ԍ��̍Đݒ�
	* @param pin_X �A�i���O�s���ԍ�(���^���d�U���W���C�����W���[���̃s��1�Ɛڑ�)
	* @param pin_Y �A�i���O�s���ԍ�(���^���d�U���W���C�����W���[���̃s��2�Ɛڑ�)
	* @return ������MRAA_SUCCESS�A����ȊO�͎��s
	*/
	mraa_result_t setPinNum(int pin_X = 0, int pin_Y = 1);
	/**
	*@brief �t�B���^�W���Đݒ�
	* @param r �W��
	*/
	void setCoefficient(double r);
	/**
	*@brief �v�������p���x�擾(�I�t�Z�b�g�L��)
	* @param avx �p���x(X)
	* @param avy �p���x(Y)
	*/
	void getAngularVelocity(double &avx, double &avy);
	/**
	*@brief �v�������p���x�擾
	* @param avx �p���x(X)
	* @param avy �p���x(Y)
	*/
	void getAngularVelocityData(double &avx, double &avy);
	/**
	*@brief �d���l���p���x�ɕϊ�
	* @param dVolt �d���l
	* @param offset �I�t�Z�b�g
	* @return �p���x
	*/
	double voltage2angularvelocity(double dVolt, double offset);
	/**
	*@brief ������
	*/
	void reset();
	
private:
	mraa::Aio* ax;
	mraa::Aio* ay;


	double _r;

	double last_x, last_y;
	
	int m_pin_X, m_pin_Y;
	double m_offsetX, m_offsetY;

};





#endif