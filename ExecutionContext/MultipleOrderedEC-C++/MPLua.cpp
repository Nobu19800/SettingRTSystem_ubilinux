/*!
* @file  MPLua.cpp
* @brief Luaから実行順序を読み込む関数
*
*/


#include "MPLua.h"
#include "FileStreamFunc.h"
#include <luabind/luabind.hpp>
#include <lua.hpp>

using namespace luabind;

/**
*@brief 実行順序追加
*/
void MainLules::addMainRule()
{
	main_Rule sr;
	rs.push_back(sr);
}

/**
*@brief 指定番号の実行順序取得
* @param num 番号
* @return 実行順序取得
*/
main_Rule* MainLules::getMainRule(int num)
{
	if(rs.size() > num)
		return &rs[num];
	return NULL;
}

/**
*@brief Luaより実行順序の読み込む関数
* @param rs 実行順序リスト
* @param Name ファイルパス
* @return 成功でTrue、失敗でFalse
*/
bool LoadMainRule_Lua(std::vector<main_Rule> &rs, std::string Name)
{
	lua_State* lua;

	lua = lua_open();
	luaL_openlibs(lua);
	luabind::open(lua);

	int ret = luaL_dofile(lua, "loadLua.lua");

	MainLules ml;

	module(lua)
	[
		class_<MainLules>("MainLules")
		.def("addMainRule", &MainLules::addMainRule)
		.def("getMainRule", &MainLules::getMainRule)

		,class_<main_Rule>("main_Rule")
		.def("addRule", &main_Rule::addRule)
		.def("addaddRule", &main_Rule::addaddRule)
		.def("getRule", &main_Rule::getRule)
		.def("getaddRule", &main_Rule::getaddRule)

		,class_<Rule>("Rule")
		.def("addP", &Rule::addP)
		.def("addsubRule", &Rule::addsubRule)


	];

	luabind::object lua_global = globals(lua);
	lua_global["MainLules_object"] = &ml;

	try {
		std::string tmp = Name;
		coil::replaceString(tmp,"\\","/");
		PathList pl = PathList(Name);
		
		
		call_function<void>(lua, "load_comp", tmp, pl.name);

	} catch (const error &e) {
		return false;
	  static_cast<void>(e);
	  std::cout << "call_function: " << lua_tostring(lua, -1) << std::endl;
	}

	rs = ml.rs;

	

	return true;


}

