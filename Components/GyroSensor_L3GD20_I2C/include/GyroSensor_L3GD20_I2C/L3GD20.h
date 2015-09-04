/*!
 * @file  L3GD20.h
 * 定数名はhttps://github.com/adafruit/Adafruit_L3GD20/blob/master/Adafruit_L3GD20.h(BSDライセンス)から引用
 * @brief ジャイロセンサL3GD20の通信関連のクラス
 *
 */


#ifndef L3GD20_H
#define L3GD20_H

#include <stdio.h>
#include <mraa.hpp>


#include "i2c_smf.h"


 
/**
 * @class L3GD20
*@brief ジャイロセンサL3GD20の通信関連のクラス
*/
class L3GD20
{
public:
	/**
	*@brief コンストラクタ
	* @param smf セマフォ操作オブジェクト
	* @param addr アドレス(SPI通信の場合はデフォルトのI2Cアドレスを指定しておく)
	* @param scale スケール
	* @param r IIRフィルタの係数
	*/
	L3GD20(i2c_smf *smf, uint8_t addr = 0x6a, uint8_t scale = 0, double r = 0.2);
	/**
	*@brief デストラクタ
	*/
	virtual ~L3GD20();
	/**
	*@brief センサの存在確認
	* @return 存在する場合true、存在しない場合false
	*/
	virtual bool sensor_Exist();
	/**
	*@brief 初期化
	*/
	virtual void reset(void);
	/**
	*@brief 計測した角速度取得
	* @param avx 角速度(X)
	* @param avy 角速度(Y)
	* @param avz 角速度(Z)
	*/
	virtual void getGyroData(double &avx, double &avy, double &avz);
	/**
	*@brief 計測した角速度取得(オフセット有り)
	* @param avx 角速度(X)
	* @param avy 角速度(Y)
	* @param avz 角速度(Z)
	*/
	virtual void getGyro(double &avx, double &avy, double &avz);
	/**
	*@brief アドレス再設定
	* @param addr I2Cアドレス
	* @return 成功でMRAA_SUCCESS、それ以外は失敗
	*/
	virtual mraa_result_t setAddr(uint8_t addr = 0x6a);
	/**
	*@brief センサスケール再設定
	* @param scale スケール
	*/
	virtual void setScale(uint8_t scale = 0);
	/**
	*@brief フィルタ係数再設定
	* @param r 係数
	*/
	virtual void setCoefficient(double r = 0.2);

	
	
	
	
	/**
	*@brief スケールを反映
	* @param scale スケール
	*/
	virtual void setRange(uint8_t scale);
	
	
	
	enum regAddr
	    {
	       WHO_AM_I       = 0x0F,

	       CTRL1          = 0x20, 
	       CTRL_REG1      = 0x20, 
	       CTRL2          = 0x21, 
	       CTRL_REG2      = 0x21, 
	       CTRL3          = 0x22, 
	       CTRL_REG3      = 0x22, 
	       CTRL4          = 0x23, 
	       CTRL_REG4      = 0x23, 
	       CTRL5          = 0x24, 
	       CTRL_REG5      = 0x24, 
	       REFERENCE      = 0x25,
	       OUT_TEMP       = 0x26,
	       STATUS         = 0x27, 
	       STATUS_REG     = 0x27, 

	       OUT_X_L        = 0x28,
	       OUT_X_H        = 0x29,
	       OUT_Y_L        = 0x2A,
	       OUT_Y_H        = 0x2B,
	       OUT_Z_L        = 0x2C,
	       OUT_Z_H        = 0x2D,

	       FIFO_CTRL      = 0x2E, 
	       FIFO_CTRL_REG  = 0x2E, 
	       FIFO_SRC       = 0x2F, 
	       FIFO_SRC_REG   = 0x2F, 

	       IG_CFG         = 0x30, 
	       INT1_CFG       = 0x30, 
	       IG_SRC         = 0x31, 
	       INT1_SRC       = 0x31, 
	       IG_THS_XH      = 0x32, 
	       INT1_THS_XH    = 0x32, 
	       IG_THS_XL      = 0x33, 
	       INT1_THS_XL    = 0x33, 
	       IG_THS_YH      = 0x34, 
	       INT1_THS_YH    = 0x34, 
	       IG_THS_YL      = 0x35, 
	       INT1_THS_YL    = 0x35, 
	       IG_THS_ZH      = 0x36, 
	       INT1_THS_ZH    = 0x36, 
	       IG_THS_ZL      = 0x37, 
	       INT1_THS_ZL    = 0x37, 
	       IG_DURATION    = 0x38, 
	       INT1_DURATION  = 0x38, 

	       LOW_ODR        = 0x39
	    };

	enum Gscale {
	  Range_250dps = 0,
	  Range_500dps,
	  Range_2000dps
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

	uint8_t _addr;

	double _r;
	double lastX, lastY, lastZ;
	
	
	
	
	uint8_t _scale;
	

	i2c_smf *_smf;
};





#endif