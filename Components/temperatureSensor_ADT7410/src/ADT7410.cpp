#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <mraa.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include "ADT7410.h"


/**
*@brief ���x�Z���TADT7410�̒ʐM�֘A�̃N���X�̃R���X�g���N�^
* @param i2c I2C����I�u�W�F�N�g
* @param smf �Z�}�t�H����I�u�W�F�N�g
* @param addr I2C�A�h���X
*/
ADT7410::ADT7410(mraa::I2c *i2c, i2c_smf *smf, uint8_t addr) {
	_i2c = i2c;

	
	
	
	_addr = addr;
	

	_smf = smf;

}


/**
*@brief ���x�Z���TADT7410�̒ʐM�֘A�̃N���X�̃f�X�g���N�^
*/
ADT7410::~ADT7410() {
	//delete _smf;
}

/**
*@brief �A�h���X�Đݒ�
* @param addr I2C�A�h���X
*/
void ADT7410::setAddr(uint8_t addr)
{
	_addr = addr;
}

/**
*@brief ���x�擾
* @return ���x
*/
float ADT7410::getTempData() {


	_smf->sem_lock();


	_i2c->address(_addr);
	uint8_t v[2];
	v[0] = 0;
	v[1] = 0;
	_i2c->read(v, 2);
	uint16_t val = (uint16_t)v[0] << 8;
	val |= v[1];
	val >>= 3;
	int ival = (int)val;
	if(val & (0x8000 >> 3)) { 
		ival = ival  - 8192; 
	}

	float tmp = (float)ival / 16.0;
	

	_smf->sem_unlock();
	
	return tmp;
}



