/*!
 * @file  i2c_smf.cpp
 * @brief �Z�}�t�H����̃N���X
 *
 */

#include <iostream>



#include "i2c_smf.h"

union semun{
	int val;
	struct semid_ds *buf;
	ushort *array;
}c_arg;


/**
*@brief �Z�}�t�H����̃N���X�̃R���X�g���N�^
* @param name �t�@�C����
* @param val �Z�}�t�H�̒l
*/
i2c_smf::i2c_smf(char *name, int val)
{
	
	
	sid=sem_get(name, val);
	
	
}

/**
*@brief �Z�}�t�H����̃N���X�̃f�X�g���N�^
*/
i2c_smf::~i2c_smf()
{

}

/**
*@brief �Z�}�t�H�擾
* @param path �t�@�C����
* @param val �Z�}�t�H�̒l
* @return ID
*/
int i2c_smf::sem_get(char *path, int val)
{
	

	if((sid=semget(ftok(path,0),1,0666|IPC_CREAT))== -1){
		perror("semget");
		return(-1);
	}

	if(semctl(sid,0,GETVAL,c_arg)==0){
		c_arg.val=val;
		if(semctl(sid,0,SETVAL,c_arg)==-1){
			perror("semctl");
			return(-1);
		}
	}
	return(sid);
}

/**
*@brief �Z�}�t�H�����b�N
* @return ������1
*/
int i2c_smf::sem_lock()
{
	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=-1;
	sb.sem_flg=0;
	if(semop(sid,&sb,1)== -1){
		perror("semop");
		return(-1);
	}
	return(1);
}

/**
*@brief �Z�}�t�H���A�����b�N
* @return ������1
*/
int i2c_smf::sem_unlock()
{
	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=1;
	sb.sem_flg=0;
	if(semop(sid,&sb,1)== -1){
		perror("semop");
		return(-1);
	}
	return(1);
}

/**
*@brief �Z�}�t�H�̒l���擾
* @return �Z�}�t�H�̒l
*/
int i2c_smf::sem_ctl()
{
	return semctl(sid,0,GETVAL,c_arg);
}


