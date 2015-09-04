/*!
 * @file  LSM9DS0.cpp
 * @brief 9軸センサLSM9DS0の通信関連のクラス
 *
 */

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <mraa.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include "LSM9DS0.h"



/**
*@brief 9軸センサLSM9DS0のI2C通信関連のクラスのコンストラクタ
* @param response 初期化成功でMRAA_SUCCESS、それ以外は失敗
* @param smf セマフォ操作オブジェクト
* @param AccaMagaddr 加速度、地磁気センサのアドレス(SPI通信の場合はデフォルトのI2Cアドレスを指定しておく)
* @param Gyroaddr ジャイロセンサのアドレス(SPI通信の場合はデフォルトのI2Cアドレスを指定しておく)
* @param Accscale 加速度センサのスケール
* @param Magnscale 地磁気センサのスケール
* @param GyroScale ジャイロセンサのスケール
* @param mx_offset 地磁気センサのオフセット(X)
* @param my_offset 地磁気センサのオフセット(Y)
* @param mz_offset 地磁気センサのオフセット(Z)
* @param ar 加速度へのIIRフィルタの係数
* @param mr 地磁気へのIIRフィルタの係数
* @param gr 角速度へのIIRフィルタの係数
*/
LSM9DS0::LSM9DS0(i2c_smf *smf, uint8_t AccaMagaddr, uint8_t Gyroaddr, uint8_t Accscale, uint8_t Magnscale, uint8_t GyroScale, int mx_offset, int my_offset, int mz_offset, double ar, double mr, double gr) {
	
	_AccMagaddr = AccaMagaddr;
	_Gyroaddr = Gyroaddr;
	
	_ar = ar;
	_mr = mr;
	_gr = gr;
	

	_smf = smf;

	_mx_offset = mx_offset;
	_my_offset = my_offset;
	_mz_offset = mz_offset;

	_Ascale = Accscale;
	_Mscale = Magnscale;
	_Gscale = GyroScale;

}

/**
*@brief 9軸センサLSM9DS0のI2C通信関連のクラスのデストラクタ
*/
LSM9DS0::~LSM9DS0() {
	//delete _smf;
}

/**
*@brief 加速度、地磁気センサの存在確認
* @return 存在する場合true、存在しない場合false
*/
bool LSM9DS0::AccMagSensor_Exist()
{
	uint8_t Buf[2];
	readByte(_AccMagaddr,LSM9DS0_REGISTER_WHO_AM_I_XM,1,Buf);


	if(Buf[0] != LSM9DS0_XM_ID)return false;

	return true;
}

/**
*@brief ジャイロセンサの存在確認
* @return 存在する場合true、存在しない場合false
*/
bool LSM9DS0::GyroSensor_Exist()
{
	uint8_t Buf[2];
	readByte(_Gyroaddr,LSM9DS0_REGISTER_WHO_AM_I_G,1,Buf);


	if(Buf[0] != LSM9DS0_G_ID)return false;
	return true;
}


/**
*@brief 加速度、地磁気センサのI2Cアドレス再設定
* @param AccaMagaddr I2Cアドレス
* @return 成功でMRAA_SUCCESS、それ以外は失敗
*/
mraa_result_t LSM9DS0::setAccMagAddr(uint8_t AccaMagaddr)
{
	if(_AccMagaddr != AccaMagaddr)
	{
		_AccMagaddr = AccaMagaddr;
		if(!AccMagSensor_Exist())return MRAA_ERROR_UNSPECIFIED;
		reset();
	}
	return MRAA_SUCCESS;

}

/**
*@brief ジャイロセンサのI2Cアドレス再設定
* @param Gyroaddr I2Cアドレス
* @return 成功でMRAA_SUCCESS、それ以外は失敗
*/
mraa_result_t LSM9DS0::setGyroAddr(uint8_t Gyroaddr)
{
	if(_Gyroaddr != Gyroaddr)
	{
		_Gyroaddr = Gyroaddr;
		if(!GyroSensor_Exist())return MRAA_ERROR_UNSPECIFIED;
		reset();
	}
	return MRAA_SUCCESS;

}

/**
*@brief 加速度センサのフィルタ係数再設定
* @param ar 係数
*/
void LSM9DS0::setAccCoefficient(double ar)
{
	_ar = ar;
}

/**
*@brief 地磁気センサのフィルタ係数再設定
* @param mr 係数
*/
void LSM9DS0::setMagnCoefficient(double mr)
{
	_mr = mr;
}

/**
*@brief ジャイロセンサのフィルタ係数再設定
* @param ar 係数
*/
void LSM9DS0::setGyroCoefficient(double gr)
{
	_gr = gr;
}

