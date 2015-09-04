/*!
 * @file  LSM9DS0.h
 * 定数名はhttps://github.com/adafruit/Adafruit_LSM9DS0_Library/blob/master/Adafruit_LSM9DS0.h(BSDライセンス)から引用しました。
 * @brief 9軸センサLSM9DS0の通信関連のクラス
 *
 */

#ifndef LSM9DS0_H
#define LSM9DS0_H

#include <stdio.h>
#include <mraa.hpp>


#include "i2c_smf.h"


#define LSM9DS0_ADDRESS_ACCELMAG	0x1D
#define LSM9DS0_ADDRESS_GYRO	0x6B
#define LSM9DS0_XM_ID	0x49
#define LSM9DS0_G_ID	0xD4



#define LSM9DS0_ACCEL_MG_LSB_2G	0.061
#define LSM9DS0_ACCEL_MG_LSB_4G	0.122
#define LSM9DS0_ACCEL_MG_LSB_6G	0.183
#define LSM9DS0_ACCEL_MG_LSB_8G 0.244
#define LSM9DS0_ACCEL_MG_LSB_16G 0.732


#define LSM9DS0_MAG_MGAUSS_2GAUSS	0.08
#define LSM9DS0_MAG_MGAUSS_4GAUSS	0.16
#define LSM9DS0_MAG_MGAUSS_8GAUSS	0.32
#define LSM9DS0_MAG_MGAUSS_12GAUSS	0.48


#define LSM9DS0_GYRO_DPS_DIGIT_245DPS	0.00875
#define LSM9DS0_GYRO_DPS_DIGIT_500DPS	0.01750
#define LSM9DS0_GYRO_DPS_DIGIT_2000DPS	0.07000


#define LSM9DS0_TEMP_LSB_DEGREE_CELSIUS	8
 

/**
 * @class LSM9DS0
*@brief 9軸センサLSM9DS0のI2C通信関連のクラス
*/
class LSM9DS0
{
public:
	/**
	*@brief コンストラクタ
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
	LSM9DS0(i2c_smf *smf, uint8_t AccaMagaddr = LSM9DS0_ADDRESS_ACCELMAG, uint8_t Gyroaddr = LSM9DS0_ADDRESS_GYRO, uint8_t Accscale = 0x03, uint8_t Magnscale = 0x02, uint8_t GyroScale = 0x01, int mx_offset = 420, int my_offset = -455, int mz_offset = -155,  double ar = 0.2, double mr = 0.2, double gr = 0.2);
	/**
	*@brief デストラクタ
	*/
	virtual ~LSM9DS0();
	/**
	*@brief 加速度、地磁気センサのI2Cアドレス再設定
	* @param AccaMagaddr I2Cアドレス
	* @return 成功でMRAA_SUCCESS、それ以外は失敗
	*/
	virtual mraa_result_t setAccMagAddr(uint8_t AccaMagaddr = LSM9DS0_ADDRESS_ACCELMAG);
	/**
	*@brief ジャイロセンサのI2Cアドレス再設定
	* @param Gyroaddr I2Cアドレス
	* @return 成功でMRAA_SUCCESS、それ以外は失敗
	*/
	virtual mraa_result_t setGyroAddr(uint8_t Gyroaddr = LSM9DS0_ADDRESS_GYRO);
	/**
	*@brief 加速度、地磁気センサの存在確認
	* @return 存在する場合true、存在しない場合false
	*/
	virtual bool AccMagSensor_Exist();
	/**
	*@brief ジャイロセンサの存在確認
	* @return 存在する場合true、存在しない場合false
	*/
	virtual bool GyroSensor_Exist();
	/**
	*@brief 加速度センサのフィルタ係数再設定
	* @param ar 係数
	*/
	virtual void setAccCoefficient(double ar = 0.2);
	/**
	*@brief 地磁気センサのフィルタ係数再設定
	* @param mr 係数
	*/
	virtual void setMagnCoefficient(double mr = 0.2);
	/**
	*@brief ジャイロセンサのフィルタ係数再設定
	* @param ar 係数
	*/
	virtual void setGyroCoefficient(double gr = 0.2);
	/**
	*@brief 加速度センサスケール再設定
	* @param Accscale スケール
	*/
	virtual void setAccScale(uint8_t Accscale = 0x03);
	/**
	*@brief 地磁気センサスケール再設定
	* @param Magnscale スケール
	*/
	virtual void setMagnScale(uint8_t Magnscale = 0x02);
	/**
	*@brief ジャイロセンサスケール再設定
	* @param GyroScale スケール
	*/
	virtual void setGyroScale(uint8_t GyroScale = 0x01);
	/**
	*@brief 地磁気センサのオフセット再設定
	* @param mx_offset オフセット(X)
	* @param my_offset オフセット(Y)
	* @param mz_offset オフセット(Z)
	*/
	virtual void setOffset(int mx_offset = 935, int my_offset = 320, int mz_offset = 730);
	/**
	*@brief 初期化
	*/
	virtual void reset(void);
	/**
	*@brief 計測した加速度取得
	* @param ax 加速度(X)
	* @param ay 加速度(Y)
	* @param az 加速度(Z)
	*/
	virtual void getAcc(double &ax, double &ay, double &az);
	/**
	*@brief 計測した地磁気取得
	* @param mx 地磁気(X)
	* @param my 地磁気(Y)
	* @param mz 地磁気(Z)
	*/
	virtual void getMagn(double &mx, double &my, double &mz);
	/**
	*@brief 計測した角速度取得
	* @param avx 角速度(X)
	* @param avy 角速度(Y)
	* @param avz 角速度(Z)
	*/
	virtual void getGyro(double &avx, double &avy, double &avz);
	/**
	*@brief 計測した温度取得(現在のところはgetTempDataと同じ)
	* @return 温度
	*/
	virtual double getTemp();
	/**
	*@brief 計測した加速度取得(オフセット有り)
	* @param ax 加速度(X)
	* @param ay 加速度(Y)
	* @param az 加速度(Z)
	*/
	virtual void getAccData(double &ax, double &ay, double &az);
	/**
	*@brief 計測した地磁気取得(オフセット有り)
	* @param mx 地磁気(X)
	* @param my 地磁気(Y)
	* @param mz 地磁気(Z)
	*/
	virtual void getMagnData(double &mx, double &my, double &mz);
	/**
	*@brief 計測した角速度取得(オフセット有り)
	* @param avx 角速度(X)
	* @param avy 角速度(Y)
	* @param avz 角速度(Z)
	*/
	virtual void getGyroData(double &avx, double &my, double &mz);
	/**
	*@brief 計測した温度取得
	* @return 温度
	*/
	virtual double getTempData();
	/**
	*@brief 姿勢を計算
	* @param rx ロール角
	* @param ry ピッチ角
	* @param rz ヨー角
	*/
	virtual void getOrientation(double &rx, double &ry, double &rz);

