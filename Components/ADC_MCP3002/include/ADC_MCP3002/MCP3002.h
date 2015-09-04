/*!
 * @file  MCP3002.h
 * @brief ADコンバータMCP3002の通信関連のクラス
 *
 */

#ifndef MCP3002_H
#define MCP3002_H

#include <stdio.h>
#include <mraa.hpp>


#include "i2c_smf.h"


 
/**
 * @class MCP3002
*@brief ADコンバータMCP3208の通信関連のクラス
*/
class MCP3002
{
public:
	/**
	*@brief コンストラクタ
	* @param response 初期化成功でMRAA_SUCCESS、それ以外は失敗
	* @param spi SPI操作オブジェクト
	* @param smf セマフォ操作オブジェクト
	* @param cs_pin デジタルピン番号(MCP3002のチップセレクトピンに接続)
	*/
	MCP3002(mraa_result_t &response, mraa::Spi *spi, i2c_smf *smf, int cs_pin=4);
	/**
	*@brief デストラクタ
	*/
	~MCP3002();
	/**
	*@brief ピン番号再設定
	* @param cs_pin デジタルピン番号(MCP3002のチップセレクトピンに接続)
	* @return 初期化成功でMRAA_SUCCESS、それ以外は失敗
	*/
	mraa_result_t setPinNum(int pin=4);
	/**
	*@brief 電圧値取得
	* @param channel チャンネル
	* @return 電圧値(0～1024)
	*/
	unsigned int getValue(int channel);
private:
	
	mraa::Spi *_spi;
	mraa::Gpio* cs;
	int m_cs_pin;

	i2c_smf *_smf;
};





#endif