/*!
 * @file  i2c_smf.h
 * @brief セマフォ操作のクラス
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
*@brief セマフォ操作のクラス
*/
class i2c_smf
{
public:
	/**
	*@brief コンストラクタ
	* @param name ファイル名
	* @param val セマフォの値
	*/
	i2c_smf(char *name = "/tmp/edisoni2csmf", int val = 1);
	/**
	*@brief デストラクタ
	*/
	~i2c_smf();
	/**
	*@brief セマフォ取得
	* @param path ファイル名
	* @param val セマフォの値
	* @return ID
	*/
	int sem_get(char *path, int val = 1);
	/**
	*@brief セマフォをロック
	* @return 成功で1
	*/
	int sem_lock();
	/**
	*@brief セマフォをアンロック
	* @return 成功で1
	*/
	int sem_unlock();
	/**
	*@brief セマフォの値を取得
	* @return セマフォの値
	*/
	int sem_ctl();
	int sid;
private:
	
};





#endif
