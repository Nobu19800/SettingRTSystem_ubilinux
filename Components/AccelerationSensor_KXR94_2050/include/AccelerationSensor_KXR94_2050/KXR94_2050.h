/*!
 * @file  KXR94_2050.h
 * @brief 加速度センサKXR94_2050の制御関連のクラス
 *
 */

#ifndef KXR94_2050_H
#define KXR94_2050_H

#include <stdio.h>
#include <mraa.hpp>



/**
 * @class KXR94_2050
*@brief 加速度センサKXR94_2050の制御関連のクラス
*/
class KXR94_2050
{
public:
	/**
	*@brief コンストラクタ
	* @param response 初期化成功でMRAA_SUCCESS、それ以外は失敗
	* @param pin_X アナログピン番号(KXR94_2050のピン6と接続)
	* @param pin_Y アナログピン番号(KXR94_2050のピン7と接続)
	* @param pin_Z アナログピン番号(KXR94_2050のピン8と接続)
	* @param voltage 電源電圧値
	* @param r IIRフィルタの係数
	*/
	KXR94_2050(mraa_result_t &response, int pin_X = 0, int pin_Y = 1, int pin_Z = 2, double voltage = 5.0, double r = 0.2);
	/**
	*@brief デストラクタ
	*/
	~KXR94_2050();
	/**
	*@brief ピン番号再設定
	* @param pin_X アナログピン番号(KXR94_2050のピン6と接続)
	* @param pin_Y アナログピン番号(KXR94_2050のピン7と接続)
	* @param pin_Z アナログピン番号(KXR94_2050のピン8と接続)
	* @return 初期化成功でMRAA_SUCCESS、それ以外は失敗
	*/
	mraa_result_t setPinNum(int pin_X = 0, int pin_Y = 1, int pin_Z = 2);
	/**
	*@brief フィルタ係数再設定
	* @param r 係数
	*/
	void setCoefficient(double r = 0.2);
	/**
	*@brief 計測した加速度取得(オフセット有り)
	* @param acx 加速度(X)
	* @param acy 加速度(Y)
	* @param acz 加速度(Z)
	*/
	void getAcceleration(double &acx, double &acy, double &acz);
	/**
	*@brief 計測した加速度取得
	* @param acx 加速度(X)
	* @param acy 加速度(Y)
	* @param acz 加速度(Z)
	*/
	void getAccelerationData(double &acx, double &acy, double &acz);
	/**
	*@brief 電圧値を加速度に変換
	* @param dVolt 電圧値(0～1)
	* @return 加速度
	*/
	double voltage2acceleration(double dVolt);
	/**
	*@brief 電源電圧値を再設定
	* @param voltage 電源電圧値
	*/
	void setVoltage(double voltage);
	/**
	*@brief 初期化
	*/
	void reset();
	
private:
	mraa::Aio* ax;
	mraa::Aio* ay;
	mraa::Aio* az;


	double _r;

	double last_x, last_y, last_z;
	
	int m_pin_X, m_pin_Y, m_pin_Z;
	double m_voltage;

};





#endif