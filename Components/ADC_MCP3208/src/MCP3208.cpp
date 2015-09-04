/*!
 * @file  MCP3208.cpp
 * @brief AD�R���o�[�^MCP3208�̒ʐM�֘A�̃N���X
 *
 */


#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <mraa.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include "MCP3208.h"

/**
*@brief AD�R���o�[�^MCP3208�̒ʐM�֘A�̃N���X�̃R���X�g���N�^
* @param response ������������MRAA_SUCCESS�A����ȊO�͎��s
* @param spi SPI����I�u�W�F�N�g
* @param smf �Z�}�t�H����I�u�W�F�N�g
* @param cs_pin �f�W�^���s���ԍ�(MCP3208�̃`�b�v�Z���N�g�s���ɐڑ�)
*/
MCP3208::MCP3208(mraa_result_t &response, mraa::Spi *spi, i2c_smf *smf, int cs_pin) {
	_spi = spi;
	_smf = smf;

	m_cs_pin = cs_pin;
	cs = new mraa::Gpio(cs_pin);
	response = cs->dir(mraa::DIR_OUT);

	if (response != MRAA_SUCCESS) {
        	mraa::printError(response);
        	return;
    	}
	cs->write(1);
	response = MRAA_SUCCESS;
}

/**
*@brief AD�R���o�[�^MCP3208�̒ʐM�֘A�̃N���X�̃f�X�g���N�^
*/
MCP3208::~MCP3208() {
	if(cs)
	{
		cs->write(0);
		delete cs;
	}
}

/**
*@brief �s���ԍ��Đݒ�
* @param cs_pin �f�W�^���s���ԍ�(MCP3208�̃`�b�v�Z���N�g�s���ɐڑ�)
* @return ������������MRAA_SUCCESS�A����ȊO�͎��s
*/
mraa_result_t MCP3208::setPinNum(int cs_pin) {
	if(m_cs_pin != cs_pin)
	{
		if(cs)
		{
			cs->write(0);
			delete cs;
		}
		cs = new mraa::Gpio(cs_pin);
		mraa_result_t response = cs->dir(mraa::DIR_OUT);
		
		if (response != MRAA_SUCCESS) {
	        	cs = NULL;
	        	return MRAA_ERROR_UNSPECIFIED;
	    	}
	}
	m_cs_pin = cs_pin;

	return MRAA_SUCCESS;
}

/**
*@brief �d���l�擾
* @param channel �`�����l��
* @return �d���l(0�`4096)
*/
unsigned int MCP3208::getValue(int channel)
{
	uint8_t *recv;
	uint8_t data[3];
	data[0] = (channel & 0x04)? 0x07: 0x06;
	data[1] = (channel & 0x03) << 6;
	data[2] = 0;

	_smf->sem_lock();
	cs->write(0);
	recv = _spi->write(data,3);
	cs->write(1);
	_smf->sem_unlock();

	unsigned int ans = ((recv[1] & 0x0f) << 8) | recv[2];

	return ans;

}