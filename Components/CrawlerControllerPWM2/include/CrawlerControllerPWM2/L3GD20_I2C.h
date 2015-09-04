/*!
 * @file  L3GD20_I2C.h
 * @brief �W���C���Z���TL3GD20��I2C�ʐM�֘A�̃N���X
 *
 */

#ifndef L3GD20_I2C_H
#define L3GD20_I2C_H

#include <stdio.h>
#include <mraa.hpp>


#include "L3GD20.h"



/**
 * @class L3GD20_I2C
*@brief �W���C���Z���TL3GD20��I2C�ʐM�֘A�̃N���X
*/
class L3GD20_I2C : public L3GD20
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param response ������������MRAA_SUCCESS�A����ȊO�͎��s
	* @param i2c I2C����I�u�W�F�N�g
	* @param smf �Z�}�t�H����I�u�W�F�N�g
	* @param addr I2C�A�h���X
	* @param scale �X�P�[��
	* @param r IIR�t�B���^�̌W��
	*/
	L3GD20_I2C(mraa_result_t &response, mraa::I2c *i2c, i2c_smf *smf, uint8_t addr = 0x6a, uint8_t scale = 0, double r = 0.2);
	/**
	*@brief �f�X�g���N�^
	*/
	~L3GD20_I2C();
	
private:
	
	//int _i2channel;
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