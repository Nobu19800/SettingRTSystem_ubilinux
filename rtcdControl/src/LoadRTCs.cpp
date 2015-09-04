/*!
* @file  LoadRTCs.cpp
* @brief RTC読み込み関連のクラス、関連
*
*/

#include <coil/stringutil.h>
#include "FileStreamFunc.h"
#include "LoadRTCs.h"

using namespace std;


/**
*@brief 動的リンクライブラリから読み込んだRTCの各情報を格納するクラスのコンストラクタ
* @param name RTC名
* @param filename ファイル名
* @param filepath ディレクトリパス
* @param func 初期化関数
* @param compList RTCオブジェクトのリスト
*/
compParam::compParam(std::string name, std::string filename, std::string filepath, RTCInitFunction func, std::vector<RTC::RtcBase *> compList)
{
	m_name = name;
	m_filename = filename;
	m_filepath = filepath;
	m_func = func;
	m_compList = compList;
}


/**
*@brief RTCロード関連の関数を持つクラスのコンストラクタ
* @param manager マネージャオブジェクト
*/
LoadRTCs::LoadRTCs(RTC::Manager* manager)
{
	mgr = manager;

}

/**
*@brief RTCロード関連の関数を持つクラスのデストラクタ
*/
LoadRTCs::~LoadRTCs()
{

}

/**
*@brief ファイルから起動するRTCのリストを読み込んで各RTCを起動
*/
void LoadRTCs::openFile()
{
	coil::Properties& prop(::RTC::Manager::instance().getConfig());
	std::string value = "";
	getProperty(prop, "manager.modules.loadRTCs", value);
	coil::eraseBlank(value);

	if(value == "")
	{
		return;
	}

#ifdef _WINDOWS
	coil::replaceString(value, "/", "\\");
#else
	coil::replaceString(value, "\\", "/");
#endif

	std::ifstream ifs( value.c_str() , ios::in | ios::binary );

	int m;
	ifs.read( (char*)&m, sizeof(m) );
	
	for(int i=0;i < m;i++)
	{
		string name;
		name = ReadString( ifs );
		string filename;
		filename = ReadString( ifs );
		int d;
		ifs.read( (char*)&d, sizeof(d) );
		string path;
		path = ReadString( ifs );
		string dir;
		dir = ReadString( ifs );

		for(int j=0;j < d;j++)
		{
			createComp(name.c_str(),filename.c_str(),dir.c_str());
		}
	}

	ifs.close();
}

/**
*@brief ファイル名からRTCの初期化関数を取得
* @param filename ファイル名
* @param filepath ディレクトリパス
* @return RTCの初期化関数
*/
RTCInitFunction LoadRTCs::getFunc(std::string filename,std::string filepath)
{
#ifdef _WINDOWS
	char szFullPath[MAX_PATH];
	_fullpath(szFullPath, filepath.c_str(), sizeof(szFullPath)/sizeof(szFullPath[0]));
	std::string path = "PATH=";
	path += getenv("PATH");
	path += ";";
	path += szFullPath;
	putenv(path.c_str());


	coil::replaceString(filepath, "/", "\\");
	std::string fn = filename + ".dll";


#else
	coil::replaceString(filepath, "\\", "/");
	std::string fn = filepath + "/" + filename + ".so";

#endif


	coil::DynamicLib *dl = new coil::DynamicLib();

	

	int ret = dl->open(fn.c_str());
	if (ret != 0) {
		
		return NULL;
	}
	dllList.push_back(dl);


	std::string fun = filename + "Init";

	RTCInitFunction InInitFunc = (RTCInitFunction)RTCInitFunction(dl->symbol(fun.c_str()));
	
	return InInitFunc;
}

/**
*@brief RTC名からRTCの各情報を取得
* @param name RTC名
* @return RTCの各情報
*/
compParam *LoadRTCs::getCompFromName(std::string name)
{
	for(int i=0;i < compList.size();i++)
	{
		
		if(compList[i].m_name == name)
		{
			return &compList[i];
		}
	}
	return NULL;
}