/**
*@brief 加速度センサスケール再設定
* @param Accscale スケール
*/
void LSM9DS0::setAccScale(uint8_t Accscale)
{
	if(_Ascale != Accscale)
	{
		_Ascale = Accscale;
		reset();
	}
	
}

/**
*@brief 地磁気センサスケール再設定
* @param Magnscale スケール
*/
void LSM9DS0::setMagnScale(uint8_t Magnscale)
{
	if(_Mscale != Magnscale)
	{
		_Mscale = Magnscale;
		reset();
	}
}

/**
*@brief ジャイロセンサスケール再設定
* @param GyroScale スケール
*/
void LSM9DS0::setGyroScale(uint8_t GyroScale)
{
	if(_Gscale != GyroScale)
	{
		_Gscale = GyroScale;
		reset();
	}
}


/**
*@brief 地磁気センサのオフセット再設定
* @param mx_offset オフセット(X)
* @param my_offset オフセット(Y)
* @param mz_offset オフセット(Z)
*/
void LSM9DS0::setOffset(int mx_offset, int my_offset, int mz_offset)
{
	_mx_offset = mx_offset;
	_my_offset = my_offset;
	_mz_offset = mz_offset;
}

/**
*@brief 加速度センサのスケールを反映
* @param scale スケール
*/
void LSM9DS0::setAccRange(uint8_t scale)
{
	_Ascale = scale;
	uint8_t reg[2];
	readByte(_AccMagaddr, LSM9DS0_REGISTER_CTRL_REG2_XM, 1, reg);
	reg[0] &= ~(0x38);
	reg[0] |= (scale << 3);
	writeByte(_AccMagaddr, LSM9DS0_REGISTER_CTRL_REG2_XM, reg[0]);
	//writeByte(_AccMagaddr, CTRL_REG4_A, _Ascale << 3);
	
	
}


/**
*@brief 地磁気センサのスケールを反映
* @param scale スケール
*/
void LSM9DS0::setMagnRange(uint8_t scale){
	_Mscale = scale;
	uint8_t reg[2];
	readByte(_AccMagaddr, LSM9DS0_REGISTER_CTRL_REG6_XM, 1, reg);
	reg[0] &= ~(0x60);
	reg[0] |= (scale << 5);
	writeByte(_AccMagaddr, LSM9DS0_REGISTER_CTRL_REG6_XM, reg[0]);
}

/**
*@brief ジャイロセンサのスケールを反映
* @param scale スケール
*/
void LSM9DS0::setGyroRange(uint8_t scale){
	_Gscale = scale;
	uint8_t reg[2];
	readByte(_Gyroaddr, LSM9DS0_REGISTER_CTRL_REG4_G, 1, reg);
	reg[0] &= ~(0x30);
	reg[0] |= (scale << 4);
	writeByte(_Gyroaddr, LSM9DS0_REGISTER_CTRL_REG4_G, reg[0]);
	
}

/**
*@brief 初期化
*/
void LSM9DS0::reset(void) {
	
	writeByte(_AccMagaddr, LSM9DS0_REGISTER_CTRL_REG1_XM, 0x67);
	writeByte(_AccMagaddr, LSM9DS0_REGISTER_CTRL_REG5_XM, 0xf0);
	writeByte(_AccMagaddr, LSM9DS0_REGISTER_CTRL_REG7_XM, 0x00);
	writeByte(_Gyroaddr, LSM9DS0_REGISTER_CTRL_REG1_G, 0x0F);
	
	uint8_t Buf[2];
	readByte(_AccMagaddr,LSM9DS0_REGISTER_CTRL_REG5_XM,1,Buf);
	writeByte(_Gyroaddr, LSM9DS0_REGISTER_CTRL_REG5_XM, Buf[0] | (1<<7));



	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = 200000000;
	nanosleep(&ts, NULL);
	
	setAccRange(_Ascale);

	nanosleep(&ts, NULL);

	setMagnRange(_Mscale);
	


	nanosleep(&ts, NULL);
	
  	setGyroRange(_Gscale);
  	
  	
 
  	
  	

	const double count = 10;
	double ax,ay,az;
	lastAX = 0;
	lastAY = 0;
	lastAZ = 0;
	
	for(int i=0;i < count;i++)
	{
		getAccData(ax,ay,az);

		lastAX += ax/count;
		lastAY += ay/count;
		lastAZ += az/count;
		usleep(10000);
	}


	

	double mx,my,mz;
	
	lastMX = 0;
	lastMY = 0;
	lastMZ = 0;
	for(int i=0;i < count;i++)
	{
		getMagnData(mx,my,mz);
		lastMX += mx/count;
		lastMY += my/count;
		lastMZ += mz/count;
		usleep(10000);
	}

	


	double avx,avy,avz;
	
	lastGX = 0;
	lastGY = 0;
	lastGZ = 0;
	for(int i=0;i < count;i++)
	{
		getGyroData(avx,avy,avz);
		lastGX += avx/count;
		lastGY += avy/count;
		lastGZ += avz/count;
		usleep(10000);
	}

	avx_offset = lastGX;
	avy_offset = lastGY;
	avz_offset = lastGZ;
}