	/**
	*@brief 加速度センサのスケールを反映
	* @param scale スケール
	*/
	virtual void setAccRange(uint8_t scale);
	/**
	*@brief 地磁気センサのスケールを反映
	* @param scale スケール
	*/
	virtual void setMagnRange(uint8_t scale);
	/**
	*@brief ジャイロセンサのスケールを反映
	* @param scale スケール
	*/
	virtual void setGyroRange(uint8_t scale);
	
    enum lsm9ds0GyroRegisters_t
    {
      LSM9DS0_REGISTER_WHO_AM_I_G          = 0x0F,
      LSM9DS0_REGISTER_CTRL_REG1_G         = 0x20,
      LSM9DS0_REGISTER_CTRL_REG3_G         = 0x22,
      LSM9DS0_REGISTER_CTRL_REG4_G         = 0x23,
      LSM9DS0_REGISTER_OUT_X_L_G           = 0x28,
      LSM9DS0_REGISTER_OUT_X_H_G           = 0x29,
      LSM9DS0_REGISTER_OUT_Y_L_G           = 0x2A,
      LSM9DS0_REGISTER_OUT_Y_H_G           = 0x2B,
      LSM9DS0_REGISTER_OUT_Z_L_G           = 0x2C,
      LSM9DS0_REGISTER_OUT_Z_H_G           = 0x2D,
    };

