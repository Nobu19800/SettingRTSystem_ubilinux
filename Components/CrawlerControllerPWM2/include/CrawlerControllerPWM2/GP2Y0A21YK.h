/*!
 * @file  GP2Y0A21YK.h
 * @brief 距離センサGP2Y0A21YKの制御関連のクラス
 *
 */

#ifndef GP2Y0A21YK_H
#define GP2Y0A21YK_H

#include <stdio.h>
#include <mraa.hpp>



/**
 * @class GP2Y0A21YK
*@brief 距離センサGP2Y0A21YKの制御関連のクラス
*/
class GP2Y0A21YK
{
public:
	/**
	*@brief コンストラクタ
	* @param response 初期化成功でMRAA_SUCCESS、それ以外は失敗
	* @param pin アナログピン番号(GP2Y0A21YKの通信線と接続)
	* @param r IIRフィルタの係数
	*/
	GP2Y0A21YK(mraa_result_t &response, int pin = 0, double r = 0.2);
	/**
	*@brief デストラクタ
	*/
	~GP2Y0A21YK();
	/**
	*@brief 計測した距離取得
	* @return 距離
	*/
	double getDistance();
	/**
	*@brief 計測した距離取得(フィルタ処理有り)
	* @return 距離
	*/
	double getDistanceData();
	/**
	*@brief 電圧値から距離に変換
	* @param dVolt 電圧値
	* @return 距離
	*/
	double voltage2distance(double dVolt);
	/**
	*@brief アナログピン再設定
	* @param pin ピン番号
	* @return 成功でMRAA_SUCCESS、それ以外は失敗
	*/
	mraa_result_t setPinNum(int pin = 0);
	/**
	*@brief フィルタ係数再設定
	* @param r 係数
	*/
	void setCoefficient(double r = 0.2);
	
private:
	mraa::Aio* a;
	double lastDistance;
	double _r;
	int m_pin;
};





#endif