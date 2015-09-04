/*!
 * @file  MCP3002.cpp
 * @brief ADコンバータMCP3002の通信関連のクラス
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
#include "MCP3002.h"

/**
*@brief ADコンバータMCP3208の通信関連のクラスのコンストラクタ
* @param response 初期化成功でMRAA_SUCCESS、それ以外は失敗
* @param spi SPI操作オブジェクト
* @param smf セマフォ操作オブジェクト
* @param cs_pin デジタルピン番号(MCP3002のチップセレクトピンに接続)
*/
MCP3002::MCP3002(mraa_result_t &response, mraa::Spi *spi, i2c_smf *smf, int cs_pin) {
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
MCP3002::~MCP3002() {
	if(cs)
	{
		cs->write(0);
		delete cs;
	}
}

/**
*@brief ピン番号再設定
* @param cs_pin デジタルピン番号(MCP3002のチップセレクトピンに接続)
* @return 初期化成功でMRAA_SUCCESS、それ以外は失敗
*/
mraa_result_t MCP3002::setPinNum(int cs_pin) {
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
* @return 電圧値(0～1024)
*/
unsigned int MCP3002::getValue(int channel)
{
	uint8_t *recv;
	uint8_t data[2];
	if(channel == 0)
	{
		data[0] = 0x68;
	}
	else
	{
		data[0] = 0x78;
	}
	data[1] = 0x00;

	_smf->sem_lock();
	cs->write(0);
	recv = _spi->write(data,2);
	cs->write(1);
	_smf->sem_unlock();

	unsigned int ans = ((recv[0] << 8) + recv[1]) & 0x03FF;

	return ans;

}