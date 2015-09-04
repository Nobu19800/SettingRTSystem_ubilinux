/*!
 * @file  LSM303DLHC.cpp
 * 定数名はhttps://github.com/pololu/lsm303-arduino/blob/master/LSM303/LSM303.h(MITライセンス)から引用しました。
 * @brief 6軸センサLSM303DLHCの通信関連のクラス
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
#include "LSM303DLHC.h"


#define DLM_WHO_ID  0x3C


/**
*@brief 6軸センサLSM303DLHCの通信関連のクラスのコンストラクタ
* @param response 初期化成功でMRAA_SUCCESS、それ以外は失敗
* @param i2c I2C操作オブジェクト
* @param smf セマフォ操作オブジェクト
* @param AccaMagaddr 加速度センサのアドレス
* @param Magnaddr 地磁気センサのアドレス
* @param Accscale 加速度センサのスケール
* @param Magnscale 地磁気センサのスケール
* @param mx_offset 地磁気センサのオフセット(X)
* @param my_offset 地磁気センサのオフセット(Y)
* @param mz_offset 地磁気センサのオフセット(Z)
* @param ar 加速度へのIIRフィルタの係数
* @param mr 地磁気へのIIRフィルタの係数
*/
LSM303DLHC::LSM303DLHC(mraa_result_t &response, mraa::I2c *i2c, i2c_smf *smf, uint8_t Accaddr, uint8_t Magnaddr, uint8_t Accscale, uint8_t Magnscale, int mx_offset, int my_offset, int mz_offset, double ar, double mr) {
	_i2c = i2c;
	
	
	_ar = ar;
	_mr = mr;
	
	
	_Accaddr = Accaddr;
	_Magnaddr = Magnaddr;

	//_smf = new i2c_smf();
	_smf = smf;

	_mx_offset = mx_offset;
	_my_offset = my_offset;
	_mz_offset = mz_offset;

	_Ascale = Accscale;
	_Mscale = Magnscale;

	if(!AccSensor_Exist())
	{
		response = MRAA_ERROR_UNSPECIFIED;
		return;
	}
	if(!MagnSensor_Exist())
	{
		response = MRAA_ERROR_UNSPECIFIED;
		return;
	}

	reset();

	response = MRAA_SUCCESS;
}

/**
*@brief 6軸センサLSM303DLHCの通信関連のクラスのデストラクタ
*/
LSM303DLHC::~LSM303DLHC() {
	//delete _smf;
}

/**
*@brief 加速度センサの存在確認
* @return 存在する場合true、存在しない場合false
*/
bool LSM303DLHC::AccSensor_Exist()
{
	//uint8_t Buf[2];
	//readByte(_Accaddr,WHO_AM_I,1,Buf);

	return true;
}

/**
*@brief 地磁気センサの存在確認
* @return 存在する場合true、存在しない場合false
*/
bool LSM303DLHC::MagnSensor_Exist()
{
	uint8_t Buf[2];
	readByte(_Magnaddr,WHO_AM_I_M,1,Buf);

	
	if(Buf[0] != DLM_WHO_ID)return false;
	return true;
}

/**
*@brief 加速度センサのI2Cアドレス再設定
* @param AccaMagaddr I2Cアドレス
* @return 成功でMRAA_SUCCESS、それ以外は失敗
*/
mraa_result_t LSM303DLHC::setAccAddr(uint8_t Accaddr)
{
	if(_Accaddr != Accaddr)
	{
		_Accaddr = Accaddr;
		if(!AccSensor_Exist())return MRAA_ERROR_UNSPECIFIED;
		reset();
	}
	return MRAA_SUCCESS;

}

/**
*@brief 地磁気センサのI2Cアドレス再設定
* @param Magnaddr I2Cアドレス
* @return 成功でMRAA_SUCCESS、それ以外は失敗
*/
mraa_result_t LSM303DLHC::setMagnAddr(uint8_t Magnaddr)
{
	if(_Magnaddr != Magnaddr)
	{
		_Magnaddr = Magnaddr;
		if(!MagnSensor_Exist())return MRAA_ERROR_UNSPECIFIED;
		reset();
	}
	return MRAA_SUCCESS;

}

