/*!
 * @file  LSM9DS0_I2C.h
 * @brief 9���Z���TLSM9DS0��I2C�ʐM�֘A�̃N���X
 *
 */

#ifndef LSM9DS0_I2C_H
#define LSM9DS0_I2C_H


#include "LSM9DS0.h"
 
/**
 * @class LSM9DS0_I2C
*@brief 9���Z���TLSM9DS0��I2C�ʐM�֘A�̃N���X
*/
class LSM9DS0_I2C : public LSM9DS0
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param response ������������MRAA_SUCCESS�A����ȊO�͎��s
	* @param i2c I2C����I�u�W�F�N�g
	* @param smf �Z�}�t�H����I�u�W�F�N�g
	* @param AccaMagaddr �����x�A�n���C�Z���T��I2C�A�h���X
	* @param Gyroaddr �W���C���Z���T��I2C�A�h���X
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
	LSM9DS0_I2C(mraa_result_t &response, mraa::I2c *i2c, i2c_smf *smf, uint8_t AccaMagaddr = LSM9DS0_ADDRESS_ACCELMAG, uint8_t Gyroaddr = LSM9DS0_ADDRESS_GYRO, uint8_t Accscale = 0x03, uint8_t Magnscale = 0x02, uint8_t GyroScale = 0x01, int mx_offset = 420, int my_offset = -455, int mz_offset = -155,  double ar = 0.2, double mr = 0.2, double gr = 0.2);
	/**
	*@brief �f�X�g���N�^
	*/
	~LSM9DS0_I2C();
	
private:
	
	
	/**
	*@brief I2C�œ��背�W�X�^�ɏ�������Œl��ǂݍ���
	* @param Address I2C�A�h���X
	* @param Register ���W�X�^
	* @param Nbytes �ǂݍ��ރf�[�^�̒���
	* @param Data �ǂݍ��񂾃f�[�^
	*/
	void readByte(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data);

	/**
	*@brief I2C�œ��背�W�X�^�ɏ�������
	* @param Address I2C�A�h���X
	* @param Register ���W�X�^
	* @param Data �������ރf�[�^
	*/
	void writeByte(uint8_t Address, uint8_t Register, uint8_t Data);
	

	mraa::I2c *_i2c;
	
};





#endif