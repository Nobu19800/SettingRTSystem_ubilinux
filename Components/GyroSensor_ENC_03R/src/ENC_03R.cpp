/*!
 * @file  ENC_03R.cpp
 * @brief ENC_03R搭載小型圧電振動ジャイロモジュールの制御関連のクラス
 *
 */

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include "ENC_03R.h"


/**
*@brief ENC_03R搭載小型圧電振動ジャイロモジュールの制御関連のクラスのコンストラクタ
* @param response 初期化成功でMRAA_SUCCESS、それ以外は失敗
* @param pin_X アナログピン番号(小型圧電振動ジャイロモジュールのピン1と接続)
* @param pin_Y アナログピン番号(小型圧電振動ジャイロモジュールのピン2と接続)
* @param r IIRフィルタの係数
*/
ENC_03R::ENC_03R(mraa_result_t &response, int pin_X, int pin_Y, double r) {
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


	_r = r;



	reset();

	response = MRAA_SUCCESS;

	
}

/**
*@brief ENC_03R搭載小型圧電振動ジャイロモジュールの制御関連のクラスのデストラクタ
*/
ENC_03R::~ENC_03R() {
	
	if(ax)delete ax;
	if(ay)delete ay;

	
}

/**
*@brief フィルタ係数再設定
* @param r 係数
*/
void ENC_03R::setCoefficient(double r)
{
	_r = r;
}

/**
*@brief 初期化
*/
void ENC_03R::reset()
{
	m_offsetX = 0;
	m_offsetY = 0;

	const double count = 10;
	double avx, avy;
	last_x = 0;
	last_y = 0;

	for(int i=0;i < count;i++)
	{
		getAngularVelocityData(avx,avy);
		last_x += avx/count;
		last_y += avy/count;
	}
	m_offsetX = last_x;
	m_offsetY = last_y;
}


/**
*@brief ピン番号の再設定
* @param pin_X アナログピン番号(小型圧電振動ジャイロモジュールのピン1と接続)
* @param pin_Y アナログピン番号(小型圧電振動ジャイロモジュールのピン2と接続)
* @return 成功でMRAA_SUCCESS、それ以外は失敗
*/
mraa_result_t ENC_03R::setPinNum(int pin_X, int pin_Y)
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

	

	return MRAA_SUCCESS;
}

/**
*@brief 計測した角速度取得(オフセット有り)
* @param avx 角速度(X)
* @param avy 角速度(Y)
*/
void ENC_03R::getAngularVelocityData(double &avx, double &avy) {
	float volx = ax->readFloat();
	float voly = ay->readFloat();

	//std::cout << volx << "\t" << voly << "\t" << volz << std::endl;
	avx = voltage2angularvelocity(volx,m_offsetX);
	avy = voltage2angularvelocity(voly,m_offsetY);

	
}

/**
*@brief 計測した角速度取得
* @param avx 角速度(X)
* @param avy 角速度(Y)
*/
void ENC_03R::getAngularVelocity(double &avx, double &avy) {
	getAngularVelocityData(avx,avy);
	
	
	last_x = (1-_r)*last_x + _r*avx;
	last_y = (1-_r)*last_y + _r*avy;



}

/**
*@brief 電圧値を角速度に変換
* @param dVolt 電圧値
* @param offset オフセット
* @return 角速度
*/
double ENC_03R::voltage2angularvelocity(double dVolt, double offset) {
  
	const double Vol = 5.0;
	const double SENS   = 0.67/1000.0*M_PI/180;
  	double av = dVolt*Vol/SENS - offset;

	return av;
}