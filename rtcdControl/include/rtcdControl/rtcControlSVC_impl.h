// -*-C++-*-
/*!
 * @file  rtcControlSVC_impl.h
 * @brief RTC起動関連のサービスインターフェース
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
*@brief RTC起動関連のサービスインターフェース
*/
class RTCDataInterfaceSVC_impl
 : public virtual POA_rtcControl::RTCDataInterface,
   public virtual PortableServer::RefCountServantBase
{
 private:


 public:

	 /**
	 *@brief コンストラクタ
	 * @param manager マネージャオブジェクト
	 */
	 RTCDataInterfaceSVC_impl(RTC::Manager* manager);
	 /**
	 *@brief デストラクタ
	 */
   virtual ~RTCDataInterfaceSVC_impl();

   /**
   *@brief 実行中のRTCのパスのリストを取得
   * @param paths RTCのパスのリスト
   * @return 成功でTrue、失敗でFalse
   */
   CORBA::Boolean getRTC(rtcControl::rtcPathSeq_out paths);
   /**
   *@brief RTC起動
   * @param name RTC名
   * @param filename ファイル名
   * @param filepath ディレクトリパス
   * @return 成功でTrue、失敗でFalse
   */
   CORBA::Boolean createComp(const char* name, const char* filename, const char* filepath);
   /**
   *@brief RTC削除
   * @param name RTC名
   * @return 成功でTrue、失敗でFalse
   */
   CORBA::Boolean removeComp(const char* name);
   /**
   *@brief 起動したRTCのリスト
   * @param names 起動したRTCのリスト
   * @return成功でTrue、失敗でFalse
   */
   CORBA::Boolean getCompList(rtcControl::RTC_List_out names);
   

private:
	LoadRTCs *loadRTCsObject;
	RTC::Manager* mgr;

};



#endif // RTCCONTROLSVC_IMPL_H


