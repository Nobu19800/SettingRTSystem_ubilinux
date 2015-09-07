/*!
* @file  FileStreamFunc.h
* @brief ファイル操作関連の関数
*
*/

#ifndef COMPSEARCH_H
#define COMPSEARCH_H

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
* @param a 文字列
* @param ofs ファイルストリーム
*/
void WriteString(std::string a, std::ofstream &ofs);

/**
*@brief バイナリファイルより文字読み込みする関数
* @param ifs ファイルストリーム
* @return 文字列
*/
std::string ReadString(std::ifstream &ifs);

/**
* @class PathList
*@brief ファイルパスからファイル名、本体名、拡張子、ディレクトリパスを出力
*/
class PathList
{
public:
	/**
	*@brief コンストラクタ
	* @param path ファイルパス
	*/
	PathList(std::string path);
	std::string fname;
	std::string name;
	std::string cxt;
	std::string dname;
};



#endif