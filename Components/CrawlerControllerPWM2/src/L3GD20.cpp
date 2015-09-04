/*!
 * @file  L3GD20.cpp
 * @brief ジャイロセンサL3GD20の通信関連のクラス
 *
 */

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <mraa.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include "L3GD20.h"

#define L3GD20_WHO_ID  0xD4


/**
*@brief ジャイロセンサL3GD20の通信関連のクラスのコンストラクタ
* @param smf セマフォ操作オブジェクト
* @param addr アドレス(SPI通信の場合はデフォルトのI2Cアドレスを指定しておく)
* @param scale スケール
* @param r IIRフィルタの係数
*/
L3GD20::L3GD20(i2c_smf *smf, uint8_t addr, uint8_t scale, double r) {

	_r = r;
	
	_scale = scale;
	
	_addr = addr;
	

	_smf = smf;

}

/**
*@brief ジャイロセンサL3GD20の通信関連のクラスのデストラクタ
*/
L3GD20::~L3GD20() {
	//delete _smf;
}

/**
*@brief センサの存在確認
* @return 存在する場合true、存在しない場合false
*/
bool L3GD20::sensor_Exist() {
	uint8_t Buf[2];
	readByte(_addr,WHO_AM_I,1,Buf);

	//std::cout << (int)Buf[0] << "\t" << (int)L3GD20_WHO_ID << std::endl;
	if(Buf[0] != L3GD20_WHO_ID)return false;
	
	return true;
}

/**
*@brief アドレス再設定
* @param addr I2Cアドレス
* @return 成功でMRAA_SUCCESS、それ以外は失敗
*/
mraa_result_t L3GD20::setAddr(uint8_t addr)
{
	if(_addr != addr)
	{
		_addr = addr;
		if(!sensor_Exist())return MRAA_ERROR_UNSPECIFIED;
		reset();
	}
	return MRAA_SUCCESS;
}

/**
*@brief センサスケール再設定
* @param scale スケール
*/
void L3GD20::setScale(uint8_t scale)
{
	if(_scale != scale)
	{
		_scale = scale;
		reset();
	}
}

/**
*@brief フィルタ係数再設定
* @param r 係数
*/
void L3GD20::setCoefficient(double r)
{
	_r = r;
}

/**
*@brief スケールを反映
* @param scale スケール
*/
void L3GD20::setRange(uint8_t scale)
{
	_scale = scale;
	writeByte(_addr, CTRL_REG4, _scale);
	
	
}



/**
*@brief 初期化
*/
void L3GD20::reset(void) {
	
	
	
	writeByte(_addr,CTRL_REG1,0x0f);

	


	
	setRange(_scale);
	

  	
  	
  	
 
  	
  	

	const double count = 10;
	double avx,avy,avz;
	lastX = 0;
	lastY = 0;
	lastZ = 0;
	
	for(int i=0;i < count;i++)
	{
		getGyroData(avx,avy,avz);

		lastX += avx/count;
		lastY += avy/count;
		lastZ += avz/count;
		usleep(10000);
	}


	

	

	
}


/**
*@brief 計測した角速度取得(オフセット有り)
* @param avx 角速度(X)
* @param avy 角速度(Y)
* @param avz 角速度(Z)
*/
void L3GD20::getGyro(double &avx, double &avy, double &avz)
{
	getGyroData(avx,avy,avz);

	lastX = _r*avx + (1-_r)*lastX;
	lastY = _r*avy + (1-_r)*lastY;
	lastZ = _r*avz + (1-_r)*lastZ;
	

}


/**
*@brief 計測した角速度取得
* @param avx 角速度(X)
* @param avy 角速度(Y)
* @param avz 角速度(Z)
*/
void L3GD20::getGyroData(double &avx, double &avy, double &avz) {



	
	uint8_t x_hi, x_lo, y_hi, y_lo, z_hi, z_lo;

	uint8_t Buf[2];
	readByte(_addr,OUT_X_H,1,Buf);
	x_hi = Buf[0];

	readByte(_addr,OUT_X_L,1,Buf);
	x_lo = Buf[0];

	readByte(_addr,OUT_Y_H,1,Buf);
	y_hi = Buf[0];

	readByte(_addr,OUT_Y_L,1,Buf);
	y_lo = Buf[0];

	readByte(_addr,OUT_Z_H,1,Buf);
	z_hi = Buf[0];

	readByte(_addr,OUT_Z_L,1,Buf);
	z_lo = Buf[0];

	short GyroRaw_x = x_hi;
	GyroRaw_x = (GyroRaw_x << 8) | x_lo;
	short GyroRaw_y = y_hi;
	GyroRaw_y = (GyroRaw_y << 8) | y_lo;
	short GyroRaw_z = z_hi;
	GyroRaw_z = (GyroRaw_z << 8) | z_lo;





	double gRes;
	if(_scale == Range_250dps)
		gRes = 2*0.00875*M_PI/180;
	else if(_scale == Range_500dps)
		gRes = 2*0.0175*M_PI/180;
	else
		gRes = 2*0.07*M_PI/180;

	avx = (double)GyroRaw_x * gRes;
	avy = (double)GyroRaw_y * gRes;
	avz = (double)GyroRaw_z * gRes;

	
	
}

/**
*@brief 特定レジスタに書き込んで値を読み込む
* @param Address I2Cアドレス(SPI通信の場合はセンサの判別に利用するのでアドレスのデフォルト値を入力)
* @param Register レジスタ
* @param Nbytes 読み込むデータの長さ
* @param Data 読み込んだデータ
*/
void L3GD20::readByte(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{

}

/**
*@brief 特定レジスタに書き込む
* @param Address I2Cアドレス(SPI通信の場合はセンサの判別に利用するのでアドレスのデフォルト値を入力)
* @param Register レジスタ
* @param Data 書き込むデータ
*/
void L3GD20::writeByte(uint8_t Address, uint8_t Register, uint8_t Data)
{

}