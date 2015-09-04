/*!
 * @file  ADT7410.h
 * @brief ���x�Z���TADT7410�̒ʐM�֘A�̃N���X
 *
 */

#ifndef ADT7410_H
#define ADT7410_H

#include <stdio.h>
#include <mraa.hpp>


#include "i2c_smf.h"


 
/**
 * @class ADT7410
*@brief ���x�Z���TADT7410�̒ʐM�֘A�̃N���X
*/
class ADT7410
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param i2c I2C����I�u�W�F�N�g
	* @param smf �Z�}�t�H����I�u�W�F�N�g
	* @param addr I2C�A�h���X
	*/
	ADT7410(mraa::I2c *i2c, i2c_smf *smf, uint8_t addr = 0x48);
	/**
	*@brief �f�X�g���N�^
	*/
	~ADT7410();
	/**
	*@brief �A�h���X�Đݒ�
	* @param addr I2C�A�h���X
	*/
	void setAddr(uint8_t addr);
	/**
	*@brief ���x�擾
	* @return ���x
	*/
	float getTempData();


	
	
	
	

	
private:

	uint8_t _addr;
	
	mraa::I2c *_i2c;

	i2c_smf *_smf;
};





#endif