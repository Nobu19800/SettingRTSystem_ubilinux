#include "MultipleOrderedEC.h"
#include <rtm/ECFactory.h>
#include <iostream>
#include <rtm/CorbaConsumer.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <coil/stringutil.h>


#include "MPTask.h"
#include "CompSearch.h"

using namespace std;

namespace RTC
{
  MultipleOrderedEC::MultipleOrderedEC()
	   : PeriodicExecutionContext()
  {
	  coil::Properties& prop(::RTC::Manager::instance().getConfig());
	  SetGui = "YES";
	  FileName = "";
	  getProperty(prop, "exec_cxt.periodic.gui", SetGui);
	  getProperty(prop, "exec_cxt.periodic.filename", FileName);

	  coil::eraseBlank(SetGui);
	  coil::eraseBlank(FileName);

	  /*if (FileName == "")
	  {
		  FileName = "CompList.conf";
	  }*/

	  if(SetGui == "YES")
	  {
#ifdef QT_GUI_LIB
		g_task = new GUITask(this);
		g_task->activate();
#endif
	  }



	  //main_Rule R;
	  //rs.push_back(R);

	  r_num = 0;

	  

	  

	  



	

  }

  MultipleOrderedEC::~MultipleOrderedEC()
  {
  }

  
   

  std::string MultipleOrderedEC::getCompName(int num)
  {
	  mutex_2.lock();
	  ComponentProfile *mc = m_comps[num]._sm.m_obj->get_component_profile();
	  std::string Name = (const char*)mc->instance_name;
	
	  delete mc;
	   mutex_2.unlock();
	  return Name;
  }
  int MultipleOrderedEC::getCompNum()
  {
	return m_comps.size();
  }

  void MultipleOrderedEC::workerComp(sub_Rule *c)
  {
	  
				
		CompItr it;
		
		it = std::find_if(m_comps.begin(), m_comps.end(),
				  find_comp(c->r));

		

		
		
		
		if (it == m_comps.end())
		{
			
			bool Flag = false;
			for(int i=0;i < m_comps.size();i++)
			{
				if(getCompName(i) == c->v)
				{
					c->r = m_comps[i]._ref;
					//m_comps[i]._sm.m_obj->get_ports();
					//m_comps[i]._sm.m_obj._retn()->get_ports()[0][0]->
				}
			}
			
		}
		else
		{
			
			Comp& cm(*it);
			cm._sm.worker();
		}
	  
	  
  }

  void MultipleOrderedEC::LoadRules()
  {
	  mutex_2.lock();
	  for(int h=0;h < rs.size();h++)
	  {
		  for(int i=0;i < rs[h].ar.size();i++)
		  {
			  for(int j=0;j <  m_comps.size();j++)
			  {
				ComponentProfile *mc = m_comps[j]._sm.m_obj->get_component_profile();
				std::string Name = (const char*)mc->instance_name;
				
				delete mc;
				if(Name == rs[h].ar[i].name)
				{
					rs[h].ar[i].r = m_comps[j]._ref;
				}
			  }
		  }
		  for(int i=0;i < rs[h].rs.size();i++)
		  {
			  for(int j=0;j < rs[h].rs[i].SR.size();j++)
			  {
				  for(int k=0;k < rs[h].rs[i].SR[j].size();k++)
				  {
					for(int l=0;l < m_comps.size();l++)
					{
						ComponentProfile *mc = m_comps[l]._sm.m_obj->get_component_profile();
						std::string Name = (const char*)mc->instance_name;
						
						delete mc;
						
						if(Name == rs[h].rs[i].SR[j][k].v)
						{
							rs[h].rs[i].SR[j][k].r = m_comps[l]._ref;
							
						}
					}
				  }
			  }
		  }
	  }
	  mutex_2.unlock();


  }

  void MultipleOrderedEC::LoadRuleGUI(std::vector<main_Rule> &RS_d)
  {

	  m_worker.mutex_.lock();

	  rs.clear();
	  rs = RS_d;

	  //LoadRules();

	  m_worker.mutex_.unlock();
  }

  void MultipleOrderedEC::LoadRule()
  {

	  
	m_worker.mutex_.lock();
	
	
	
	
	for(int h=0;h < rs.size();h++)
		rs[h].rs.clear();
	rs.clear();

	
	LoadMainRule(rs, FileName);

	//LoadRules();
	

	m_worker.mutex_.unlock();
	

  }


