/*!
* @file  Crawler.h
* @brief クローラー制御のクラス
*
*/

#ifndef CRAWLER_H
#define CRAWLER_H


#include <stdio.h>
#include <coil/Time.h>
#include <coil/TimeMeasure.h>

enum Crawler_Direction { C_Forword, C_Forword_Left, C_Forword_Right, C_Left, C_Right, C_Back, C_Back_Left, C_Back_Right, C_Stop };



/**
* @class Crawler
*@brief クローラー制御のクラス
*/
class Crawler
{
public:
	/**
	*@brief コンストラクタ
	* @param frontRangeSensor 前方に距離センサを取り付ける場合はtrue
	* @param backRangeSensor 後方に距離センサを取り付ける場合はtrue
	* @param bias 値が大きくなるほど旋回しやすくなるパラメータ
	* @param frontDistance 回避運動を開始する障害物までの最長距離
	* @param backDistance 回避運動を開始する障害物までの最短距離
	* @param filter 余分に回避運動をするパラメータ
	* @param rotCorVal 姿勢の変化した方向に抗う方向に回転する補正への係数
	*/
	Crawler(int frontRangeSensor = 1, int backRangeSensor = 1, double bias = 1.0, double frontDistance = 0.5, double backDistance = 0.1, double filter = 0.05,  double rotCorVal = 0.3);
	/**
	*@brief 各パラメータ再設定
	* @param frontRangeSensor 前方に距離センサを取り付ける場合はtrue
	* @param backRangeSensor 後方に距離センサを取り付ける場合はtrue
	* @param bias 値が大きくなるほど旋回しやすくなるパラメータ
	* @param frontDistance 回避運動を開始する障害物までの最長距離
	* @param backDistance 回避運動を開始する障害物までの最短距離
	* @param filter 余分に回避運動をするパラメータ
	* @param rotCorVal 姿勢の変化した方向に抗う方向に回転する補正への係数
	*/
	void setParam(int frontRangeSensor = 1, int backRangeSensor = 1, double bias = 1.0, double frontDistance = 0.5, double backDistance = 0.1, double filter = 0.05, double rotCorVal = 15);
	/**
	*@brief 初期化
	*/
	void reset();
	/**
	*@brief モーターへの出力計算
	* @param input_crawlerVol0 左モータードライバのデューティー比
	* @param input_crawlerVol1 右モータードライバのデューティー比
	* @param rn0 距離センサ(右前)の計測値
	* @param rn1 距離センサ(左前)の計測値
	* @param rn2 距離センサ(右後)の計測値
	* @param rn3 距離センサ(左後)の計測値
	* @return 直進速度
	*/
	double calc(double &input_crawlerVol0, double &input_crawlerVol1, double rn0 = 0, double rn1 = 0, double rn2 = 0, double rn3 = 0, double rz = 0);
	/**
	*@brief 姿勢角の変化量計算
	* @param rz Z軸の姿勢角
	* @return 姿勢角の変化量
	*/
	double calcAV(double rz);
	/**
	*@brief 各モーターへの出力の目標値設定
	* @param v0 左モータードライバのデューティー比
	* @param v1 右モータードライバのデューティー比
	*/
	void setVol(double v0, double v1);
private:
	int m_frontRangeSensor, m_backRangeSensor;
	double m_bias, m_frontDistance, m_backDistance, m_filter, m_rotCorVal;
	double crawlerVol0;
	double crawlerVol1;

	double last_bias0;
	double last_bias1;


	double last_rz;

	int lv_count;
	coil::TimeValue last_time, first_time;
};
#endif
