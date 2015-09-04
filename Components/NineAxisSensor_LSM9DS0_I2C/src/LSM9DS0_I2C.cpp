/*!
 * @file  LSM9DS0_I2C.cpp
 * @brief 9���Z���TLSM9DS0��I2C�ʐM�֘A�̃N���X
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
#include "LSM9DS0_I2C.h"



/**
*@brief 9���Z���TLSM9DS0��I2C�ʐM�֘A�̃N���X�̃R���X�g���N�^
* @param response ������������MRAA_SUCCESS�A����ȊO�͎��s
* @param i2c I2C����I�u�W�F�N�g
* @param smf �Z�}�t�H����I�u�W�F�N�g
* @param AccaMagaddr �����x�A�n���C�Z���T��I2C�A�h���X
* @param Gyroaddr �W���C���Z���T��I2C�A�h���X
* @param Accscale �����x�Z���T�̃X�P�[��
* @param Magnscale �n���C�Z���T�̃X�P�[��
* @param GyroScale �W���C���Z���T�̃X�P�[��
* @param mx_offset �n���C�Z���T�̃I�t�Z�b�g(X)
* @param my_offset �n���C�Z���T�̃I�t�Z�b�g(Y)
* @param mz_offset �n���C�Z���T�̃I�t�Z�b�g(Z)
* @param ar �����x�ւ�IIR�t�B���^�̌W��
* @param mr �n���C�ւ�IIR�t�B���^�̌W��
* @param gr �p���x�ւ�IIR�t�B���^�̌W��
*/
LSM9DS0_I2C::LSM9DS0_I2C(mraa_result_t &response, mraa::I2c *i2c, i2c_smf *smf, uint8_t AccaMagaddr, uint8_t Gyroaddr, uint8_t Accscale, uint8_t Magnscale, uint8_t GyroScale, int mx_offset, int my_offset, int mz_offset, double ar, double mr, double gr) :
LSM9DS0(smf,AccaMagaddr,Gyroaddr,Accscale,Magnscale,GyroScale,mx_offset,my_offset,mz_offset,ar,mr,gr)
{
	_i2c = i2c;
	




	if(!AccMagSensor_Exist())
	{
		response = MRAA_ERROR_UNSPECIFIED;
		return;
	}
	if(!GyroSensor_Exist())
	{
		response = MRAA_ERROR_UNSPECIFIED;
		return;
	}

	reset();

	response = MRAA_SUCCESS;
}

/**
*@brief 9���Z���TLSM9DS0��I2C�ʐM�֘A�̃N���X�̃f�X�g���N�^
*/
LSM9DS0_I2C::~LSM9DS0_I2C() {
	//delete _smf;
}



/**
*@brief I2C�œ��背�W�X�^�ɏ�������
* @param Address I2C�A�h���X
* @param Register ���W�X�^
* @param Data �������ރf�[�^
*/
void LSM9DS0_I2C::writeByte(uint8_t Address, uint8_t Register, uint8_t Data) {

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
void LSM9DS0_I2C::readByte(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data) {
	
	_smf->sem_lock();

	_i2c->address(Address);
	_i2c->writeByte(Register);
	
	
	_i2c->read(Data,Nbytes);
	
	_smf->sem_unlock();
}