/*!
 * @file  i2c_smf.cpp
 * @brief セマフォ操作のクラス
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
*@brief セマフォ操作のクラスのコンストラクタ
* @param name ファイル名
* @param val セマフォの値
*/
i2c_smf::i2c_smf(char *name, int val)
{
	
	
	sid=sem_get(name, val);
	
	
}

/**
*@brief セマフォ操作のクラスのデストラクタ
*/
i2c_smf::~i2c_smf()
{

}

/**
*@brief セマフォ取得
* @param path ファイル名
* @param val セマフォの値
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
*@brief セマフォをロック
* @return 成功で1
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
*@brief セマフォをアンロック
* @return 成功で1
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
*@brief セマフォの値を取得
* @return セマフォの値
*/
int i2c_smf::sem_ctl()
{
	return semctl(sid,0,GETVAL,c_arg);
}


