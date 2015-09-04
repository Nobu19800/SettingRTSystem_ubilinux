/*!
 * @file  PCA9685.cpp
 * https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library/blob/master/Adafruit_PWMServoDriver.cpp(BSD���C�Z���X)��Intel Edison�p�ɉ���
 * @brief PWM�T�[�{�h���C�oPCA9685�̒ʐM�֘A�̃N���X
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <mraa.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include "PCA9685.h"


/**
*@brief PWM�T�[�{�h���C�oPCA9685�̒ʐM�֘A�̃N���X�̃R���X�g���N�^
* @param i2c I2C����I�u�W�F�N�g
* @param smf �Z�}�t�H����I�u�W�F�N�g
* @param addr I2C�A�h���X
*/
PCA9685::PCA9685(mraa::I2c *i2c, i2c_smf *smf, uint8_t addr) {
	_i2c = i2c;
	_i2caddr = addr;
	_smf = smf;
	
	//_smf = new i2c_smf();
}


/**
*@brief PWM�T�[�{�h���C�oPCA9685�̒ʐM�֘A�̃N���X�̃f�X�g���N�^
* @param i2c I2C����I�u�W�F�N�g
* @param smf �Z�}�t�H����I�u�W�F�N�g
* @param addr I2C�A�h���X
*/
PCA9685::~PCA9685() {
	//delete _smf;
}

/**
*@brief �A�h���X�Đݒ�
* @param addr I2C�A�h���X
*/
void PCA9685::setAddr(uint8_t addr)
{
	if(_i2caddr != addr)
	{
		reset();
	}
	_i2caddr = addr;
}

/**
*@brief �ʐM�J�n
*/
void PCA9685::begin(void) {
	
	
	reset();
}

/**
*@brief ������
*/
void PCA9685::reset(void) {
	_smf->sem_lock();
	_i2c->address(_i2caddr);
	_i2c->writeReg(PCA9685_MODE1, 0x0);
	_smf->sem_unlock();
}

/**
*@brief PWM�̎��g���ݒ�
* @param freq ���g��
*/
void PCA9685::setPWMFreq(float freq) {
  
  freq *= 0.9;
  float prescaleval = 25000000;
  prescaleval /= 4096;
  prescaleval /= freq;
  prescaleval -= 1;

  uint8_t prescale = floor(prescaleval + 0.5);
  
  _smf->sem_lock();
  _i2c->address(_i2caddr);
  uint8_t oldmode = _i2c->readReg(PCA9685_MODE1);
  uint8_t newmode = (oldmode&0x7F) | 0x10;

  
  _i2c->writeReg(PCA9685_MODE1, newmode);
  _i2c->writeReg(PCA9685_PRESCALE, prescale);
  _i2c->writeReg(PCA9685_MODE1, oldmode);
  usleep(5000);
  _i2c->writeReg(PCA9685_MODE1, oldmode | 0xa1);
  _smf->sem_unlock();
}

/**
*@brief PWM�̃f���[�e�B�[��ݒ�
* @param num �s���ԍ�
* @param on ���d����HIGH�ɂ��邩��ݒ�(0�`4096)
* @param off ���d����LOW�ɂ��邩��ݒ�(0�`4096)
*/
void PCA9685::setPWM(uint8_t num, uint16_t on, uint16_t off) {
  
 	uint8_t data[5];
	data[0] = LED0_ON_L+4*num;
	data[1] = on;
	data[2] = on>>8;
	data[3] = off;
	data[4] = off>>8;
	_smf->sem_lock();
	_i2c->address(_i2caddr);
	_i2c->write(data,5);
 	_smf->sem_unlock();
}

/**
*@brief 
* @param num 
* @param val 
* @param invert 
*/
void PCA9685::setPin(uint8_t num, uint16_t val, bool invert)
{
  
  val = (uint8_t)std::min((int)val, 4095);
  if (invert) {
    if (val == 0) {
      
      setPWM(num, 4096, 0);
    }
    else if (val == 4095) {
      
      setPWM(num, 0, 4096);
    }
    else {
      setPWM(num, 0, 4095-val);
    }
  }
  else {
    if (val == 4095) {
      
      setPWM(num, 4096, 0);
    }
    else if (val == 0) {
      
      setPWM(num, 0, 4096);
    }
    else {
      setPWM(num, 0, val);
    }
  }
}


