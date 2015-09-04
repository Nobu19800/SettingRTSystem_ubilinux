/*!
 * @file  L3GD20_I2C.cpp
 * @brief ジャイロセンサL3GD20のI2C通信関連のクラス
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
*@brief ジャイロセンサL3GD20のI2C通信関連のクラスのコンストラクタ
* @param response 初期化成功でMRAA_SUCCESS、それ以外は失敗
* @param i2c I2C操作オブジェクト
* @param smf セマフォ操作オブジェクト
* @param addr I2Cアドレス
* @param scale スケール
* @param r IIRフィルタの係数
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
*@brief ジャイロセンサL3GD20のI2C通信関連のクラスのデストラクタ
*/
L3GD20_I2C::~L3GD20_I2C() {
	//delete _smf;
}

/**
*@brief I2Cで特定レジスタに書き込む
* @param Address I2Cアドレス
* @param Register レジスタ
* @param Data 書き込むデータ
*/
void L3GD20_I2C::writeByte(uint8_t Address, uint8_t Register, uint8_t Data) {

	_smf->sem_lock();
	_i2c->address(Address);
	
	_i2c->writeReg(Register, Data);
	
	_smf->sem_unlock();

  	
}

/**
*@brief I2Cで特定レジスタに書き込んで値を読み込む
* @param Address I2Cアドレス
* @param Register レジスタ
* @param Nbytes 読み込むデータの長さ
* @param Data 読み込んだデータ
*/
void L3GD20_I2C::readByte(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data) {
	
	_smf->sem_lock();

	_i2c->address(Address);
	_i2c->writeByte(Register);

	
	_i2c->read(Data,Nbytes);
	
	_smf->sem_unlock();
}