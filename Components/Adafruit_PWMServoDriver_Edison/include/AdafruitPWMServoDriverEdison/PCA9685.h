/*!
 * @file  PCA9685.h
 * https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library/blob/master/Adafruit_PWMServoDriver.h(BSDライセンス)をIntel Edison用に改変
 * @brief PWMサーボドライバPCA9685の通信関連のクラス
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
*@brief PWMサーボドライバPCA9685の通信関連のクラス
*/
class PCA9685
{
public:
	/**
	*@brief コンストラクタ
	* @param i2c I2C操作オブジェクト
	* @param smf セマフォ操作オブジェクト
	* @param addr I2Cアドレス
	*/
	PCA9685(mraa::I2c *i2c, i2c_smf *smf, uint8_t addr = 0x40);
	/**
	*@brief デストラクタ
	*/
	~PCA9685();
	/**
	*@brief 通信開始
	*/
	void begin(void);
	/**
	*@brief 初期化
	*/
	void reset(void);
	/**
	*@brief PWMの周波数設定
	* @param freq 周波数
	*/
	void setPWMFreq(float freq);
	/**
	*@brief PWMのデューティー比設定
	* @param num ピン番号
	* @param on いつ電圧をHIGHにするかを設定(0～4096)
	* @param off いつ電圧をLOWにするかを設定(0～4096)
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
	*@brief アドレス再設定
	* @param addr I2Cアドレス
	*/
	void setAddr(uint8_t addr = 0x40);
	
private:
	uint8_t _i2caddr;
	//int _i2channel;



	mraa::I2c *_i2c;

	i2c_smf *_smf;
};





#endif