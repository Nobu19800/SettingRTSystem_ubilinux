/*!
 * @file  LSM9DS0_I2C.h
 * @brief 9軸センサLSM9DS0のI2C通信関連のクラス
 *
 */

#ifndef LSM9DS0_I2C_H
#define LSM9DS0_I2C_H


#include "LSM9DS0.h"
 
/**
 * @class LSM9DS0_I2C
*@brief 9軸センサLSM9DS0のI2C通信関連のクラス
*/
class LSM9DS0_I2C : public LSM9DS0
{
public:
	/**
	*@brief コンストラクタ
	* @param response 初期化成功でMRAA_SUCCESS、それ以外は失敗
	* @param i2c I2C操作オブジェクト
	* @param smf セマフォ操作オブジェクト
	* @param AccaMagaddr 加速度、地磁気センサのI2Cアドレス
	* @param Gyroaddr ジャイロセンサのI2Cアドレス
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
	LSM9DS0_I2C(mraa_result_t &response, mraa::I2c *i2c, i2c_smf *smf, uint8_t AccaMagaddr = LSM9DS0_ADDRESS_ACCELMAG, uint8_t Gyroaddr = LSM9DS0_ADDRESS_GYRO, uint8_t Accscale = 0x03, uint8_t Magnscale = 0x02, uint8_t GyroScale = 0x01, int mx_offset = 420, int my_offset = -455, int mz_offset = -155,  double ar = 0.2, double mr = 0.2, double gr = 0.2);
	/**
	*@brief デストラクタ
	*/
	~LSM9DS0_I2C();
	
private:
	
	
	/**
	*@brief I2Cで特定レジスタに書き込んで値を読み込む
	* @param Address I2Cアドレス
	* @param Register レジスタ
	* @param Nbytes 読み込むデータの長さ
	* @param Data 読み込んだデータ
	*/
	void readByte(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data);

	/**
	*@brief I2Cで特定レジスタに書き込む
	* @param Address I2Cアドレス
	* @param Register レジスタ
	* @param Data 書き込むデータ
	*/
	void writeByte(uint8_t Address, uint8_t Register, uint8_t Data);
	

	mraa::I2c *_i2c;
	
};





#endif