/**
*@brief RTC起動の関数
* @param name RTC名
* @param filename ファイル名
* @param filepath ディレクトリパス
* @return 成功でTrue、失敗でFalse
*/
bool LoadRTCs::createComp(const char* name, const char* filename, const char* filepath)
{
	
	updateCompList();
	
	RTCInitFunction InInitFunc = NULL;
	compParam *preLoadComp = getCompFromName(name);
	if(preLoadComp)
	{
		InInitFunc = preLoadComp->m_func;
		
	}

	if(preLoadComp == NULL)
	{
		InInitFunc = getFunc(filename, filepath);
		if(InInitFunc == NULL)
		{
			return false;
		}
		InInitFunc(mgr);
	}

	if(InInitFunc)
	{
		
		RTC::RtcBase *comp = mgr->createComponent(filename);
		if(!comp)
			return false;
		

		compParam *cp;

		if(preLoadComp)
		{
			preLoadComp->m_compList.push_back(comp);
			cp = preLoadComp;
		}
		else
		{
			std::vector<RTC::RtcBase *> rl;
			rl.push_back(comp);

			
			
			compList.push_back(compParam(name, filename, filepath, InInitFunc, rl));
			cp = &compList[compList.size()-1];
			
		}
		comp->addPostComponentActionListener(RTC::POST_ON_FINALIZE, new RTC_FinalizeListener(comp,cp));
		
		return true;
	}
	else
	{
		return false;
	}
	return false;

}


/**
*@brief RTC削除の関数(同一のRTCを複数起動している場合は一番最後に起動したRTCを終了)
* @param name RTC名
* @return 成功でTrue、失敗でFalse
*/
bool LoadRTCs::removeComp(const char* name)
{
	updateCompList();
	compParam *c = getCompFromName(name);
	
	if(c)
	{
		if(c->m_compList.size() != 0)
		{
			c->m_compList[c->m_compList.size()-1]->exit();
			c->m_compList.pop_back();
		}
		else
		{
			return false;
		}
		
	}
	else
	{
		return false;
	}
	return true;

}

/**
*@brief 削除予定
*/
void LoadRTCs::updateCompList()
{
	/*std::cout << "test2" << std::endl;
	for (std::vector<compParam>::iterator it = compList.begin(); it != compList.end(); ++it)
	{
		for (std::vector<RTC::RtcBase *>::iterator rtc = (*it).m_compList.begin(); rtc != (*it).m_compList.end();)
		{
			
			try
			{
				//(*rtc)->getObjRef()->get_owned_contexts();
				(*rtc)->getObjRef();
				++rtc;
			}
			catch (...)
			{
				std::cout << "test" << std::endl;
				rtc = (*it).m_compList.erase(rtc);
				//++rtc;
			}
			
		}
		
	}*/
}


/**
*@brief RTC終了時にRTCのリストから削除するのリスナのコンストラクタ
* @param rtc RTCオブジェクト
* @param list RTCの各情報
*/
RTC_FinalizeListener::RTC_FinalizeListener(RTC::RtcBase * rtc, compParam *list)
{
	m_rtc = rtc;
	m_list = list;
};

/**
*@brief RTC終了時にRTCのリストから削除する
* @param ec_id 実行コンテキストのID
* @param list RTC::ReturnCode_t
*/
void RTC_FinalizeListener::operator()(RTC::UniqueId ec_id, RTC::ReturnCode_t ret)
{
	//std::cout << m_list->m_filename << coil::otos<int>(ec_id) << std::endl;
	//m_list->m_compList.clear();
	m_list->m_compList.erase(std::remove(m_list->m_compList.begin(), m_list->m_compList.end(), m_rtc), m_list->m_compList.end());
};


// End of example implementational code