/**
*@brief 姿勢を計算
* @param rx ロール角
* @param ry ピッチ角
* @param rz ヨー角
*/
void LSM9DS0::getOrientation(double &rx, double &ry, double &rz)
{
	

	ry = atan2(lastAY,lastAZ)-M_PI;
	rx = atan2(-lastAX,sqrt(lastAY*lastAY+lastAZ*lastAZ));

	

	double mxi = cos(ry)*lastMX + sin(rx)*sin(ry)*lastMY + cos(rx)*sin(ry)*lastMZ;
	double myi = cos(rx)*lastMY - sin(rx)*lastMZ;

	

	rz = atan2(myi,mxi);

	//std::cout << rz << "\t" << lastMX << "\t" << lastMY << "\t" << lastMZ << std::endl;
}

/**
*@brief 計測した加速度取得(オフセット有り)
* @param ax 加速度(X)
* @param ay 加速度(Y)
* @param az 加速度(Z)
*/
void LSM9DS0::getAcc(double &ax, double &ay, double &az)
{
	getAccData(ax,ay,az);

	lastAX = _ar*ax + (1-_ar)*lastAX;
	lastAY = _ar*ay + (1-_ar)*lastAY;
	lastAZ = _ar*az + (1-_ar)*lastAZ;
	

}

/**
*@brief 計測した地磁気取得(オフセット有り)
* @param ax 地磁気(X)
* @param ay 地磁気(Y)
* @param az 地磁気(Z)
*/
void LSM9DS0::getMagn(double &mx, double &my, double &mz)
{
	getMagnData(mx,my,mz);
	//mx = _mr*mx + (1-_mr)*lastMX;
	//my = _mr*my + (1-_mr)*lastMY;
	//mz = _mr*mz + (1-_mr)*lastMZ;

	lastMX = _mr*mx + (1-_mr)*lastMX;
	lastMY = _mr*my + (1-_mr)*lastMY;
	lastMZ = _mr*mz + (1-_mr)*lastMZ;

	//std::cout << mx << "\t" << my << "\t" << mz << std::endl;
}

/**
*@brief 計測した角速度取得(オフセット有り)
* @param ax 角速度(X)
* @param ay 角速度(Y)
* @param az 角速度(Z)
*/
void LSM9DS0::getGyro(double &avx, double &avy, double &avz)
{
	getGyroData(avx,avy,avz);
	avx -= avx_offset;
	avy -= avy_offset;
	avz -= avz_offset;

	lastGX = _gr*avx + (1-_gr)*lastGX;
	lastGY = _gr*avy + (1-_gr)*lastGY;
	lastGZ = _gr*avz + (1-_gr)*lastGZ;

	//std::cout << mx << "\t" << my << "\t" << mz << std::endl;
}


/**
*@brief 計測した温度取得(現在のところはgetTempDataと同じ)
* @return 温度
*/
double LSM9DS0::getTemp()
{
	lastTemp = getTempData();
	return lastTemp;
}




/**
*@brief 計測した加速度取得(オフセット有り)
* @param ax 加速度(X)
* @param ay 加速度(Y)
* @param az 加速度(Z)
*/
void LSM9DS0::getAccData(double &ax, double &ay, double &az) {
	uint8_t Buf[6];
	readByte(_AccMagaddr, LSM9DS0_REGISTER_OUT_X_L_A|0x80, 6, Buf);

	

	short AccelRaw_x = ((Buf[1] << 8) | Buf[0]);
	short AccelRaw_y = ((Buf[3] << 8) | Buf[2]);
	short AccelRaw_z = ((Buf[5] << 8) | Buf[4]);

	double aRes;
	if(_Ascale == LSM9DS0_ACCELRANGE_2G)
		aRes = LSM9DS0_ACCEL_MG_LSB_2G / 1000 * 9.8;
	else if(_Ascale == LSM9DS0_ACCELRANGE_4G)
		aRes = LSM9DS0_ACCEL_MG_LSB_4G / 1000 * 9.8;
	else if(_Ascale == LSM9DS0_ACCELRANGE_6G)
		aRes = LSM9DS0_ACCEL_MG_LSB_6G / 1000 * 9.8;
	else if(_Ascale == LSM9DS0_ACCELRANGE_8G)
		aRes = LSM9DS0_ACCEL_MG_LSB_8G / 1000 * 9.8;
	else
		aRes = LSM9DS0_ACCEL_MG_LSB_16G / 1000 * 9.8;
	ax = (double)AccelRaw_x * aRes;
	ay = (double)AccelRaw_y * aRes;
	az = (double)AccelRaw_z * aRes;

	

	
}

