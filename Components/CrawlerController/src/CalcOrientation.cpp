/*!
* @file  CalcOrientation.cpp
* @brief 加速度、地磁気、角速度から姿勢計算するためのクラス
*
*/

#define _USE_MATH_DEFINES
#include <math.h>
#include "CalcOrientation.h"


/**
*@brief 加速度、地磁気、角速度から姿勢計算するためのクラスのコンストラクタ
* @param ar 加速度センサの計測値でのIIRフィルタの係数
* @param mr 地磁気センサの計測値でのIIRフィルタの係数
* @param gr ジャイロセンサの計測値でのIIRフィルタの係数
* @param r 相補フィルタの係数
*/
CalcOrientation::CalcOrientation(double ar, double mr, double gr, double r)
{
	setParam( ar, mr, gr, r);
}


/**
*@brief パラメータ再設定
* @param ar 加速度センサの計測値でのIIRフィルタの係数
* @param mr 地磁気センサの計測値でのIIRフィルタの係数
* @param gr ジャイロセンサの計測値でのIIRフィルタの係数
* @param r 相補フィルタの係数
*/
void CalcOrientation::setParam(double ar, double mr, double gr, double r)
{

	m_ar = ar;
	m_mr = mr;
	m_gr = gr;
	m_r = r;
}


/**
*@brief 初期化
*/
void CalcOrientation::reset()
{
	lv_count = 0;
	first_time = coil::TimeValue(coil::gettimeofday());

	
	

}

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
void CalcOrientation::calc(double ax, double ay, double az, double mx, double my, double mz, double &rx, double &ry, double &rz)
{
	calcAcceleration(ax,ay,az);
	calcMagnetic(mx,my,mz);
	double dt = updateTime();

	
	calcOrientation(last_ax, last_ay, last_az, last_mx, last_my, last_mz, rx, ry, rz);
	lv_count += 1;

}



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
void CalcOrientation::calc(double ax, double ay, double az, double mx, double my, double mz, double avx, double avy, double avz, double &rx, double &ry, double &rz)
{
	calcAcceleration(ax,ay,az);
	calcMagnetic(mx,my,mz);
	calcGyro(avx,avy,avz);
	double dt = updateTime();

	double am_rx, am_ry, am_rz;
	calcOrientation(last_ax, last_ay, last_az, last_mx, last_my, last_mz, am_rx, am_ry, am_rz);

	
	if(lv_count == 0)
	{
		rx = am_rx;
		ry = am_ry;
		rz = am_rz;
		last_rx = rx;
		last_ry = ry;
		last_rz = rz;
	}
	else
	{
		double sx = sin(last_rx);
		double cx = cos(last_rx);
		double sy = sin(last_ry);
		double cy = cos(last_ry);
		double sz = sin(last_rz);
		double cz = cos(last_rz);
		double a_avx = cz*cy*last_avx + (-sz*cx + cz*sy*sx)*last_avy + (sz*sx + cz*sy*cx)*last_avz;
		double a_avy = sz*cy*last_avx + (cz*cx + sz*sy*sx)*last_avy + (-cz*sx + sz*sy*cx)*last_avz;
		double a_avz = -sy*last_avx + cy*sx*last_avy + cy*cx*last_avz;

		rx = m_r*(last_rx + a_avx*dt) + (1-m_r)*am_rx;
		ry = m_r*(last_ry + a_avy*dt) + (1-m_r)*am_ry;
		rz = m_r*(last_rz + a_avz*dt) + (1-m_r)*am_rz;

		last_rx = rx;
		last_ry = ry;
		last_rz = rz;
	}
	lv_count += 1;

}

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
void CalcOrientation::calcOrientation(double ax, double ay, double az, double mx, double my, double mz, double &rx, double &ry, double &rz)
{
	ry = atan2(ay,az) - M_PI;
	rx = atan2(-ax,sqrt(ay*ay+az*az));

	double mxi = cos(ry)*mx + sin(rx)*sin(ry)*my + cos(rx)*sin(ry)*mz;
	double myi = cos(rx)*my - sin(rx)*mz;

	rz = atan2(myi,mxi);

	
}

/**
*@brief 加速度センサの計測値をIIRフィルタに通す
* @param ax 加速度(X)
* @param ay 加速度(Y)
* @param az 加速度(Z)
*/
void CalcOrientation::calcAcceleration(double ax, double ay, double az)
{
	if(lv_count > 0)
	{
		last_ax = m_ar*ax + (1-m_ar)*last_ax;
		last_ay = m_ar*ay + (1-m_ar)*last_ay;
		last_az = m_ar*az + (1-m_ar)*last_az;
	}
	else
	{
		last_ax = ax;
		last_ay = ay;
		last_az = az;
	}
}

/**
*@brief 地磁気センサの計測値をIIRフィルタに通す
* @param mx 地磁気(X)
* @param my 地磁気(Y)
* @param mz 地磁気(Z)
*/
void CalcOrientation::calcMagnetic(double mx, double my, double mz)
{
	if(lv_count > 0)
	{
		last_mx = m_mr*mx + (1-m_mr)*last_mx;
		last_my = m_mr*my + (1-m_mr)*last_my;
		last_mz = m_mr*mz + (1-m_mr)*last_mz;
	}
	else
	{

		last_mx = mx;
		last_my = my;
		last_mz = mz;
	}
}

/**
*@brief ジャイロセンサの計測値をIIRフィルタに通す
* @param avx 角速度(X)
* @param avy 角速度(Y)
* @param avz 角速度(Z)
*/
void CalcOrientation::calcGyro(double avx, double avy, double avz)
{
	if(lv_count > 0)
	{
		last_avx = m_gr*avx + (1-m_gr)*last_avx;
		last_avy = m_gr*avy + (1-m_gr)*last_avy;
		last_avz = m_gr*avz + (1-m_gr)*last_avz;
	}
	else
	{
		last_avx = avx;
		last_avy = avy;
		last_avz = avz;
	}
}

/**
*@brief 時間を更新
* @return 前回計測した時間との差分
*/
double CalcOrientation::updateTime()
{
	
	coil::TimeValue t0(coil::gettimeofday());
	double now_time = (double)(t0-first_time);

	double ans = 0;
	if(lv_count > 0)
	{
		ans = now_time - last_time;
	}
	last_time = now_time;

	

	return ans;
}