// -*-C++-*-
/*!
 * @file  rtcControlSVC_impl.cpp
 * @brief RTC�N���֘A�̃T�[�r�X�C���^�[�t�F�[�X
 *
 */

#include <coil/stringutil.h>
#include "rtcControlSVC_impl.h"




/**
*@brief RTC�N���֘A�̃T�[�r�X�C���^�[�t�F�[�X�̃R���X�g���N�^
* @param manager �}�l�[�W���I�u�W�F�N�g
*/
RTCDataInterfaceSVC_impl::RTCDataInterfaceSVC_impl(RTC::Manager* manager)
{
	mgr = manager;
	loadRTCsObject = new LoadRTCs(manager);
	loadRTCsObject->openFile();
  
}

/**
*@brief RTC�N���֘A�̃T�[�r�X�C���^�[�t�F�[�X�̃f�X�g���N�^
*/
RTCDataInterfaceSVC_impl::~RTCDataInterfaceSVC_impl()
{
  
}


/**
*@brief ���s����RTC�̃p�X�̃��X�g���擾
* @param paths RTC�̃p�X�̃��X�g
* @return ������True�A���s��False
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
*@brief RTC�N��
* @param name RTC��
* @param filename �t�@�C����
* @param filepath �f�B���N�g���p�X
* @return ������True�A���s��False
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
*@brief RTC�폜
* @param name RTC��
* @return ������True�A���s��False
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
*@brief �N������RTC�̃��X�g
* @param names �N������RTC�̃��X�g
* @return������True�A���s��False
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






