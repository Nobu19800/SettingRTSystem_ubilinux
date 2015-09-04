/*!
 * @file  GP2Y0A21YK.cpp
 * @brief 距離センサGP2Y0A21YKの制御関連のクラス
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "GP2Y0A21YK.h"


/**
*@brief 距離センサGP2Y0A21YKの制御関連のクラスのコンストラクタ
* @param response 初期化成功でMRAA_SUCCESS、それ以外は失敗
* @param pin アナログピン番号(GP2Y0A21YKの通信線と接続)
* @param r IIRフィルタの係数
*/
GP2Y0A21YK::GP2Y0A21YK(mraa_result_t &response, int pin, double r) {
	m_pin = pin;
	a = new mraa::Aio(pin);
	if (a == NULL) {
        	response = MRAA_ERROR_UNSPECIFIED;
		return;
    	}
	response = MRAA_SUCCESS;

	const int count = 10;
	lastDistance = 0;
	for(int i=0;i < count;i++)
	{
		lastDistance += getDistanceData()/count;
	}
	
	_r = r;
}

/**
*@brief 距離センサGP2Y0A21YKの制御関連のクラスのデストラクタ
*/
GP2Y0A21YK::~GP2Y0A21YK() {
	if(a)
	{
		delete a;
	}
}

/**
*@brief 計測した距離取得
* @return 距離
*/
double GP2Y0A21YK::getDistanceData() {
	float vol = a->readFloat();
	double distance = voltage2distance(vol*5)/100;

	return distance;
}

/**
*@brief アナログピン再設定
* @param pin ピン番号
* @return 成功でMRAA_SUCCESS、それ以外は失敗
*/
mraa_result_t GP2Y0A21YK::setPinNum(int pin)
{
	if(pin != m_pin)
	{
		if(a)
		{
			delete a;
		}
		a = new mraa::Aio(pin);
		if (a == NULL) {
	        	return MRAA_ERROR_UNSPECIFIED;
	    	}
		m_pin = pin;
	}
	return MRAA_SUCCESS;
}

/**
*@brief フィルタ係数再設定
* @param r 係数
*/
void GP2Y0A21YK::setCoefficient(double r)
{
	_r = r;
}

/**
*@brief 計測した距離取得(フィルタ処理有り)
* @return 距離
*/
double GP2Y0A21YK::getDistance() {
	

	lastDistance = _r*getDistanceData() + (1-_r)*lastDistance;

	return lastDistance;
}

/**
*@brief 電圧値から距離に変換
*http://nekosan0.bake-neko.net/connection_ir_measure.htmlのデータを使用
* @param dVolt 電圧値
* @return 距離
*/
double GP2Y0A21YK::voltage2distance(double dVolt) {
  
  	double dDist;
  
  
	if(dVolt < 0.384321){
	    dDist = 999.0;

	  }else if(dVolt < 0.430210){
	    dDist = dVolt * (-217.916667) + 163.750000;
	    
	  }else if (dVolt < 0.493308){
	    dDist = dVolt * (-158.484848) + 138.181818;
	      
	  }else if (dVolt < 0.590822){
	    dDist = dVolt * (-102.549020) + 110.588235;
	        
	  }else if (dVolt < 0.722753){
	    dDist = dVolt * (-75.797101) + 94.782609;
	          
	  }else if (dVolt < 0.894837){
	    dDist = dVolt * (-58.111111) + 82.000000;
	            
	  }else if (dVolt < 1.284895){
	    dDist = dVolt * (-25.637255) + 52.941176;
	              
	  }else if (dVolt < 1.623327){
	    dDist = dVolt * (-14.774011) + 38.983051;
	                
	  }else if (dVolt < 2.294455){
	    dDist = dVolt * (-7.450142) + 27.094017;
	                  
	  }else if (dVolt < 3.131931){
	    dDist = dVolt * (-5.970320) + 23.698630;
	  }

	  else{
	    dDist = 0.0;
	}

	return dDist;
}