/*!
 * @file  ENC_03R.h
 * @brief ENC_03R搭載小型圧電振動ジャイロモジュールの制御関連のクラス
 *
 */

#ifndef ENC_03R_H
#define ENC_03R_H

#include <stdio.h>
#include <mraa.hpp>



/**
 * @class ENC_03R
*@brief ENC_03R搭載小型圧電振動ジャイロモジュールの制御関連のクラス
*/
class ENC_03R
{
public:
	/**
	*@brief コンストラクタ
	* @param response 初期化成功でMRAA_SUCCESS、それ以外は失敗
	* @param pin_X アナログピン番号(小型圧電振動ジャイロモジュールのピン1と接続)
	* @param pin_Y アナログピン番号(小型圧電振動ジャイロモジュールのピン2と接続)
	* @param r IIRフィルタの係数
	*/
	ENC_03R(mraa_result_t &response, int pin_X = 0, int pin_Y = 1, double r = 0.2);
	/**
	*@brief デストラクタ
	*/
	~ENC_03R();
	/**
	*@brief ピン番号の再設定
	* @param pin_X アナログピン番号(小型圧電振動ジャイロモジュールのピン1と接続)
	* @param pin_Y アナログピン番号(小型圧電振動ジャイロモジュールのピン2と接続)
	* @return 成功でMRAA_SUCCESS、それ以外は失敗
	*/
	mraa_result_t setPinNum(int pin_X = 0, int pin_Y = 1);
	/**
	*@brief フィルタ係数再設定
	* @param r 係数
	*/
	void setCoefficient(double r);
	/**
	*@brief 計測した角速度取得(オフセット有り)
	* @param avx 角速度(X)
	* @param avy 角速度(Y)
	*/
	void getAngularVelocity(double &avx, double &avy);
	/**
	*@brief 計測した角速度取得
	* @param avx 角速度(X)
	* @param avy 角速度(Y)
	*/
	void getAngularVelocityData(double &avx, double &avy);
	/**
	*@brief 電圧値を角速度に変換
	* @param dVolt 電圧値
	* @param offset オフセット
	* @return 角速度
	*/
	double voltage2angularvelocity(double dVolt, double offset);
	/**
	*@brief 初期化
	*/
	void reset();
	
private:
	mraa::Aio* ax;
	mraa::Aio* ay;


	double _r;

	double last_x, last_y;
	
	int m_pin_X, m_pin_Y;
	double m_offsetX, m_offsetY;

};





#endif