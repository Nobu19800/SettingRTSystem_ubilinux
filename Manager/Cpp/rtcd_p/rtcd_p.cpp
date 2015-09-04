

#include <iostream>
#include <rtm/Manager.h>
#include <coil/stringutil.h>
#include "LoadRTCs.h"


/**
*@brief プロパティから指定したキーの値を取得
* @param prop プロパティ
* @param key キー
* @param value 値
*/
template <class T>
void getProperty(coil::Properties& prop, const char* key, T& value)
{
	if (prop.findNode(key) != 0)
	{
		T tmp;
		if (coil::stringTo(tmp, prop[key].c_str()))
		{
			value = tmp;
		}
	}
}

/**
*@brief 指定したキーの値を取得
* @param name キー
* @return 値
*/
std::string getParam(std::string name)
{
	coil::Properties& prop(::RTC::Manager::instance().getConfig());
	std::string param = "";
	getProperty(prop, name.c_str(), param);
	coil::eraseBlank(param);
	return param;
}


/**
*@brief メイン関数
* @param argc コマンドライン引数の数
* @param argv コマンドライン引数
* @return 0
*/
int main(int argc, char** argv)
{
	RTC::Manager* manager;
	manager = RTC::Manager::init(argc, argv);
	

#ifdef _WINDOWS
	std::string path = getParam("manager.modules.load_path");
	coil::eraseBlank(path);

	coil::vstring pathList = coil::split(path, ",");

	for (int i = 0; i < pathList.size(); i++)
	{
		std::string filepath = pathList[i];

		char szFullPath[MAX_PATH];
		_fullpath(szFullPath, filepath.c_str(), sizeof(szFullPath) / sizeof(szFullPath[0]));
		std::string path = "PATH=";
		path += getenv("PATH");
		path += ";";
		path += szFullPath;
		putenv(path.c_str());

	}

#endif

	

	manager->activateManager();

	LoadRTCs *loadRTCsObject = new LoadRTCs(manager);
	loadRTCsObject->openFile();

	manager->runManager();

	return 0;
}
