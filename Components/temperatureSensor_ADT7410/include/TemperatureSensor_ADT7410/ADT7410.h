/*!
 * @file  ADT7410.h
 * @brief 温度センサADT7410の通信関連のクラス
 *
 */

#ifndef ADT7410_H
#define ADT7410_H

#include <stdio.h>
#include <mraa.hpp>


#include "i2c_smf.h"


 
/**
 * @class ADT7410
*@brief 温度センサADT7410の通信関連のクラス
*/
class ADT7410
{
public:
	/**
	*@brief コンストラクタ
	* @param i2c I2C操作オブジェクト
	* @param smf セマフォ操作オブジェクト
	* @param addr I2Cアドレス
	*/
	ADT7410(mraa::I2c *i2c, i2c_smf *smf, uint8_t addr = 0x48);
	/**
	*@brief デストラクタ
	*/
	~ADT7410();
	/**
	*@brief アドレス再設定
	* @param addr I2Cアドレス
	*/
	void setAddr(uint8_t addr);
	/**
	*@brief 温度取得
	* @return 温度
	*/
	float getTempData();


	
	
	
	

	
private:

	uint8_t _addr;
	
	mraa::I2c *_i2c;

	i2c_smf *_smf;
};





#endif