/**
*@brief 加速度センサのフィルタ係数再設定
* @param ar 係数
*/
void LSM303DLHC::setAccCoefficient(double ar)
{
	_ar = ar;
}

/**
*@brief 地磁気センサのフィルタ係数再設定
* @param mr 係数
*/
void LSM303DLHC::setMagnCoefficient(double mr)
{
	_mr = mr;
}

/**
*@brief 加速度センサスケール再設定
* @param Accscale スケール
*/
void LSM303DLHC::setAccScale(uint8_t Accscale)
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
void LSM303DLHC::setMagnScale(uint8_t Magnscale)
{
	if(_Mscale != Magnscale)
	{
		_Mscale = Magnscale;
		reset();
	}
}


/**
*@brief 地磁気センサのオフセット再設定
* @param mx_offset オフセット(X)
* @param my_offset オフセット(Y)
* @param mz_offset オフセット(Z)
*/
void LSM303DLHC::setOffset(int mx_offset, int my_offset, int mz_offset)
{
	_mx_offset = mx_offset;
	_my_offset = my_offset;
	_mz_offset = mz_offset;
}

/**
*@brief 加速度センサのスケールを反映
* @param scale スケール
*/
void LSM303DLHC::setAccRange(uint8_t scale)
{
	_Ascale = scale;
	writeByte(_Accaddr, CTRL_REG4_A, _Ascale << 3);
	
	
}


/**
*@brief 地磁気センサのスケールを反映
* @param scale スケール
*/
void LSM303DLHC::setMagnRange(uint8_t scale){
	_Mscale = scale;
	writeByte(_Magnaddr, CRB_REG_M, _Mscale << 3);
	
}

/**
*@brief 初期化
*/
void LSM303DLHC::reset(void) {
	
	
	

	
	//_i2c->address(_Accaddr);

	
	writeByte(_Accaddr,CTRL_REG1_A,0x27);

	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = 200000000;
	nanosleep(&ts, NULL);
	
	setAccRange(_Ascale);
	
	
	
	writeByte(_Magnaddr,CRA_REG_M,0x14);
	nanosleep(&ts, NULL);
	//writeByte(_Magnaddr,CRB_REG_M,0x20);
	writeByte(_Magnaddr,MR_REG_M,0x00);
	nanosleep(&ts, NULL);
	setMagnRange(_Mscale);
	


	nanosleep(&ts, NULL);
	
  	
  	
  	
 
  	
  	

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

	
}

/**
*@brief 姿勢を計算
* @param rx ロール角
* @param ry ピッチ角
* @param rz ヨー角
*/
void LSM303DLHC::getOrientation(double &rx, double &ry, double &rz)
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
void LSM303DLHC::getAcc(double &ax, double &ay, double &az)
{
	getAccData(ax,ay,az);

	lastAX = _ar*ax + (1-_ar)*lastAX;
	lastAY = _ar*ay + (1-_ar)*lastAY;
	lastAZ = _ar*az + (1-_ar)*lastAZ;
	

}