/**
*@brief 計測した地磁気取得(オフセット有り)
* @param ax 地磁気(X)
* @param ay 地磁気(Y)
* @param az 地磁気(Z)
*/
void LSM9DS0::getMagnData(double &mx, double &my, double &mz) {
	
	

	uint8_t Mag[6];

	readByte(_AccMagaddr, LSM9DS0_REGISTER_OUT_X_L_M|0x80, 6, Mag);

	short MagnRaw_x = ((Mag[1] << 8) | Mag[0]);
	short MagnRaw_y = ((Mag[3] << 8) | Mag[2]);
	short MagnRaw_z = ((Mag[5] << 8) | Mag[4]);
	
	
	MagnRaw_x += _mx_offset;
	MagnRaw_y += _my_offset;
	MagnRaw_z += _mz_offset;

	//std::cout << MagnRaw_x << "\t" << MagnRaw_y << "\t" << MagnRaw_z << std::endl;

	double mRes;
	if(_Mscale == LSM9DS0_MAGGAIN_2GAUSS)
		mRes = LSM9DS0_MAG_MGAUSS_2GAUSS / 1000;
	else if(_Mscale == LSM9DS0_MAGGAIN_4GAUSS)
		mRes = LSM9DS0_MAG_MGAUSS_4GAUSS / 1000;
	else if(_Mscale == LSM9DS0_MAGGAIN_8GAUSS)
		mRes = LSM9DS0_MAG_MGAUSS_8GAUSS / 1000;
	else
		mRes = LSM9DS0_MAG_MGAUSS_12GAUSS / 1000;

	mx = (double)MagnRaw_x * mRes;
	my = (double)MagnRaw_y * mRes;
	mz = (double)MagnRaw_z * mRes;

	
}

/**
*@brief 計測した角速度取得(オフセット有り)
* @param ax 角速度(X)
* @param ay 角速度(Y)
* @param az 角速度(Z)
*/
void LSM9DS0::getGyroData(double &avx, double &avy, double &avz) {
	
	

	uint8_t Gyro[6];

	readByte(_Gyroaddr, LSM9DS0_REGISTER_OUT_X_L_G|0x80, 6, Gyro);

	short GyroRaw_x = ((Gyro[1] << 8) | Gyro[0]);
	short GyroRaw_y = ((Gyro[3] << 8) | Gyro[2]);
	short GyroRaw_z = ((Gyro[5] << 8) | Gyro[4]);
	


	double gRes;
	if(_Gscale == LSM9DS0_GYROSCALE_245DPS)
		gRes = LSM9DS0_GYRO_DPS_DIGIT_245DPS*M_PI/180;
	else if(_Gscale == LSM9DS0_GYROSCALE_500DPS)
		gRes = LSM9DS0_GYRO_DPS_DIGIT_500DPS*M_PI/180;
	else
		gRes = LSM9DS0_GYRO_DPS_DIGIT_2000DPS*M_PI/180;

	avx = (double)GyroRaw_x * gRes;
	avy = (double)GyroRaw_y * gRes;
	avz = (double)GyroRaw_z * gRes;

	
}

/**
*@brief 計測した温度取得
* @return 温度
*/
double LSM9DS0::getTempData()
{
	uint8_t Buf[2];
	readByte(_AccMagaddr,LSM9DS0_REGISTER_TEMP_OUT_L_XM|0x80,2,Buf);

	short Temp = (Buf[1] << 8) | Buf[0];

	
	return 21.0 + (double)Temp/LSM9DS0_TEMP_LSB_DEGREE_CELSIUS;
}

/**
*@brief 特定レジスタに書き込んで値を読み込む
* @param Address I2Cアドレス(SPI通信の場合はセンサの判別に利用するのでアドレスのデフォルト値を入力)
* @param Register レジスタ
* @param Nbytes 読み込むデータの長さ
* @param Data 読み込んだデータ
*/
void LSM9DS0::writeByte(uint8_t Address, uint8_t Register, uint8_t Data) {


}

/**
*@brief 特定レジスタに書き込む
* @param Address I2Cアドレス(SPI通信の場合はセンサの判別に利用するのでアドレスのデフォルト値を入力)
* @param Register レジスタ
* @param Data 書き込むデータ
*/
void LSM9DS0::readByte(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data) {
	

}