// -*-C++-*-
/*!
 * @file  rtcControlSVC_impl.cpp
 * @brief RTC起動関連のサービスインターフェース
 *
 */

#include <coil/stringutil.h>
#include "rtcControlSVC_impl.h"




/**
*@brief RTC起動関連のサービスインターフェースのコンストラクタ
* @param manager マネージャオブジェクト
*/
RTCDataInterfaceSVC_impl::RTCDataInterfaceSVC_impl(RTC::Manager* manager)
{
	mgr = manager;
	loadRTCsObject = new LoadRTCs(manager);
	loadRTCsObject->openFile();
  
}

/**
*@brief RTC起動関連のサービスインターフェースのデストラクタ
*/
RTCDataInterfaceSVC_impl::~RTCDataInterfaceSVC_impl()
{
  
}


/**
*@brief 実行中のRTCのパスのリストを取得
* @param paths RTCのパスのリスト
* @return 成功でTrue、失敗でFalse
*/
CORBA::Boolean RTCDataInterfaceSVC_impl::getRTC(rtcControl::rtcPathSeq_out paths)
{
	rtcControl::rtcPathSeq_var paths_var = new rtcControl::rtcPathSeq;
	std::vector<RTC::RtcBase*> comps = mgr->getComponents();
	paths_var->length(comps.size());
	for(int i=0;i < comps.size();i++)
	{
		RTC::ComponentProfile_var prof;
		
		prof = comps[i]->get_component_profile();
		RTC::NVList prop = prof->properties;
		
		//NVUtil::dump(prof->properties);
		
		CORBA::Any value = NVUtil::find(prop, "naming.names");
		const char* ans;
		value >>= ans;
		
		paths_var[i] = ans;
		
		
	}
	paths = paths_var._retn();
	return true;
  
#ifndef WIN32
  #warning "Code missing in function <CORBA::Boolean RTCDataInterfaceSVC_impl::getRTC(rtcControl::rtcPathSeq_out paths)>"
#endif
  return 0;
}






/**
*@brief RTC起動
* @param name RTC名
* @param filename ファイル名
* @param filepath ディレクトリパス
* @return 成功でTrue、失敗でFalse
*/
CORBA::Boolean RTCDataInterfaceSVC_impl::createComp(const char* name, const char* filename, const char* filepath)
{
	
	
	return loadRTCsObject->createComp(name, filename,filepath);
	
	
  
#ifndef WIN32
  #warning "Code missing in function <CORBA::Boolean RTCDataInterfaceSVC_impl::createComp(const char* filename, const char* filepath)>"
#endif
  return 0;
}

/**
*@brief RTC削除
* @param name RTC名
* @return 成功でTrue、失敗でFalse
*/
CORBA::Boolean RTCDataInterfaceSVC_impl::removeComp(const char* name)
{
	return loadRTCsObject->removeComp(name);
	
  
#ifndef WIN32
  #warning "Code missing in function <CORBA::Boolean RTCDataInterfaceSVC_impl::removeComp(const char* name)>"
#endif
  return 0;
}

/**
*@brief 起動したRTCのリスト
* @param names 起動したRTCのリスト
* @return成功でTrue、失敗でFalse
*/
CORBA::Boolean RTCDataInterfaceSVC_impl::getCompList(rtcControl::RTC_List_out names)
{

	
	loadRTCsObject->updateCompList();

	rtcControl::RTC_List_var paths_var = new rtcControl::RTC_List;

	int size = 0;
	for(int i=0;i < loadRTCsObject->compList.size();i++)
	{
		if(loadRTCsObject->compList[i].m_compList.size() > 0)
			size += 1;
	}
	
	paths_var->length(size);

	for(int i=0;i < loadRTCsObject->compList.size();i++)
	{
		if(loadRTCsObject->compList[i].m_compList.size() > 0)
		{
			paths_var[i].name = loadRTCsObject->compList[i].m_name.c_str();
			paths_var[i].filename = loadRTCsObject->compList[i].m_filename.c_str();
			paths_var[i].num = loadRTCsObject->compList[i].m_compList.size();
		}
		
		
	}
	
	names = paths_var._retn();

	return true;
#ifndef WIN32
  #warning "Code missing in function <CORBA::Boolean RTCDataInterfaceSVC_impl::removeComp(const char* name)>"
#endif
  return 0;
}






