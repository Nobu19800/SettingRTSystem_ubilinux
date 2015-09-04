// -*-C++-*-
/*!
 * @file  rtcControlSVC_impl.h
 * @brief RTC�N���֘A�̃T�[�r�X�C���^�[�t�F�[�X
 *
 */

#include <rtm/DataFlowComponentBase.h>
#include "BasicDataTypeSkel.h"

#include "rtcControlSkel.h"

#ifndef RTCCONTROLSVC_IMPL_H
#define RTCCONTROLSVC_IMPL_H

#include <rtm/Manager.h>

#include "LoadRTCs.h"
 






/**
* @class RTCDataInterfaceSVC_impl
*@brief RTC�N���֘A�̃T�[�r�X�C���^�[�t�F�[�X
*/
class RTCDataInterfaceSVC_impl
 : public virtual POA_rtcControl::RTCDataInterface,
   public virtual PortableServer::RefCountServantBase
{
 private:


 public:

	 /**
	 *@brief �R���X�g���N�^
	 * @param manager �}�l�[�W���I�u�W�F�N�g
	 */
	 RTCDataInterfaceSVC_impl(RTC::Manager* manager);
	 /**
	 *@brief �f�X�g���N�^
	 */
   virtual ~RTCDataInterfaceSVC_impl();

   /**
   *@brief ���s����RTC�̃p�X�̃��X�g���擾
   * @param paths RTC�̃p�X�̃��X�g
   * @return ������True�A���s��False
   */
   CORBA::Boolean getRTC(rtcControl::rtcPathSeq_out paths);
   /**
   *@brief RTC�N��
   * @param name RTC��
   * @param filename �t�@�C����
   * @param filepath �f�B���N�g���p�X
   * @return ������True�A���s��False
   */
   CORBA::Boolean createComp(const char* name, const char* filename, const char* filepath);
   /**
   *@brief RTC�폜
   * @param name RTC��
   * @return ������True�A���s��False
   */
   CORBA::Boolean removeComp(const char* name);
   /**
   *@brief �N������RTC�̃��X�g
   * @param names �N������RTC�̃��X�g
   * @return������True�A���s��False
   */
   CORBA::Boolean getCompList(rtcControl::RTC_List_out names);
   

private:
	LoadRTCs *loadRTCsObject;
	RTC::Manager* mgr;

};



#endif // RTCCONTROLSVC_IMPL_H


