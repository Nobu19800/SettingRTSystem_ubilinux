#include "MPTask.h"

bool GUITask::app_flag = false;

MPTask::MPTask(RTC::MultipleOrderedEC *c)
{
	m_ec = c;
}

void MPTask::addComp(sub_Rule *c, int I, int J, int K)
{
	MPComp mc;
	mc.comp = c;
	mc.I = I;
	mc.J = J;
	mc.K = K;
	m_comp.push_back(mc);
	
}

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


GUITask::GUITask(RTC::MultipleOrderedEC *ec)
{
	
	this->m_ec = ec;
	
	
}

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


void GUITask::updateRTC()
{

}
