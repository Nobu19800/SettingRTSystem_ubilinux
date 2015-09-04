/*!
 * @file  L3GD20_I2C.h
 * @brief ジャイロセンサL3GD20のI2C通信関連のクラス
 *
 */

#ifndef L3GD20_I2C_H
#define L3GD20_I2C_H

#include <stdio.h>
#include <mraa.hpp>


#include "L3GD20.h"



/**
 * @class L3GD20_I2C
*@brief ジャイロセンサL3GD20のI2C通信関連のクラス
*/
class L3GD20_I2C : public L3GD20
{
public:
	/**
	*@brief コンストラクタ
	* @param response 初期化成功でMRAA_SUCCESS、それ以外は失敗
	* @param i2c I2C操作オブジェクト
	* @param smf セマフォ操作オブジェクト
	* @param addr I2Cアドレス
	* @param scale スケール
	* @param r IIRフィルタの係数
	*/
	L3GD20_I2C(mraa_result_t &response, mraa::I2c *i2c, i2c_smf *smf, uint8_t addr = 0x6a, uint8_t scale = 0, double r = 0.2);
	/**
	*@brief デストラクタ
	*/
	~L3GD20_I2C();
	
private:
	
	//int _i2channel;
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