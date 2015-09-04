#ifndef MPCOMP_H
#define MPCOMP_H
#include <rtm/RTC.h>
#include <rtm/Manager.h>
#include <rtm/PeriodicExecutionContext.h>

#include <vector>


/*
*実行条件のクラス
*/
class add_Rule
{
public:
	add_Rule(){};
	int state;
	std::string name;
	RTC::LightweightRTObject_var r;
};

/*
*直列ブロックのクラス
*/

class sub_Rule
{
public:
	sub_Rule(){};
	std::string v;
	RTC::LightweightRTObject_var r;
	int s;
};

/*
*並列ブロックのクラス
*/

class Rule
{
private:
    
public:
	std::vector<std::vector<sub_Rule> > SR;
	Rule(){};
	~Rule(){};
	void addP();
	void addsubRule(int num, std::string v);
    
};

/*
*実行順序のクラス
*/
class main_Rule
{
public:
	main_Rule(){};
	std::vector<Rule> rs;
	std::vector<add_Rule> ar;

	/*
	*並列ブロックの追加の関数
	*/
	void addRule();
	/*
	*実行条件の追加の関数
	*/
	void addaddRule(std::string n, int s);

	Rule *getRule(int num);
	add_Rule *getaddRule(int num);
	
};

/*
*ファイルより実行順序の読み込む関数
*/
bool LoadMainRule(std::vector<main_Rule> &rs, std::string Name);
/*
*テキストファイルからの実行順序読み込む関数
*/
void LoadAddRule(std::vector<std::string> &cs, int &nm, std::vector<add_Rule> &ar);
void LoadSubRule(std::vector<std::string> &cs, int &nm, std::vector<sub_Rule> &sr);
void LoadHRule(std::vector<std::string> &cs, int &nm, std::vector<Rule> &rs);
void LoadSRule(std::vector<std::string> &cs, int &nm, Rule &r);
bool AddCount(std::vector<std::string> &cs, int &nm);


#endif