/*!
 * @file  MCP3002.h
 * @brief AD�R���o�[�^MCP3002�̒ʐM�֘A�̃N���X
 *
 */

#ifndef MCP3002_H
#define MCP3002_H

#include <stdio.h>
#include <mraa.hpp>


#include "i2c_smf.h"


 
/**
 * @class MCP3002
*@brief AD�R���o�[�^MCP3208�̒ʐM�֘A�̃N���X
*/
class MCP3002
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param response ������������MRAA_SUCCESS�A����ȊO�͎��s
	* @param spi SPI����I�u�W�F�N�g
	* @param smf �Z�}�t�H����I�u�W�F�N�g
	* @param cs_pin �f�W�^���s���ԍ�(MCP3002�̃`�b�v�Z���N�g�s���ɐڑ�)
	*/
	MCP3002(mraa_result_t &response, mraa::Spi *spi, i2c_smf *smf, int cs_pin=4);
	/**
	*@brief �f�X�g���N�^
	*/
	~MCP3002();
	/**
	*@brief �s���ԍ��Đݒ�
	* @param cs_pin �f�W�^���s���ԍ�(MCP3002�̃`�b�v�Z���N�g�s���ɐڑ�)
	* @return ������������MRAA_SUCCESS�A����ȊO�͎��s
	*/
	mraa_result_t setPinNum(int pin=4);
	/**
	*@brief �d���l�擾
	* @param channel �`�����l��
	* @return �d���l(0�`1024)
	*/
	unsigned int getValue(int channel);
private:
	
	mraa::Spi *_spi;
	mraa::Gpio* cs;
	int m_cs_pin;

	i2c_smf *_smf;
};





#endif