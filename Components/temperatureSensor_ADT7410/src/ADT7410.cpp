#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <mraa.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include "ADT7410.h"


/**
*@brief 温度センサADT7410の通信関連のクラスのコンストラクタ
* @param i2c I2C操作オブジェクト
* @param smf セマフォ操作オブジェクト
* @param addr I2Cアドレス
*/
ADT7410::ADT7410(mraa::I2c *i2c, i2c_smf *smf, uint8_t addr) {
	_i2c = i2c;

	
	
	
	_addr = addr;
	

	_smf = smf;

}


/**
*@brief 温度センサADT7410の通信関連のクラスのデストラクタ
*/
ADT7410::~ADT7410() {
	//delete _smf;
}

/**
*@brief アドレス再設定
* @param addr I2Cアドレス
*/
void ADT7410::setAddr(uint8_t addr)
{
	_addr = addr;
}

/**
*@brief 温度取得
* @return 温度
*/
float ADT7410::getTempData() {


	_smf->sem_lock();


	_i2c->address(_addr);
	uint8_t v[2];
	v[0] = 0;
	v[1] = 0;
	_i2c->read(v, 2);
	uint16_t val = (uint16_t)v[0] << 8;
	val |= v[1];
	val >>= 3;
	int ival = (int)val;
	if(val & (0x8000 >> 3)) { 
		ival = ival  - 8192; 
	}

	float tmp = (float)ival / 16.0;
	

	_smf->sem_unlock();
	
	return tmp;
}



