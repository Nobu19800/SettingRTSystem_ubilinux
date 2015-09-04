/*!
* @file  LoadRTCs.h
* @brief RTC読み込み関連のクラス、関連
*
*/



#ifndef LOADRTCS_H
#define LOADRTCS_H



#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <coil/DynamicLib.h>
 
typedef void (*RTCInitFunction)(RTC::Manager* pManager);


/**
* @class compParam
*@brief 動的リンクライブラリから読み込んだRTCの各情報を格納するクラス
*/

class compParam
{
public:
	/**
	*@brief コンストラクタ
	* @param name RTC名
	* @param filename ファイル名
	* @param filepath ディレクトリパス
	* @param func 初期化関数
	* @param compList RTCオブジェクトのリスト
	*/
	compParam(std::string name, std::string filename, std::string filepath, RTCInitFunction func, std::vector<RTC::RtcBase *> compList);
	std::string m_name;
	std::string m_filename;
	std::string m_filepath;
	RTCInitFunction m_func;
	std::vector<RTC::RtcBase *> m_compList;
};

/**
* @class LoadRTCs
*@brief RTCロード関連の関数を持つクラス
*/
class LoadRTCs
{
 
 public:
  /**
  *@brief コンストラクタ
  * @param manager マネージャオブジェクト
  */
  LoadRTCs(RTC::Manager* manager);
  /**
  *@brief デストラクタ
  */
  virtual ~LoadRTCs();

  /**
  *@brief 削除予定
  */
   void updateCompList();
   
   /**
   *@brief RTC起動の関数
   * @param name RTC名
   * @param filename ファイル名
   * @param filepath ディレクトリパス
   * @return 成功でTrue、失敗でFalse
   */
   bool createComp(const char* name, const char* filename, const char* filepath);

   /**
   *@brief RTC削除の関数(同一のRTCを複数起動している場合は一番最後に起動したRTCを終了)
   * @param name RTC名
   * @return 成功でTrue、失敗でFalse
   */
   bool removeComp(const char* name);
   
   /**
   *@brief RTC名からRTCの各情報を取得
   * @param name RTC名
   * @return RTCの各情報
   */
   compParam *getCompFromName(std::string name);
   /**
   *@brief ファイル名からRTCの初期化関数を取得
   * @param filename ファイル名
   * @param filepath ディレクトリパス
   * @return RTCの初期化関数
   */
   RTCInitFunction getFunc(std::string filename,std::string filepath);
   /**
   *@brief ファイルから起動するRTCのリストを読み込んで各RTCを起動
   */
   void openFile();

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


	std::vector<coil::DynamicLib*> dllList;
	std::vector<compParam> compList;
	RTC::Manager* mgr;

private:

};


/**
* @class RTC_FinalizeListener
*@brief RTC終了時にRTCのリストから削除するのリスナ
*/
class RTC_FinalizeListener
	: public RTC::PostComponentActionListener
{
public:
	/**
	*@brief コンストラクタ
	* @param rtc RTCオブジェクト
	* @param list RTCの各情報
	*/
	RTC_FinalizeListener(RTC::RtcBase * rtc, compParam *list);
	/**
	*@brief RTC終了時にRTCのリストから削除する
	* @param ec_id 実行コンテキストのID
	* @param list RTC::ReturnCode_t
	*/
	void operator()(RTC::UniqueId ec_id, RTC::ReturnCode_t ret);
	RTC::RtcBase * m_rtc;
	compParam *m_list;
};



#endif // RTCCONTROLSVC_IMPL_H


