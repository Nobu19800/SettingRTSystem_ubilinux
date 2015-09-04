/*!
 * @file  MCP3208.h
 * @brief ADコンバータMCP3208の通信関連のクラス
 *
 */

#ifndef MCP3208_H
#define MCP3208_H

#include <stdio.h>
#include <mraa.hpp>


#include "i2c_smf.h"


 
/**
 * @class MCP3208
*@brief ADコンバータMCP3208の通信関連のクラス
*/
class MCP3208
{
public:
	/**
	*@brief コンストラクタ
	* @param response 初期化成功でMRAA_SUCCESS、それ以外は失敗
	* @param spi SPI操作オブジェクト
	* @param smf セマフォ操作オブジェクト
	* @param cs_pin デジタルピン番号(MCP3208のチップセレクトピンに接続)
	*/
	MCP3208(mraa_result_t &response, mraa::Spi *spi, i2c_smf *smf, int cs_pin=4);
	/**
	*@brief デストラクタ
	*/
	~MCP3208();
	/**
	*@brief ピン番号再設定
	* @param cs_pin デジタルピン番号(MCP3208のチップセレクトピンに接続)
	* @return 初期化成功でMRAA_SUCCESS、それ以外は失敗
	*/
	mraa_result_t setPinNum(int pin=4);
	/**
	*@brief 電圧値取得
	* @param channel チャンネル
	* @return 電圧値(0～4096)
	*/
	unsigned int getValue(int channel);
private:
	
	mraa::Spi *_spi;
	mraa::Gpio* cs;
	int m_cs_pin;

	i2c_smf *_smf;
};





#endif