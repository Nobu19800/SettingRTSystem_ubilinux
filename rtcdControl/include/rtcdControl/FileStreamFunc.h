/*!
* @file  FileStreamFunc.h
* @brief ファイル操作関連の関数
*
*/

#ifndef FILESTREAMFUNC_H
#define FILESTREAMFUNC_H

#include <stdio.h>


#include <iostream>
#include <rtm/CorbaNaming.h>
#include <rtm/RTObject.h>
#include <rtm/CorbaConsumer.h>
#include <assert.h>
#include <string>
#include <vector>


/**
*@brief バイナリファイルに文字保存する関数
*@param a 保存する文字列
*@param ofs ファイルストリーム
*/
void WriteString(std::string a, std::ofstream &ofs);

/**
*@brief バイナリファイルに文字保存する関数
*@param a 文字列
*@param ofs ファイルストリーム
* @return 読み込んだ文字列
*/
std::string ReadString(std::ifstream &ifs);


/**
* @class PathList
*@brief 指定パスのファイル名、本体名、拡張子、ディレクトリパスを取得
*/
class PathList
{
public:
	/**
	*@brief コンストラクタ
	* @param path パス
	*/
	PathList(std::string path);
	std::string fname;
	std::string name;
	std::string cxt;
	std::string dname;
};



#endif