/*!
 * @file  LSM9DS0.h
 * �萔����https://github.com/adafruit/Adafruit_LSM9DS0_Library/blob/master/Adafruit_LSM9DS0.h(BSD���C�Z���X)������p���܂����B
 * @brief 9���Z���TLSM9DS0�̒ʐM�֘A�̃N���X
 *
 */

#ifndef LSM9DS0_H
#define LSM9DS0_H

#include <stdio.h>
#include <mraa.hpp>


#include "i2c_smf.h"


#define LSM9DS0_ADDRESS_ACCELMAG	0x1D
#define LSM9DS0_ADDRESS_GYRO	0x6B
#define LSM9DS0_XM_ID	0x49
#define LSM9DS0_G_ID	0xD4



#define LSM9DS0_ACCEL_MG_LSB_2G	0.061
#define LSM9DS0_ACCEL_MG_LSB_4G	0.122
#define LSM9DS0_ACCEL_MG_LSB_6G	0.183
#define LSM9DS0_ACCEL_MG_LSB_8G 0.244
#define LSM9DS0_ACCEL_MG_LSB_16G 0.732


#define LSM9DS0_MAG_MGAUSS_2GAUSS	0.08
#define LSM9DS0_MAG_MGAUSS_4GAUSS	0.16
#define LSM9DS0_MAG_MGAUSS_8GAUSS	0.32
#define LSM9DS0_MAG_MGAUSS_12GAUSS	0.48


#define LSM9DS0_GYRO_DPS_DIGIT_245DPS	0.00875
#define LSM9DS0_GYRO_DPS_DIGIT_500DPS	0.01750
#define LSM9DS0_GYRO_DPS_DIGIT_2000DPS	0.07000


#define LSM9DS0_TEMP_LSB_DEGREE_CELSIUS	8
 

