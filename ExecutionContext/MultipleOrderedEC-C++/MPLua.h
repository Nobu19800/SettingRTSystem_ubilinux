/*!
* @file  MPLua.h
* @brief Luaから実行順序を読み込む関数
*
*/

#ifndef MPLUA_H
#define MPLUA_H

#include "MultipleOrderedEC.h"
#include "MPComp.h"


/**
*@brief Luaより実行順序の読み込む関数
* @param rs 実行順序リスト
* @param Name ファイルパス
* @return 成功でTrue、失敗でFalse
*/
bool LoadMainRule_Lua(std::vector<main_Rule> &rs, std::string Name);


/**
* @class MainLules
*@brief 実行順序のリスト
*/
class MainLules
{
public:
	/**
	*@brief コンストラクタ
	*/
	MainLules(){};
	std::vector<main_Rule> rs;
	/**
	*@brief 実行順序追加
	*/
	void addMainRule();
	/**
	*@brief 指定番号の実行順序取得
	* @param num 番号
	* @return 実行順序取得
	*/
	main_Rule* getMainRule(int num);
};



#endif
