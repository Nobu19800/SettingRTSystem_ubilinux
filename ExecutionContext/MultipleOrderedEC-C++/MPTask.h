/*!
* @file  MPTask.h
* @brief GUI、直列ブロック実行スレッド
*
*/

#ifndef MPTASK_H
#define MPTASK_H

#include <rtm/RTC.h>



#include <rtm/Manager.h>
#include <rtm/PeriodicExecutionContext.h>


#include "MultipleOrderedEC.h"
#include "MPComp.h"

#ifdef QT_GUI_LIB
#include "mainwindow.h"
#include <QApplication>
#endif



/**
* @class MPComp
*@brief 同一スレッドでの実行順序クラス
*/
class MPComp
{
public:
	/**
	*@brief コンストラクタ
	*/
	MPComp(){};
	sub_Rule *comp;
	int I;
	int J;
	int K;
};


/**
* @class MainLules
*@brief 直列ブロックを実行するスレッドのクラス
*/
class MPTask : public virtual coil::Task
{
public:
		/**
		*@brief コンストラクタ
		* @param c 実行コンテキストオブジェクト
		*/
		MPTask(RTC::MultipleOrderedEC *c);
		
		/**
		*@brief スレッド実行関数
		* @return
		*/
		virtual int svc();
		
		/**
		*@brief
		* @param c ブロック
		* @param I 全体の並列ブロックの番号
		* @param J 並列ブロック内の直列ブロックの番号
		* @param K 直列ブロック内のブロックの番号
		*/
		void addComp(sub_Rule *c, int I, int J, int K);
private:
	std::vector<MPComp> m_comp;
	RTC::MultipleOrderedEC *m_ec;

};


/**
* @class GUITask
*@brief GUIを実行するスレッド
*/
class GUITask : public virtual coil::Task
{
public:
		/**
		*@brief コンストラクタ
		* @param ec 実行コンテキストオブジェクト
		*/
		GUITask(RTC::MultipleOrderedEC *ec);
		/**
		*@brief スレッド実行関数
		* @return
		*/
		virtual int svc();
		/**
		*@brief 未使用
		* @return
		*/
		void updateRTC();
		coil::Mutex mu;

		static bool app_flag;
private:
	RTC::MultipleOrderedEC *m_ec;

#ifdef QT_GUI_LIB
	MainWindow *mw;
	QApplication *app;
#endif

	
	
};



#endif
