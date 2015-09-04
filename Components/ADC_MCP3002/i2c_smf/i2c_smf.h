/*!
 * @file  i2c_smf.h
 * @brief �Z�}�t�H����̃N���X
 *
 */

#ifndef i2c_smf_H
#define i2c_smf_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>




/**
 * @class i2c_smf
*@brief �Z�}�t�H����̃N���X
*/
class i2c_smf
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param name �t�@�C����
	* @param val �Z�}�t�H�̒l
	*/
	i2c_smf(char *name = "/tmp/edisoni2csmf", int val = 1);
	/**
	*@brief �f�X�g���N�^
	*/
	~i2c_smf();
	/**
	*@brief �Z�}�t�H�擾
	* @param path �t�@�C����
	* @param val �Z�}�t�H�̒l
	* @return ID
	*/
	int sem_get(char *path, int val = 1);
	/**
	*@brief �Z�}�t�H�����b�N
	* @return ������1
	*/
	int sem_lock();
	/**
	*@brief �Z�}�t�H���A�����b�N
	* @return ������1
	*/
	int sem_unlock();
	/**
	*@brief �Z�}�t�H�̒l���擾
	* @return �Z�}�t�H�̒l
	*/
	int sem_ctl();
	int sid;
private:
	
};





#endif
