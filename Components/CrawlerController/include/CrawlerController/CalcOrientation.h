/*!
* @file  CalcOrientation.h
* @brief 加速度、地磁気、角速度から姿勢計算するためのクラス
*
*/

#ifndef CalcOrientation_H
#define CalcOrientation_H

#include <coil/Time.h>
#include <coil/TimeMeasure.h>


/**
* @class CalcOrientation
*@brief 加速度、地磁気、角速度から姿勢計算するためのクラス
*/
class CalcOrientation
{
public:
	/**
	*@brief コンストラクタ
	* @param ar 加速度センサの計測値でのIIRフィルタの係数
	* @param mr 地磁気センサの計測値でのIIRフィルタの係数
	* @param gr ジャイロセンサの計測値でのIIRフィルタの係数
	* @param r 相補フィルタの係数
	*/
	CalcOrientation(double ar = 0.2, double mr = 0.2, double gr = 1.0, double r = 0.8);
	/**
	*@brief パラメータ再設定
	* @param ar 加速度センサの計測値でのIIRフィルタの係数
	* @param mr 地磁気センサの計測値でのIIRフィルタの係数
	* @param gr ジャイロセンサの計測値でのIIRフィルタの係数
	* @param r 相補フィルタの係数
	*/
	void setParam(double ar = 0.2, double mr = 0.2, double gr = 1.0, double r = 0.8);
	/**
	*@brief 初期化
	*/
	void reset();
	/**
	*@brief 姿勢角導出(加速度センサ、地磁気センサの計測値を利用)
	* @param ax 加速度(X)
	* @param ay 加速度(Y)
	* @param az 加速度(Z)
	* @param mx 地磁気(X)
	* @param my 地磁気(Y)
	* @param mz 地磁気(Z)
	* @param rx 姿勢角(X)
	* @param ry 姿勢角(Y)
	* @param rz 姿勢角(Z)
	*/
	void calc(double ax, double ay, double az, double mx, double my, double mz, double &rx, double &ry, double &rz);
	/**
	*@brief 姿勢角導出(加速度センサ、地磁気センサ、ジャイロセンサの計測値を利用)
	* @param ax 加速度(X)
	* @param ay 加速度(Y)
	* @param az 加速度(Z)
	* @param mx 地磁気(X)
	* @param my 地磁気(Y)
	* @param mz 地磁気(Z)
	* @param avx 角速度(X)
	* @param avy 角速度(Y)
	* @param avz 角速度(Z)
	* @param rx 姿勢角(X)
	* @param ry 姿勢角(Y)
	* @param rz 姿勢角(Z)
	*/
	void calc(double ax, double ay, double az, double mx, double my, double mz, double avx, double avy, double avz, double &rx, double &ry, double &rz);
	/**
	*@brief 加速度、地磁気による姿勢角の導出
	* @param ax 加速度(X)
	* @param ay 加速度(Y)
	* @param az 加速度(Z)
	* @param mx 地磁気(X)
	* @param my 地磁気(Y)
	* @param mz 地磁気(Z)
	* @param rx 姿勢角(X)
	* @param ry 姿勢角(Y)
	* @param rz 姿勢角(Z)
	*/
	void calcOrientation(double ax, double ay, double az, double mx, double my, double mz, double &rx, double &ry, double &rz);
	/**
	*@brief 加速度センサの計測値をIIRフィルタに通す
	* @param ax 加速度(X)
	* @param ay 加速度(Y)
	* @param az 加速度(Z)
	*/
	void calcAcceleration(double ax, double ay, double az);
	/**
	*@brief 地磁気センサの計測値をIIRフィルタに通す
	* @param mx 地磁気(X)
	* @param my 地磁気(Y)
	* @param mz 地磁気(Z)
	*/
	void calcMagnetic(double mx, double my, double mz);
	/**
	*@brief ジャイロセンサの計測値をIIRフィルタに通す
	* @param avx 角速度(X)
	* @param avy 角速度(Y)
	* @param avz 角速度(Z)
	*/
	void calcGyro(double avx, double avy, double avz);
	/**
	*@brief 時間を更新
	* @return 前回計測した時間との差分
	*/
	double updateTime();
private:

	double m_r;
	double m_ar, m_mr, m_gr;
	double last_ax, last_ay, last_az;
	double last_mx, last_my, last_mz;
	double last_avx, last_avy, last_avz;
	coil::TimeValue first_time;
	double last_time;
	int lv_count;
	double last_rx, last_ry, last_rz;
};



#endif
