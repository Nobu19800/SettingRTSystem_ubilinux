/*!
 * @file  PCA9685.h
 * https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library/blob/master/Adafruit_PWMServoDriver.h(BSD���C�Z���X)��Intel Edison�p�ɉ���
 * @brief PWM�T�[�{�h���C�oPCA9685�̒ʐM�֘A�̃N���X
 *
 */

#ifndef PCA9685_H
#define PCA9685_H

#include <stdio.h>
#include <mraa.hpp>

#include "i2c_smf.h"


#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD


/**
 * @class PCA9685
*@brief PWM�T�[�{�h���C�oPCA9685�̒ʐM�֘A�̃N���X
*/
class PCA9685
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param i2c I2C����I�u�W�F�N�g
	* @param smf �Z�}�t�H����I�u�W�F�N�g
	* @param addr I2C�A�h���X
	*/
	PCA9685(mraa::I2c *i2c, i2c_smf *smf, uint8_t addr = 0x40);
	/**
	*@brief �f�X�g���N�^
	*/
	~PCA9685();
	/**
	*@brief �ʐM�J�n
	*/
	void begin(void);
	/**
	*@brief ������
	*/
	void reset(void);
	/**
	*@brief PWM�̎��g���ݒ�
	* @param freq ���g��
	*/
	void setPWMFreq(float freq);
	/**
	*@brief PWM�̃f���[�e�B�[��ݒ�
	* @param num �s���ԍ�
	* @param on ���d����HIGH�ɂ��邩��ݒ�(0�`4096)
	* @param off ���d����LOW�ɂ��邩��ݒ�(0�`4096)
	*/
	void setPWM(uint8_t num, uint16_t on, uint16_t off);
	/**
	*@brief 
	* @param num 
	* @param val 
	* @param invert 
	*/
	void setPin(uint8_t num, uint16_t val, bool invert=false);
	/**
	*@brief �A�h���X�Đݒ�
	* @param addr I2C�A�h���X
	*/
	void setAddr(uint8_t addr = 0x40);
	
private:
	uint8_t _i2caddr;
	//int _i2channel;



	mraa::I2c *_i2c;

	i2c_smf *_smf;
};





#endif