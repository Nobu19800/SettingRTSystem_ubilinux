/*!
 * @file  TA7291P.h
 * @brief モータードライバTA7291Pの制御関連のクラス
 *
 */

#ifndef TA7291P_H
#define TA7291P_H

#include <stdio.h>
#include <mraa.hpp>



/**
 * @class TA7291P
*@brief モータードライバTA7291Pの制御関連のクラス
*/
class TA7291P
{
public:
	/**
	*@brief コンストラクタ
	* @param response 初期化成功でMRAA_SUCCESS、それ以外は失敗
	* @param pwm_pin PWMピン番号(TA7291PのVrefに接続)
	* @param in0_pin デジタルピン番号(TA7291PのIN1に接続)
	* @param in1_pin デジタルピン番号(TA7291PのIN2に接続)
	*/
	TA7291P(mraa_result_t &response, int pwm_pin = 3, int in0_pin = 2, int in1_pin = 4);
	/**
	*@brief デストラクタ
	*/
	~TA7291P();
	/**
	*@brief TA7291Pの出力のデューティー比を設定
	* @param vol デューティー比
	*/
	void setValue(double vol);
	/**
	*@brief ピンの番号の再設定
	* @param pwm_pin PWMピン番号(TA7291PのVrefに接続)
	* @param in0_pin デジタルピン番号(TA7291PのIN1に接続)
	* @param in1_pin デジタルピン番号(TA7291PのIN2に接続)
	* @return 初期化成功でMRAA_SUCCESS、それ以外は失敗
	*/
	mraa_result_t setPinNum(int pwm_pin = 3, int in0_pin = 2, int in1_pin = 4);
	
private:
	mraa::Pwm* pwm;
	mraa::Gpio* in0;
	mraa::Gpio* in1;
	int m_pwm_pin;
	int m_in0_pin;
	int m_in1_pin;
};





#endif