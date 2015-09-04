#ifndef MPLUA_H
#define MPLUA_H

#include "MultipleOrderedEC.h"
#include "MPComp.h"

/*
*Luaより実行順序の読み込む関数
*/
bool LoadMainRule_Lua(std::vector<main_Rule> &rs, std::string Name);

/*
*全実行順序のクラス
*/
class MainLules
{
public:
	MainLules(){};
	std::vector<main_Rule> rs;
	void addMainRule();
	main_Rule* getMainRule(int num);
};



#endif