/**
 * @class LSM9DS0
*@brief 9���Z���TLSM9DS0��I2C�ʐM�֘A�̃N���X
*/
class LSM9DS0
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param response ������������MRAA_SUCCESS�A����ȊO�͎��s
	* @param smf �Z�}�t�H����I�u�W�F�N�g
	* @param AccaMagaddr �����x�A�n���C�Z���T�̃A�h���X(SPI�ʐM�̏ꍇ�̓f�t�H���g��I2C�A�h���X���w�肵�Ă���)
	* @param Gyroaddr �W���C���Z���T�̃A�h���X(SPI�ʐM�̏ꍇ�̓f�t�H���g��I2C�A�h���X���w�肵�Ă���)
	* @param Accscale �����x�Z���T�̃X�P�[��
	* @param Magnscale �n���C�Z���T�̃X�P�[��
	* @param GyroScale �W���C���Z���T�̃X�P�[��
	* @param mx_offset �n���C�Z���T�̃I�t�Z�b�g(X)
	* @param my_offset �n���C�Z���T�̃I�t�Z�b�g(Y)
	* @param mz_offset �n���C�Z���T�̃I�t�Z�b�g(Z)
	* @param ar �����x�ւ�IIR�t�B���^�̌W��
	* @param mr �n���C�ւ�IIR�t�B���^�̌W��
	* @param gr �p���x�ւ�IIR�t�B���^�̌W��
	*/
	LSM9DS0(i2c_smf *smf, uint8_t AccaMagaddr = LSM9DS0_ADDRESS_ACCELMAG, uint8_t Gyroaddr = LSM9DS0_ADDRESS_GYRO, uint8_t Accscale = 0x03, uint8_t Magnscale = 0x02, uint8_t GyroScale = 0x01, int mx_offset = 420, int my_offset = -455, int mz_offset = -155,  double ar = 0.2, double mr = 0.2, double gr = 0.2);
	/**
	*@brief �f�X�g���N�^
	*/
	virtual ~LSM9DS0();
	/**
	*@brief �����x�A�n���C�Z���T��I2C�A�h���X�Đݒ�
	* @param AccaMagaddr I2C�A�h���X
	* @return ������MRAA_SUCCESS�A����ȊO�͎��s
	*/
	virtual mraa_result_t setAccMagAddr(uint8_t AccaMagaddr = LSM9DS0_ADDRESS_ACCELMAG);
	/**
	*@brief �W���C���Z���T��I2C�A�h���X�Đݒ�
	* @param Gyroaddr I2C�A�h���X
	* @return ������MRAA_SUCCESS�A����ȊO�͎��s
	*/
	virtual mraa_result_t setGyroAddr(uint8_t Gyroaddr = LSM9DS0_ADDRESS_GYRO);
	/**
	*@brief �����x�A�n���C�Z���T�̑��݊m�F
	* @return ���݂���ꍇtrue�A���݂��Ȃ��ꍇfalse
	*/
	virtual bool AccMagSensor_Exist();
	/**
	*@brief �W���C���Z���T�̑��݊m�F
	* @return ���݂���ꍇtrue�A���݂��Ȃ��ꍇfalse
	*/
	virtual bool GyroSensor_Exist();
	/**
	*@brief �����x�Z���T�̃t�B���^�W���Đݒ�
	* @param ar �W��
	*/
	virtual void setAccCoefficient(double ar = 0.2);
	/**
	*@brief �n���C�Z���T�̃t�B���^�W���Đݒ�
	* @param mr �W��
	*/
	virtual void setMagnCoefficient(double mr = 0.2);
	/**
	*@brief �W���C���Z���T�̃t�B���^�W���Đݒ�
	* @param ar �W��
	*/
	virtual void setGyroCoefficient(double gr = 0.2);
	/**
	*@brief �����x�Z���T�X�P�[���Đݒ�
	* @param Accscale �X�P�[��
	*/
	virtual void setAccScale(uint8_t Accscale = 0x03);
	/**
	*@brief �n���C�Z���T�X�P�[���Đݒ�
	* @param Magnscale �X�P�[��
	*/
	virtual void setMagnScale(uint8_t Magnscale = 0x02);
	/**
	*@brief �W���C���Z���T�X�P�[���Đݒ�
	* @param GyroScale �X�P�[��
	*/
	virtual void setGyroScale(uint8_t GyroScale = 0x01);
	/**
	*@brief �n���C�Z���T�̃I�t�Z�b�g�Đݒ�
	* @param mx_offset �I�t�Z�b�g(X)
	* @param my_offset �I�t�Z�b�g(Y)
	* @param mz_offset �I�t�Z�b�g(Z)
	*/
	virtual void setOffset(int mx_offset = 935, int my_offset = 320, int mz_offset = 730);
	/**
	*@brief ������
	*/
	virtual void reset(void);
	/**
	*@brief �v�����������x�擾
	* @param ax �����x(X)
	* @param ay �����x(Y)
	* @param az �����x(Z)
	*/
	virtual void getAcc(double &ax, double &ay, double &az);
	/**
	*@brief �v�������n���C�擾
	* @param mx �n���C(X)
	* @param my �n���C(Y)
	* @param mz �n���C(Z)
	*/
	virtual void getMagn(double &mx, double &my, double &mz);
	/**
	*@brief �v�������p���x�擾
	* @param avx �p���x(X)
	* @param avy �p���x(Y)
	* @param avz �p���x(Z)
	*/
	virtual void getGyro(double &avx, double &avy, double &avz);
	/**
	*@brief �v���������x�擾(���݂̂Ƃ����getTempData�Ɠ���)
	* @return ���x
	*/
	virtual double getTemp();
	/**
	*@brief �v�����������x�擾(�I�t�Z�b�g�L��)
	* @param ax �����x(X)
	* @param ay �����x(Y)
	* @param az �����x(Z)
	*/
	virtual void getAccData(double &ax, double &ay, double &az);
	/**
	*@brief �v�������n���C�擾(�I�t�Z�b�g�L��)
	* @param mx �n���C(X)
	* @param my �n���C(Y)
	* @param mz �n���C(Z)
	*/
	virtual void getMagnData(double &mx, double &my, double &mz);
	/**
	*@brief �v�������p���x�擾(�I�t�Z�b�g�L��)
	* @param avx �p���x(X)
	* @param avy �p���x(Y)
	* @param avz �p���x(Z)
	*/
	virtual void getGyroData(double &avx, double &my, double &mz);
	/**
	*@brief �v���������x�擾
	* @return ���x
	*/
	virtual double getTempData();
	/**
	*@brief �p�����v�Z
	* @param rx ���[���p
	* @param ry �s�b�`�p
	* @param rz ���[�p
	*/
	virtual void getOrientation(double &rx, double &ry, double &rz);

	/**
	*@brief �����x�Z���T�̃X�P�[���𔽉f
	* @param scale �X�P�[��
	*/
	virtual void setAccRange(uint8_t scale);
	/**
	*@brief �n���C�Z���T�̃X�P�[���𔽉f
	* @param scale �X�P�[��
	*/
	virtual void setMagnRange(uint8_t scale);
	/**
	*@brief �W���C���Z���T�̃X�P�[���𔽉f
	* @param scale �X�P�[��
	*/
	virtual void setGyroRange(uint8_t scale);
	
    enum lsm9ds0GyroRegisters_t
    {
      LSM9DS0_REGISTER_WHO_AM_I_G          = 0x0F,
      LSM9DS0_REGISTER_CTRL_REG1_G         = 0x20,
      LSM9DS0_REGISTER_CTRL_REG3_G         = 0x22,
      LSM9DS0_REGISTER_CTRL_REG4_G         = 0x23,
      LSM9DS0_REGISTER_OUT_X_L_G           = 0x28,
      LSM9DS0_REGISTER_OUT_X_H_G           = 0x29,
      LSM9DS0_REGISTER_OUT_Y_L_G           = 0x2A,
      LSM9DS0_REGISTER_OUT_Y_H_G           = 0x2B,
      LSM9DS0_REGISTER_OUT_Z_L_G           = 0x2C,
      LSM9DS0_REGISTER_OUT_Z_H_G           = 0x2D,
    };

    enum lsm9ds0MagAccelRegisters_t
    {
      LSM9DS0_REGISTER_TEMP_OUT_L_XM       = 0x05,
      LSM9DS0_REGISTER_TEMP_OUT_H_XM       = 0x06,
      LSM9DS0_REGISTER_STATUS_REG_M        = 0x07,
      LSM9DS0_REGISTER_OUT_X_L_M           = 0x08,
      LSM9DS0_REGISTER_OUT_X_H_M           = 0x09,
      LSM9DS0_REGISTER_OUT_Y_L_M           = 0x0A,
      LSM9DS0_REGISTER_OUT_Y_H_M           = 0x0B,
      LSM9DS0_REGISTER_OUT_Z_L_M           = 0x0C,
      LSM9DS0_REGISTER_OUT_Z_H_M           = 0x0D,
      LSM9DS0_REGISTER_WHO_AM_I_XM         = 0x0F,
      LSM9DS0_REGISTER_INT_CTRL_REG_M      = 0x12,
      LSM9DS0_REGISTER_INT_SRC_REG_M       = 0x13,
      LSM9DS0_REGISTER_CTRL_REG1_XM        = 0x20,
      LSM9DS0_REGISTER_CTRL_REG2_XM        = 0x21,
      LSM9DS0_REGISTER_CTRL_REG5_XM        = 0x24,
      LSM9DS0_REGISTER_CTRL_REG6_XM        = 0x25,
      LSM9DS0_REGISTER_CTRL_REG7_XM        = 0x26,
      LSM9DS0_REGISTER_OUT_X_L_A           = 0x28,
      LSM9DS0_REGISTER_OUT_X_H_A           = 0x29,
      LSM9DS0_REGISTER_OUT_Y_L_A           = 0x2A,
      LSM9DS0_REGISTER_OUT_Y_H_A           = 0x2B,
      LSM9DS0_REGISTER_OUT_Z_L_A           = 0x2C,
      LSM9DS0_REGISTER_OUT_Z_H_A           = 0x2D,
    };

	enum lsm9ds0AccelRange_t {
	  LSM9DS0_ACCELRANGE_2G = 0,
	  LSM9DS0_ACCELRANGE_4G,
	  LSM9DS0_ACCELRANGE_6G,
	  LSM9DS0_ACCELRANGE_8G,
	  LSM9DS0_ACCELRANGE_16G
	};

    enum lm9ds0AccelDataRate_t
    {
      LSM9DS0_ACCELDATARATE_POWERDOWN= 0,
      LSM9DS0_ACCELDATARATE_3_125HZ,
      LSM9DS0_ACCELDATARATE_6_25HZ,
      LSM9DS0_ACCELDATARATE_12_5HZ,
      LSM9DS0_ACCELDATARATE_25HZ,
      LSM9DS0_ACCELDATARATE_50HZ,
      LSM9DS0_ACCELDATARATE_100HZ,
      LSM9DS0_ACCELDATARATE_200HZ,
      LSM9DS0_ACCELDATARATE_400HZ,
      LSM9DS0_ACCELDATARATE_800HZ,
      LSM9DS0_ACCELDATARATE_1600HZ
    };

    enum lsm9ds0MagGain_t
    {
      LSM9DS0_MAGGAIN_2GAUSS = 1,
      LSM9DS0_MAGGAIN_4GAUSS,
      LSM9DS0_MAGGAIN_8GAUSS ,
      LSM9DS0_MAGGAIN_12GAUSS
    };
    
    enum lsm9ds0MagDataRate_t
    {
      LSM9DS0_MAGDATARATE_3_125HZ = 0,
      LSM9DS0_MAGDATARATE_6_25HZ,
      LSM9DS0_MAGDATARATE_12_5HZ,
      LSM9DS0_MAGDATARATE_25HZ,
      LSM9DS0_MAGDATARATE_50HZ,
      LSM9DS0_MAGDATARATE_100HZ  
    };

    enum lsm9ds0GyroScale_t
    {
      LSM9DS0_GYROSCALE_245DPS = 0,
      LSM9DS0_GYROSCALE_500DPS,
      LSM9DS0_GYROSCALE_2000DPS
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
	
	double _ar, _mr, _gr;
	double lastAX, lastAY, lastAZ;
	double lastMX, lastMY, lastMZ;
	double lastGX, lastGY, lastGZ;
	
	double lastTemp;
	
	uint8_t _Ascale;
	uint8_t _Mscale;
	uint8_t _Gscale;

	uint8_t _AccMagaddr;
	uint8_t _Gyroaddr;

	i2c_smf *_smf;

	int _mx_offset, _my_offset, _mz_offset;
	double avx_offset, avy_offset, avz_offset;
};





#endif