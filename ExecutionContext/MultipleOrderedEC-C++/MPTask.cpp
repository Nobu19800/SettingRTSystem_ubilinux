/*!
* @file  MPTask.cpp
* @brief GUI、直列ブロック実行スレッド
*
*/


#include "MPTask.h"

bool GUITask::app_flag = false;

/**
*@brief 直列ブロックを実行するスレッドのクラスのコンストラクタ
*/
MPTask::MPTask(RTC::MultipleOrderedEC *c)
{
	m_ec = c;
}

/**
*@brief
* @param c ブロック
* @param I 全体の並列ブロックの番号
* @param J 並列ブロック内の直列ブロックの番号
* @param K 直列ブロック内のブロックの番号
*/
void MPTask::addComp(sub_Rule *c, int I, int J, int K)
{
	MPComp mc;
	mc.comp = c;
	mc.I = I;
	mc.J = J;
	mc.K = K;
	m_comp.push_back(mc);
	
}

/**
*@brief スレッド実行関数
* @return
*/
int MPTask::svc()
{
	if(m_ec->rs.size() > m_ec->r_num)
	{
		for(int i=0;i < m_comp.size();i++)
		{
			m_ec->rs[m_ec->r_num].rs[m_comp[i].I].SR[m_comp[i].J][m_comp[i].K].s = 1;
			m_ec->workerComp(m_comp[i].comp);
			m_ec->rs[m_ec->r_num].rs[m_comp[i].I].SR[m_comp[i].J][m_comp[i].K].s = 0;
			
		}
	}

	return 0;
}

/**
*@brief GUIを実行するスレッドのコンストラクタ
* @param ec 実行コンテキストオブジェクト
*/
GUITask::GUITask(RTC::MultipleOrderedEC *ec)
{
	
	this->m_ec = ec;
	
	
}

/**
*@brief スレッド実行関数
* @return
*/
int GUITask::svc()
{
	
#ifdef QT_GUI_LIB
	if(!app_flag)
	{
		app_flag = true;

		mu.lock();

		int _argc(1);
		char* _argv[]={""};

		Q_INIT_RESOURCE(MultipleOrderedEC);
		app = new QApplication(_argc, (char**)_argv);

		

		mw = new MainWindow(this->m_ec);

		

		mu.unlock();

		mw->show();

		

		app->exec();
	}
	else
	{
		
	}
#endif
	return 0;

	
}

/**
*@brief 未使用
* @return
*/
void GUITask::updateRTC()
{

}
