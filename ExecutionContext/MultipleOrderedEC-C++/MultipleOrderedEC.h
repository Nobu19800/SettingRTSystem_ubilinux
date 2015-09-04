#ifndef RTC_MUTIPLEORDEREDEC_H
#define RTC_MUTIPLEORDEREDEC_H

#include <rtm/RTC.h>



#include <rtm/Manager.h>
#include <rtm/PeriodicExecutionContext.h>

#include "MPComp.h"


#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

class MPTask;
class GUITask;

namespace RTC
{
  /*
  *実行順序の設定ができる実行コンテキストクラス
  */
  class MultipleOrderedEC
    : public virtual PeriodicExecutionContext
  {

  public:

    MultipleOrderedEC();

    virtual ~MultipleOrderedEC(void);

	/*
	*スレッド実行関数
	*/
    virtual int svc(void);
	/*
	*コンポーネントのロジック実行の関数
	*/
	void workerComp(sub_Rule *c);

	
	/*
	*ファイルから実行順序の読み込みの関数
	*/
	void LoadRule();

	
	/*
	*コンポーネントの名前取得の関数
	*/
	std::string getCompName(int num);
	/*
	*コンポーネントの数取得の関数
	*/
	int getCompNum();

	/*
	*GUIから実行順序の読み込みの関数
	*/
	void LoadRuleGUI(std::vector<main_Rule> &RS_d);

	/*
	*設定した実行順序のRTCを格納する関数
	*/
	void LoadRules();

	std::vector<main_Rule> rs;
	GUITask *g_task;

	int r_num;

	coil::Mutex mutex_2;

	std::string FileName;
	std::string SetGui;

	//std::vector<Comp> s_comp;
	/*
	*rtc.confの設定を取得する関数
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

	
	
	



  };
};

#ifdef WIN32
#pragma warning( default : 4290 )
#endif


extern "C"
{
  DLL_EXPORT void MultipleOrderedECInit(RTC::Manager* manager);
};

#endif
