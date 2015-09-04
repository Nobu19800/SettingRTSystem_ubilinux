/*!
 * @file  TA8428K.h
 * @brief モータードライバTA8428Kの制御関連のクラス
 *
 */

#ifndef TA8428K_H
#define TA8428K_H

#include <stdio.h>
#include <mraa.hpp>



/**
 * @class TA8428K
*@brief モータードライバTA8428Kの制御関連のクラス
*/
class TA8428K
{
public:
	/**
	*@brief コンストラクタ
	* @param response 初期化成功でMRAA_SUCCESS、それ以外は失敗
	* @param pwm_pin0 PWMピンの番号(TA8428KのIN1に接続)
	* @param pwm_pin1 PWMピンの番号(TA8428KのIN2に接続)
	*/
	TA8428K(mraa_result_t &response, int pwm_pin0 = 3, int pwm_pin1 = 5);
	/**
	*@brief デストラクタ
	*/
	~TA8428K();
	/**
	*@brief TA8428Kの出力のデューティー比を設定
	* @param vol デューティー比
	*/
	void setValue(double vol);
	/**
	*@brief PWMピンの番号の再設定
	* @param pwm_pin0 PWMピンの番号(TA8428KのIN1に接続)
	* @param pwm_pin1 PWMピンの番号(TA8428KのIN2に接続)
	* @return 初期化成功でMRAA_SUCCESS、それ以外は失敗
	*/
	mraa_result_t setPinNum(int pwm_pin0 = 3, int pwm_pin1 = 5);
private:
	mraa::Pwm* pwm0;
	mraa::Pwm* pwm1;
	int m_pin0;
	int m_pin1;
};





#endif