/**
*@brief 計測した地磁気取得(オフセット有り)
* @param mx 地磁気(X)
* @param my 地磁気(Y)
* @param mz 地磁気(Z)
*/
void LSM303DLHC::getMagn(double &mx, double &my, double &mz)
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
*@brief 計測した温度取得(現在のところはgetTempDataと同じ)
* @return 温度
*/
double LSM303DLHC::getTemp()
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
void LSM303DLHC::getAccData(double &ax, double &ay, double &az) {
	uint8_t Buf[6];
	readByte(_Accaddr, OUT_X_L_A|0x80, 6, Buf);

	

	short AccelRaw_x = ((Buf[1] << 8) | Buf[0]);
	short AccelRaw_y = ((Buf[3] << 8) | Buf[2]);
	short AccelRaw_z = ((Buf[5] << 8) | Buf[4]);

	double aRes;
	if(_Ascale == AFS_2G)
		aRes = 4.0/32768.0;
	else if(_Ascale == AFS_4G)
		aRes = 8.0/32768.0;
	else if(_Ascale == AFS_8G)
		aRes = 16.0/32768.0;
	else
		aRes = 32.0/32768.0;
	ax = (double)AccelRaw_x * aRes;
	ay = (double)AccelRaw_y * aRes;
	az = (double)AccelRaw_z * aRes;

	

	
}

/**
*@brief 計測した地磁気取得(オフセット有り)
* @param mx 地磁気(X)
* @param my 地磁気(Y)
* @param mz 地磁気(Z)
*/
void LSM303DLHC::getMagnData(double &mx, double &my, double &mz) {
	
	

	uint8_t Mag[6];

	readByte(_Magnaddr, DLH_OUT_X_H_M, 6, Mag);

	short MagnRaw_x = ((Mag[0] << 8) | Mag[1]);
	short MagnRaw_y = ((Mag[4] << 8) | Mag[5]);
	short MagnRaw_z = ((Mag[2] << 8) | Mag[3]);
	
	MagnRaw_x += _mx_offset;
	MagnRaw_y += _my_offset;
	MagnRaw_z += _mz_offset;

	//std::cout << MagnRaw_x << "\t" << MagnRaw_y << "\t" << MagnRaw_z << std::endl;

	double mRes;
	if(_Mscale == MFS_1300mG)
		mRes = 2.6/32768.0;
	else if(_Mscale == MFS_1900mG)
		mRes = 3.8/32768.0;
	else if(_Mscale == MFS_2500mG)
		mRes = 5.0/32768.0;
	else if(_Mscale == MFS_4000mG)
		mRes = 8.0/32768.0;
	else if(_Mscale == MFS_4700mG)
		mRes = 9.4/32768.0;
	else if(_Mscale == MFS_5600mG)
		mRes = 11.2/32768.0;
	else
		mRes = 16.2/32768.0;

	mx = (double)MagnRaw_x * mRes;
	my = (double)MagnRaw_y * mRes;
	mz = (double)MagnRaw_z * mRes;

	
}

/**
*@brief 計測した温度取得
* @return 温度
*/
double LSM303DLHC::getTempData()
{
	uint8_t Buf[2];
	readByte(_Magnaddr,TEMP_OUT_H_M,1,Buf);

	short Temp = Buf[0] << 8;

	readByte(_Magnaddr,TEMP_OUT_L_M,1,Buf);

	Temp = Temp | Buf[0];


	
	
	
	
	return (double)Temp/8.;
}

/**
*@brief 特定レジスタに書き込む
* @param Address I2Cアドレス(SPI通信の場合はセンサの判別に利用するのでアドレスのデフォルト値を入力)
* @param Register レジスタ
* @param Data 書き込むデータ
*/
void LSM303DLHC::writeByte(uint8_t Address, uint8_t Register, uint8_t Data) {

	_smf->sem_lock();
	_i2c->address(Address);
	
	_i2c->writeReg(Register, Data);
	
	_smf->sem_unlock();

  	
}

/**
*@brief 特定レジスタに書き込んで値を読み込む
* @param Address I2Cアドレス(SPI通信の場合はセンサの判別に利用するのでアドレスのデフォルト値を入力)
* @param Register レジスタ
* @param Nbytes 読み込むデータの長さ
* @param Data 読み込んだデータ
*/
void LSM303DLHC::readByte(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data) {
	
	_smf->sem_lock();

	_i2c->address(Address);
	_i2c->writeByte(Register);
	
	
	_i2c->read(Data,Nbytes);
	
	_smf->sem_unlock();
}