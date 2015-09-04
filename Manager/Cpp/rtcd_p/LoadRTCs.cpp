/*!
* @file  LoadRTCs.cpp
* @brief RTC�ǂݍ��݊֘A�̃N���X�A�֘A
*
*/

#include <coil/stringutil.h>
#include "FileStreamFunc.h"
#include "LoadRTCs.h"

using namespace std;


/**
*@brief ���I�����N���C�u��������ǂݍ���RTC�̊e�����i�[����N���X�̃R���X�g���N�^
* @param name RTC��
* @param filename �t�@�C����
* @param filepath �f�B���N�g���p�X
* @param func �������֐�
* @param compList RTC�I�u�W�F�N�g�̃��X�g
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
*@brief RTC���[�h�֘A�̊֐������N���X�̃R���X�g���N�^
* @param manager �}�l�[�W���I�u�W�F�N�g
*/
LoadRTCs::LoadRTCs(RTC::Manager* manager)
{
	mgr = manager;

}

/**
*@brief RTC���[�h�֘A�̊֐������N���X�̃f�X�g���N�^
*/
LoadRTCs::~LoadRTCs()
{

}

/**
*@brief �t�@�C������N������RTC�̃��X�g��ǂݍ���ŊeRTC���N��
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
*@brief �t�@�C��������RTC�̏������֐����擾
* @param filename �t�@�C����
* @param filepath �f�B���N�g���p�X
* @return RTC�̏������֐�
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
*@brief RTC������RTC�̊e�����擾
* @param name RTC��
* @return RTC�̊e���
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
*@brief RTC�N���̊֐�
* @param name RTC��
* @param filename �t�@�C����
* @param filepath �f�B���N�g���p�X
* @return ������True�A���s��False
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
*@brief RTC�폜�̊֐�(�����RTC�𕡐��N�����Ă���ꍇ�͈�ԍŌ�ɋN������RTC���I��)
* @param name RTC��
* @return ������True�A���s��False
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
*@brief �폜�\��
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
*@brief RTC�I������RTC�̃��X�g����폜����̃��X�i�̃R���X�g���N�^
* @param rtc RTC�I�u�W�F�N�g
* @param list RTC�̊e���
*/
RTC_FinalizeListener::RTC_FinalizeListener(RTC::RtcBase * rtc, compParam *list)
{
	m_rtc = rtc;
	m_list = list;
};

/**
*@brief RTC�I������RTC�̃��X�g����폜����
* @param ec_id ���s�R���e�L�X�g��ID
* @param list RTC::ReturnCode_t
*/
void RTC_FinalizeListener::operator()(RTC::UniqueId ec_id, RTC::ReturnCode_t ret)
{
	//std::cout << m_list->m_filename << coil::otos<int>(ec_id) << std::endl;
	//m_list->m_compList.clear();
	m_list->m_compList.erase(std::remove(m_list->m_compList.begin(), m_list->m_compList.end(), m_rtc), m_list->m_compList.end());
};


// End of example implementational code