  int MultipleOrderedEC::svc(void)
  {
	  RTC_TRACE(("svc()"));
      int count(0);

	  LoadRule();
	  
	  
	  do{
		  

		  

		  
		  m_worker.mutex_.lock();
		  //LoadRules();
		  
			while (!m_worker.running_)
			{
				m_worker.cond_.wait();
			}
			
			coil::TimeValue t0(coil::gettimeofday());
			if (m_worker.running_)
			{
				
				//std::cout << m_comps.size() << std::endl;
				for(int i=0;i < rs.size();i++)
				{
					bool S = true;
					for(int j=0;j < rs[i].ar.size();j++)
					{
						bool Flag = false;
						for(int k=0;k < m_comps.size();k++)
						{
							if(rs[i].ar[j].r == m_comps[k]._ref)
							{
								Flag = true;
								if(rs[i].ar[j].state == -1)
								{

								}
								else
								{
									if(rs[i].ar[j].state != m_comps[k]._sm.get_state())
									{
										S = false;
									}
								}
							}
						}
						if(!Flag)
						{
							
							for(int k=0;k < m_comps.size();k++)
							{
								if(getCompName(k) == rs[i].ar[j].name)
								{
									rs[i].ar[j].r = m_comps[k]._ref;
									if(rs[i].ar[j].state == -1)
									{

									}
									else
									{
										if(rs[i].ar[j].state != m_comps[k]._sm.get_state())
										{
											S = false;
										}
									}
								}
							}
						}

					}

					
					if(S)
					{
						r_num = i;
						break;
					}
				}

				
				{
				
				
				if(r_num < rs.size())
				{
					for(int i=0;i < rs[r_num].rs.size();i++)
					{
						
						//std::cout << rs[r_num].rs[i].SR.size() << std::endl;
						if(rs[r_num].rs[i].SR.size() == 0)
						{

						}
						else if(rs[r_num].rs[i].SR.size() == 1)
						{
							for(int j=0;j < rs[r_num].rs[i].SR[0].size();j++)
							{
								rs[r_num].rs[i].SR[0][j].s = 1;
								workerComp(&rs[r_num].rs[i].SR[0][j]);
								rs[r_num].rs[i].SR[0][j].s = 0;

							}
						}
						else
						{
							int p_num = rs[r_num].rs[i].SR.size();
							MPTask **m_task = new MPTask *[p_num];
							for(int j=0;j < p_num;j++)
							{
								
								m_task[j] = new MPTask(this);
								for(int k=0;k < rs[r_num].rs[i].SR[j].size();k++)
								{
									m_task[j]->addComp(&rs[r_num].rs[i].SR[j][k],i,j,k);
								}
								m_task[j]->activate();
							}

							for(int j=0;j < p_num;j++)
							{
								m_task[j]->wait();
								m_task[j]->close();
								delete m_task[j];
							}
							coil::TimeValue T0(coil::gettimeofday());
				
							/*coil::Task *mTask = new coil::Task();
							mTask->close();
							delete mTask;

							coil::TimeValue T1(coil::gettimeofday());
							std::cout << T1 - T0 << std::endl;*/

							

							delete m_task;
						}
					}
				}

			  }
			  
			}
			
			m_worker.mutex_.unlock();
			coil::TimeValue t1(coil::gettimeofday());
			//std::cout << t1 - t0 << std::endl;
			if (count > 1000)
			  {
				RTC_PARANOID(("Period:    %f [s]", (double)m_period));
				RTC_PARANOID(("Execution: %f [s]", (double)(t1 - t0)));
				RTC_PARANOID(("Sleep:     %f [s]", (double)(m_period - (t1 - t0))));
			  }
			coil::TimeValue t2(coil::gettimeofday());
			if (!m_nowait && m_period > (t1 - t0))
			  {
				if (count > 1000) { RTC_PARANOID(("sleeping...")); }
				coil::sleep((coil::TimeValue)(m_period - (t1 - t0)));
			  }
			if (count > 1000)
			  {
				coil::TimeValue t3(coil::gettimeofday());
				RTC_PARANOID(("Slept:     %f [s]", (double)(t3 - t2)));
				count = 0;
			  }
			++count;

			
			
	  }while (m_svc);

    
    return 0;
  }


};


extern "C"
{
   void MultipleOrderedECInit(RTC::Manager* manager)
  {
    manager->registerECFactory("MultipleOrderedEC",
			       RTC::ECCreate<RTC::MultipleOrderedEC>,
			       RTC::ECDelete<RTC::MultipleOrderedEC>);
  }
};
