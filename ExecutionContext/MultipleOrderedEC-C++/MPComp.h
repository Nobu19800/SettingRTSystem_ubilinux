/*!
* @file  MPComp.h
* @brief 実行順序設定関連のクラス、関数
*
*/

#ifndef MPCOMP_H
#define MPCOMP_H
#include <rtm/RTC.h>
#include <rtm/Manager.h>
#include <rtm/PeriodicExecutionContext.h>

#include <vector>



/**
* @class add_Rule
*@brief 実行条件のクラス
*/
class add_Rule
{
public:
	/**
	*@brief コンストラクタ
	*/
	add_Rule(){};
	int state;
	std::string name;
	RTC::LightweightRTObject_var r;
};


/**
* @class sub_Rule
*@brief ブロックのクラス
*/
class sub_Rule
{
public:
	/**
	*@brief コンストラクタ
	*/
	sub_Rule(){};
	std::string v;
	RTC::LightweightRTObject_var r;
	int s;
};

/**
* @class Rule
*@brief 並列ブロックのクラス
*/
class Rule
{
private:
    
public:
	/**
	*@brief コンストラクタ
	*/
	Rule(){};
	/**
	*@brief デストラクタ
	*/
	~Rule(){};
	std::vector<std::vector<sub_Rule> > SR;
	/**
	*@brief 直列ブロック追加
	*/
	void addP();
	/**
	*@brief 指定番号の直列ブロックにブロック追加
	* @param num 番号
	* @param s ブロックのRTC名
	*/
	void addsubRule(int num, std::string v);
    
};


/**
* @class main_Rule
*@brief 実行順序のクラス
*/
class main_Rule
{
public:
	/**
	*@brief コンストラクタ
	*/
	main_Rule(){};
	std::vector<Rule> rs;
	std::vector<add_Rule> ar;

	
	/**
	*@brief 並列ブロック追加
	*/
	void addRule();
	
	/**
	*@brief 実行条件追加
	* @param n RTC名
	* @param s 状態
	*/
	void addaddRule(std::string n, int s);

	/**
	*@brief 指定した番号の並列ブロックを取得
	* @param num 番号
	* @return 並列ブロック
	*/
	Rule *getRule(int num);

	/**
	*@brief 指定した番号の実行条件を取得
	* @param num 番号
	* @return 実行条件
	*/
	add_Rule *getaddRule(int num);
	
};


/**
*@brief ファイルより実行順序の読み込む関数
* @param rs 実行順序
* @param Name ファイル名
* @return 成功でTrue、失敗でFalse
*/
bool LoadMainRule(std::vector<main_Rule> &rs, std::string Name);

/**
*@brief テキストファイルからの実行順序(実行条件)読み込む関数
* @param cs ファイルから読み込んだ単語のリスト
* @param nm 現在の位置
* @param ar 条件のリスト
*/
void LoadAddRule(std::vector<std::string> &cs, int &nm, std::vector<add_Rule> &ar);
/**
*@brief テキストファイルからの実行順序(直列ブロック)読み込む関数
* @param cs ファイルから読み込んだ単語のリスト
* @param nm 現在の位置
* @param sr 条件のリスト
*/
void LoadSubRule(std::vector<std::string> &cs, int &nm, std::vector<sub_Rule> &sr);
/**
*@brief テキストファイルからの実行順序(並列ブロック)読み込む関数
* @param cs ファイルから読み込んだ単語のリスト
* @param nm 現在の位置
* @param rs 実行順序
*/
void LoadHRule(std::vector<std::string> &cs, int &nm, std::vector<Rule> &rs);
/**
*@brief テキストファイルからの実行順序(直列ブロックのリスト)読み込む関数
* @param cs ファイルから読み込んだ単語のリスト
* @param nm 現在の位置
* @param r 並列ブロック
*/
void LoadSRule(std::vector<std::string> &cs, int &nm, Rule &r);
/**
*@brief 単語のリストの位置を移動する
* @param cs ファイルから読み込んだ単語のリスト
* @param nm 現在の位置
* @return 成功でTrue、失敗でFalse
*/
bool AddCount(std::vector<std::string> &cs, int &nm);


#endif