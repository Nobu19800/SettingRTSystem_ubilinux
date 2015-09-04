/*!
 * @file  MCP3208.cpp
 * @brief ADコンバータMCP3208の通信関連のクラス
 *
 */


#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <mraa.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include "MCP3208.h"

/**
*@brief ADコンバータMCP3208の通信関連のクラスのコンストラクタ
* @param response 初期化成功でMRAA_SUCCESS、それ以外は失敗
* @param spi SPI操作オブジェクト
* @param smf セマフォ操作オブジェクト
* @param cs_pin デジタルピン番号(MCP3208のチップセレクトピンに接続)
*/
MCP3208::MCP3208(mraa_result_t &response, mraa::Spi *spi, i2c_smf *smf, int cs_pin) {
	_spi = spi;
	_smf = smf;

	m_cs_pin = cs_pin;
	cs = new mraa::Gpio(cs_pin);
	response = cs->dir(mraa::DIR_OUT);

	if (response != MRAA_SUCCESS) {
        	mraa::printError(response);
        	return;
    	}
	cs->write(1);
	response = MRAA_SUCCESS;
}

/**
*@brief ADコンバータMCP3208の通信関連のクラスのデストラクタ
*/
MCP3208::~MCP3208() {
	if(cs)
	{
		cs->write(0);
		delete cs;
	}
}

/**
*@brief ピン番号再設定
* @param cs_pin デジタルピン番号(MCP3208のチップセレクトピンに接続)
* @return 初期化成功でMRAA_SUCCESS、それ以外は失敗
*/
mraa_result_t MCP3208::setPinNum(int cs_pin) {
	if(m_cs_pin != cs_pin)
	{
		if(cs)
		{
			cs->write(0);
			delete cs;
		}
		cs = new mraa::Gpio(cs_pin);
		mraa_result_t response = cs->dir(mraa::DIR_OUT);
		
		if (response != MRAA_SUCCESS) {
	        	cs = NULL;
	        	return MRAA_ERROR_UNSPECIFIED;
	    	}
	}
	m_cs_pin = cs_pin;

	return MRAA_SUCCESS;
}

/**
*@brief 電圧値取得
* @param channel チャンネル
* @return 電圧値(0～4096)
*/
unsigned int MCP3208::getValue(int channel)
{
	uint8_t *recv;
	uint8_t data[3];
	data[0] = (channel & 0x04)? 0x07: 0x06;
	data[1] = (channel & 0x03) << 6;
	data[2] = 0;

	_smf->sem_lock();
	cs->write(0);
	recv = _spi->write(data,3);
	cs->write(1);
	_smf->sem_unlock();

	unsigned int ans = ((recv[1] & 0x0f) << 8) | recv[2];

	return ans;

}