    enum lsm9ds0MagAccelRegisters_t
    {
      LSM9DS0_REGISTER_TEMP_OUT_L_XM       = 0x05,
      LSM9DS0_REGISTER_TEMP_OUT_H_XM       = 0x06,
      LSM9DS0_REGISTER_STATUS_REG_M        = 0x07,
      LSM9DS0_REGISTER_OUT_X_L_M           = 0x08,
      LSM9DS0_REGISTER_OUT_X_H_M           = 0x09,
      LSM9DS0_REGISTER_OUT_Y_L_M           = 0x0A,
      LSM9DS0_REGISTER_OUT_Y_H_M           = 0x0B,
      LSM9DS0_REGISTER_OUT_Z_L_M           = 0x0C,
      LSM9DS0_REGISTER_OUT_Z_H_M           = 0x0D,
      LSM9DS0_REGISTER_WHO_AM_I_XM         = 0x0F,
      LSM9DS0_REGISTER_INT_CTRL_REG_M      = 0x12,
      LSM9DS0_REGISTER_INT_SRC_REG_M       = 0x13,
      LSM9DS0_REGISTER_CTRL_REG1_XM        = 0x20,
      LSM9DS0_REGISTER_CTRL_REG2_XM        = 0x21,
      LSM9DS0_REGISTER_CTRL_REG5_XM        = 0x24,
      LSM9DS0_REGISTER_CTRL_REG6_XM        = 0x25,
      LSM9DS0_REGISTER_CTRL_REG7_XM        = 0x26,
      LSM9DS0_REGISTER_OUT_X_L_A           = 0x28,
      LSM9DS0_REGISTER_OUT_X_H_A           = 0x29,
      LSM9DS0_REGISTER_OUT_Y_L_A           = 0x2A,
      LSM9DS0_REGISTER_OUT_Y_H_A           = 0x2B,
      LSM9DS0_REGISTER_OUT_Z_L_A           = 0x2C,
      LSM9DS0_REGISTER_OUT_Z_H_A           = 0x2D,
    };

	enum lsm9ds0AccelRange_t {
	  LSM9DS0_ACCELRANGE_2G = 0,
	  LSM9DS0_ACCELRANGE_4G,
	  LSM9DS0_ACCELRANGE_6G,
	  LSM9DS0_ACCELRANGE_8G,
	  LSM9DS0_ACCELRANGE_16G
	};

    enum lm9ds0AccelDataRate_t
    {
      LSM9DS0_ACCELDATARATE_POWERDOWN= 0,
      LSM9DS0_ACCELDATARATE_3_125HZ,
      LSM9DS0_ACCELDATARATE_6_25HZ,
      LSM9DS0_ACCELDATARATE_12_5HZ,
      LSM9DS0_ACCELDATARATE_25HZ,
      LSM9DS0_ACCELDATARATE_50HZ,
      LSM9DS0_ACCELDATARATE_100HZ,
      LSM9DS0_ACCELDATARATE_200HZ,
      LSM9DS0_ACCELDATARATE_400HZ,
      LSM9DS0_ACCELDATARATE_800HZ,
      LSM9DS0_ACCELDATARATE_1600HZ
    };

    enum lsm9ds0MagGain_t
    {
      LSM9DS0_MAGGAIN_2GAUSS = 1,
      LSM9DS0_MAGGAIN_4GAUSS,
      LSM9DS0_MAGGAIN_8GAUSS ,
      LSM9DS0_MAGGAIN_12GAUSS
    };
    
    enum lsm9ds0MagDataRate_t
    {
      LSM9DS0_MAGDATARATE_3_125HZ = 0,
      LSM9DS0_MAGDATARATE_6_25HZ,
      LSM9DS0_MAGDATARATE_12_5HZ,
      LSM9DS0_MAGDATARATE_25HZ,
      LSM9DS0_MAGDATARATE_50HZ,
      LSM9DS0_MAGDATARATE_100HZ  
    };

    enum lsm9ds0GyroScale_t
    {
      LSM9DS0_GYROSCALE_245DPS = 0,
      LSM9DS0_GYROSCALE_500DPS,
      LSM9DS0_GYROSCALE_2000DPS
    };

protected:
	
	//int _i2channel;
	/**
	*@brief 特定レジスタに書き込んで値を読み込む
	* @param Address I2Cアドレス(SPI通信の場合はセンサの判別に利用するのでアドレスのデフォルト値を入力)
	* @param Register レジスタ
	* @param Nbytes 読み込むデータの長さ
	* @param Data 読み込んだデータ
	*/
	virtual void readByte(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data);
	/**
	*@brief 特定レジスタに書き込む
	* @param Address I2Cアドレス(SPI通信の場合はセンサの判別に利用するのでアドレスのデフォルト値を入力)
	* @param Register レジスタ
	* @param Data 書き込むデータ
	*/
	virtual void writeByte(uint8_t Address, uint8_t Register, uint8_t Data);
	
	double _ar, _mr, _gr;
	double lastAX, lastAY, lastAZ;
	double lastMX, lastMY, lastMZ;
	double lastGX, lastGY, lastGZ;
	
	double lastTemp;
	
	uint8_t _Ascale;
	uint8_t _Mscale;
	uint8_t _Gscale;

	uint8_t _AccMagaddr;
	uint8_t _Gyroaddr;

	i2c_smf *_smf;

	int _mx_offset, _my_offset, _mz_offset;
	double avx_offset, avy_offset, avz_offset;
};





#endif