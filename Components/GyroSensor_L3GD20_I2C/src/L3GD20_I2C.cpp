/*!
 * @file  L3GD20_I2C.cpp
 * @brief �W���C���Z���TL3GD20��I2C�ʐM�֘A�̃N���X
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
#include "L3GD20_I2C.h"


/**
*@brief �W���C���Z���TL3GD20��I2C�ʐM�֘A�̃N���X�̃R���X�g���N�^
* @param response ������������MRAA_SUCCESS�A����ȊO�͎��s
* @param i2c I2C����I�u�W�F�N�g
* @param smf �Z�}�t�H����I�u�W�F�N�g
* @param addr I2C�A�h���X
* @param scale �X�P�[��
* @param r IIR�t�B���^�̌W��
*/
L3GD20_I2C::L3GD20_I2C(mraa_result_t &response, mraa::I2c *i2c, i2c_smf *smf, uint8_t addr, uint8_t scale, double r) :
L3GD20(smf,addr,scale,r)
{
	_i2c = i2c;


	if(!sensor_Exist())
	{
		response = MRAA_ERROR_UNSPECIFIED;
		return;
	}

	reset();

	response = MRAA_SUCCESS;
}

/**
*@brief �W���C���Z���TL3GD20��I2C�ʐM�֘A�̃N���X�̃f�X�g���N�^
*/
L3GD20_I2C::~L3GD20_I2C() {
	//delete _smf;
}

/**
*@brief I2C�œ��背�W�X�^�ɏ�������
* @param Address I2C�A�h���X
* @param Register ���W�X�^
* @param Data �������ރf�[�^
*/
void L3GD20_I2C::writeByte(uint8_t Address, uint8_t Register, uint8_t Data) {

	_smf->sem_lock();
	_i2c->address(Address);
	
	_i2c->writeReg(Register, Data);
	
	_smf->sem_unlock();

  	
}

/**
*@brief I2C�œ��背�W�X�^�ɏ�������Œl��ǂݍ���
* @param Address I2C�A�h���X
* @param Register ���W�X�^
* @param Nbytes �ǂݍ��ރf�[�^�̒���
* @param Data �ǂݍ��񂾃f�[�^
*/
void L3GD20_I2C::readByte(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data) {
	
	_smf->sem_lock();

	_i2c->address(Address);
	_i2c->writeByte(Register);

	
	_i2c->read(Data,Nbytes);
	
	_smf->sem_unlock();
}