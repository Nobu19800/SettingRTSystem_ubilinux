/*!
 * @file  L3GD20.h
 * �萔����https://github.com/adafruit/Adafruit_L3GD20/blob/master/Adafruit_L3GD20.h(BSD���C�Z���X)������p
 * @brief �W���C���Z���TL3GD20�̒ʐM�֘A�̃N���X
 *
 */


#ifndef L3GD20_H
#define L3GD20_H

#include <stdio.h>
#include <mraa.hpp>


#include "i2c_smf.h"


 
/**
 * @class L3GD20
*@brief �W���C���Z���TL3GD20�̒ʐM�֘A�̃N���X
*/
class L3GD20
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param smf �Z�}�t�H����I�u�W�F�N�g
	* @param addr �A�h���X(SPI�ʐM�̏ꍇ�̓f�t�H���g��I2C�A�h���X���w�肵�Ă���)
	* @param scale �X�P�[��
	* @param r IIR�t�B���^�̌W��
	*/
	L3GD20(i2c_smf *smf, uint8_t addr = 0x6a, uint8_t scale = 0, double r = 0.2);
	/**
	*@brief �f�X�g���N�^
	*/
	virtual ~L3GD20();
	/**
	*@brief �Z���T�̑��݊m�F
	* @return ���݂���ꍇtrue�A���݂��Ȃ��ꍇfalse
	*/
	virtual bool sensor_Exist();
	/**
	*@brief ������
	*/
	virtual void reset(void);
	/**
	*@brief �v�������p���x�擾
	* @param avx �p���x(X)
	* @param avy �p���x(Y)
	* @param avz �p���x(Z)
	*/
	virtual void getGyroData(double &avx, double &avy, double &avz);
	/**
	*@brief �v�������p���x�擾(�I�t�Z�b�g�L��)
	* @param avx �p���x(X)
	* @param avy �p���x(Y)
	* @param avz �p���x(Z)
	*/
	virtual void getGyro(double &avx, double &avy, double &avz);
	/**
	*@brief �A�h���X�Đݒ�
	* @param addr I2C�A�h���X
	* @return ������MRAA_SUCCESS�A����ȊO�͎��s
	*/
	virtual mraa_result_t setAddr(uint8_t addr = 0x6a);
	/**
	*@brief �Z���T�X�P�[���Đݒ�
	* @param scale �X�P�[��
	*/
	virtual void setScale(uint8_t scale = 0);
	/**
	*@brief �t�B���^�W���Đݒ�
	* @param r �W��
	*/
	virtual void setCoefficient(double r = 0.2);

	
	
	
	
	/**
	*@brief �X�P�[���𔽉f
	* @param scale �X�P�[��
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
	*@brief ���背�W�X�^�ɏ�������Œl��ǂݍ���
	* @param Address I2C�A�h���X(SPI�ʐM�̏ꍇ�̓Z���T�̔��ʂɗ��p����̂ŃA�h���X�̃f�t�H���g�l�����)
	* @param Register ���W�X�^
	* @param Nbytes �ǂݍ��ރf�[�^�̒���
	* @param Data �ǂݍ��񂾃f�[�^
	*/
	virtual void readByte(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data);
	/**
	*@brief ���背�W�X�^�ɏ�������
	* @param Address I2C�A�h���X(SPI�ʐM�̏ꍇ�̓Z���T�̔��ʂɗ��p����̂ŃA�h���X�̃f�t�H���g�l�����)
	* @param Register ���W�X�^
	* @param Data �������ރf�[�^
	*/
	virtual void writeByte(uint8_t Address, uint8_t Register, uint8_t Data);

	uint8_t _addr;

	double _r;
	double lastX, lastY, lastZ;
	
	
	
	
	uint8_t _scale;
	

	i2c_smf *_smf;
};





#endif