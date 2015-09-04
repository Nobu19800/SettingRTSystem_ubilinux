/*!
 * @file  LSM9DS0_I2C.cpp
 * @brief 9軸センサLSM9DS0のI2C通信関連のクラス
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
*@brief 9軸センサLSM9DS0のI2C通信関連のクラスのコンストラクタ
* @param response 初期化成功でMRAA_SUCCESS、それ以外は失敗
* @param i2c I2C操作オブジェクト
* @param smf セマフォ操作オブジェクト
* @param AccaMagaddr 加速度、地磁気センサのI2Cアドレス
* @param Gyroaddr ジャイロセンサのI2Cアドレス
* @param Accscale 加速度センサのスケール
* @param Magnscale 地磁気センサのスケール
* @param GyroScale ジャイロセンサのスケール
* @param mx_offset 地磁気センサのオフセット(X)
* @param my_offset 地磁気センサのオフセット(Y)
* @param mz_offset 地磁気センサのオフセット(Z)
* @param ar 加速度へのIIRフィルタの係数
* @param mr 地磁気へのIIRフィルタの係数
* @param gr 角速度へのIIRフィルタの係数
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
*@brief 9軸センサLSM9DS0のI2C通信関連のクラスのデストラクタ
*/
LSM9DS0_I2C::~LSM9DS0_I2C() {
	//delete _smf;
}



/**
*@brief I2Cで特定レジスタに書き込む
* @param Address I2Cアドレス
* @param Register レジスタ
* @param Data 書き込むデータ
*/
void LSM9DS0_I2C::writeByte(uint8_t Address, uint8_t Register, uint8_t Data) {

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
void LSM9DS0_I2C::readByte(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data) {
	
	_smf->sem_lock();

	_i2c->address(Address);
	_i2c->writeByte(Register);
	
	
	_i2c->read(Data,Nbytes);
	
	_smf->sem_unlock();
}