/*!
 * @file  KXR94_2050.cpp
 * @brief 加速度センサKXR94_2050の制御関連のクラス
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

#include "KXR94_2050.h"


/**
*@brief 加速度センサKXR94_2050の制御関連のクラスのコンストラクタ
* @param response 初期化成功でMRAA_SUCCESS、それ以外は失敗
* @param pin_X アナログピン番号(KXR94_2050のピン6と接続)
* @param pin_Y アナログピン番号(KXR94_2050のピン7と接続)
* @param pin_Z アナログピン番号(KXR94_2050のピン8と接続)
* @param voltage 電源電圧値
* @param r IIRフィルタの係数
*/
KXR94_2050::KXR94_2050(mraa_result_t &response, int pin_X, int pin_Y, int pin_Z, double voltage, double r) {
	m_pin_X = pin_X;
	ax = new mraa::Aio(pin_X);
	if (ax == NULL) {
        	response = MRAA_ERROR_UNSPECIFIED;
		return;
    	}
	m_pin_Y = pin_Y;
	ay = new mraa::Aio(pin_Y);
	if (ay == NULL) {
        	response = MRAA_ERROR_UNSPECIFIED;
		return;
    	}
	m_pin_Z = pin_Z;
	az = new mraa::Aio(pin_Z);
	if (az == NULL) {
        	response = MRAA_ERROR_UNSPECIFIED;
		return;
    	}

	_r = r;
	m_voltage = voltage;

	reset();

	response = MRAA_SUCCESS;

	
}

/**
*@brief 加速度センサKXR94_2050の制御関連のクラスのデストラクタ
*/
KXR94_2050::~KXR94_2050() {
	
	if(ax)delete ax;
	if(ay)delete ay;
	if(az)delete az;
	
}

/**
*@brief フィルタ係数再設定
* @param r 係数
*/
void KXR94_2050::setCoefficient(double r)
{
	_r = r;
}

/**
*@brief 初期化
*/
void KXR94_2050::reset()
{
	const double count = 10;
	double acx, acy, acz;
	last_x = 0;
	last_y = 0;
	last_z = 0;
	for(int i=0;i < count;i++)
	{
		getAccelerationData(acx,acy,acz);
		last_x += acx/count;
		last_y += acy/count;
		last_z += acz/count;
	}
}

/**
*@brief 電源電圧値を再設定
* @param voltage 電源電圧値
*/
void KXR94_2050::setVoltage(double voltage)
{
	m_voltage = voltage;
	reset();
}

/**
*@brief ピン番号再設定
* @param pin_X アナログピン番号(KXR94_2050のピン6と接続)
* @param pin_Y アナログピン番号(KXR94_2050のピン7と接続)
* @param pin_Z アナログピン番号(KXR94_2050のピン8と接続)
* @return 初期化成功でMRAA_SUCCESS、それ以外は失敗
*/
mraa_result_t KXR94_2050::setPinNum(int pin_X, int pin_Y, int pin_Z)
{
	if(m_pin_X != pin_X)
	{
		if(ax)
		{
			delete ax;
		}
		ax = new mraa::Aio(pin_X);
		if (ax == NULL) {
	        	return MRAA_ERROR_UNSPECIFIED;
	    	}
	}
	m_pin_X = pin_X;

	if(m_pin_Y != pin_Y)
	{
		if(ay)
		{
			delete ay;
		}
		ay = new mraa::Aio(pin_Y);
		if (ay == NULL) {
	        	return MRAA_ERROR_UNSPECIFIED;
	    	}
	}
	m_pin_Y = pin_Y;

	if(m_pin_Z != pin_Z)
	{
		if(az)
		{
			delete az;
		}
		az = new mraa::Aio(pin_Z);
		if (az == NULL) {
	        	return MRAA_ERROR_UNSPECIFIED;
	    	}
	}
	m_pin_Z = pin_Z;

	return MRAA_SUCCESS;
}

/**
*@brief 計測した加速度取得
* @param acx 加速度(X)
* @param acy 加速度(Y)
* @param acz 加速度(Z)
*/
void KXR94_2050::getAccelerationData(double &acx, double &acy, double &acz) {
	float volx = ax->readFloat();
	float voly = ay->readFloat();
	float volz = az->readFloat();
	//std::cout << volx << "\t" << voly << "\t" << volz << std::endl;
	acx = voltage2acceleration(volx);
	acy = voltage2acceleration(voly);
	acz = voltage2acceleration(volz);
	
}

/**
*@brief 計測した加速度取得(オフセット有り)
* @param acx 加速度(X)
* @param acy 加速度(Y)
* @param acz 加速度(Z)
*/
void KXR94_2050::getAcceleration(double &acx, double &acy, double &acz) {
	getAccelerationData(acx,acy,acz);
	
	
	last_x = (1-_r)*last_x + _r*acx;
	last_y = (1-_r)*last_y + _r*acy;
	last_z = (1-_r)*last_z + _r*acz;


}

/**
*@brief 電圧値を加速度に変換
* @param dVolt 電圧値(0～1)
* @return 加速度
*/
double KXR94_2050::voltage2acceleration(double dVolt) {
  
	const double Vol = 5.0;
	const double g = 9.8;
	const double s = 3.3/0.66;
  	double acc = (dVolt - 0.5*(m_voltage/Vol))*s*g*(Vol/m_voltage);

	return acc;
}