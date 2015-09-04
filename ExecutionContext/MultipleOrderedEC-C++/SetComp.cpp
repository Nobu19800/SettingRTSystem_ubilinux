
#include <QtWidgets>
#include <sstream>
#include "SetComp.h"

using namespace std;



SetComp::SetComp(RTC::MultipleOrderedEC *ec, QWidget *parent)
    : QTabWidget(parent)
{

	tc = QTextCodec::codecForLocale();

	

	this->m_ec = ec;

	//CreateComp();

	connect(this, SIGNAL(currentChanged(int)),
            this, SLOT(UpdateSizeSlot()));

	

	time = new QTimer(this);

	connect( time, SIGNAL(timeout()),
	   this, SLOT(UpdateEC()) );

	time->start(100);

	

	if(!open(this->m_ec->FileName.c_str()))
		newFile();
}

void SetComp::DeleteComp(FrameComp *fc)
{
	{
		std::vector<FrameComp *>::iterator it = FCS.begin();

		while (it != FCS.end()) {
			if (*it == fc) {
				it = FCS.erase(it);
			}
			else {
				++it;
			}
		}
	}

	this->removeTab(this->indexOf(fc));
	this->removeTab(this->indexOf(fc->cf));
	
	fc->cf->close();
	fc->close();
}

void SetComp::CreateComp()
{
	FrameComp *FC = new FrameComp(m_ec, this);
	connect(FC, SIGNAL(UpdateSizeSignal()),
            this, SLOT(UpdateSizeSlot()));

	FCS.push_back(FC);


	std::ostringstream stream;
	stream << FCS.size();
	std::string N = "system:" + stream.str();
	addTab(FC, tc->toUnicode(N.c_str()));
	N = N + "条件";
	addTab(FC->cf, tc->toUnicode(N.c_str()));

	/*FC->cf->resetComp();
	for(int i=0;i < rtclist.size();i++)
	{
		FC->cf->addComp(rtclist[i].c_str());
	}*/


	
}

bool SetComp::save(const char *Name)
{
	std::vector<main_Rule> mR;

	ofstream ofs2(Name, ios_base::out | ios_base::trunc | ios_base::binary );
	if(!ofs2)return false;


	int c = FCS.size();
	ofs2.write( (char*)&c, sizeof(c) );
	for(int i=0;i < FCS.size();i++)
	{
		FCS[i]->save(ofs2, mR);
	}
	
	m_ec->LoadRuleGUI(mR);

	ofs2.close();
	return true;
}

void SetComp::UpdateComp2()
{
	for(int h=0;h < FCS.size();h++)
	{
		FCS[h]->cf->resetComp();
		
		for(int i=0;i < rtclist.size();i++)
		{
			FCS[h]->cf->addComp(rtclist[i].c_str());
		}


		FCS[h]->UpdateComp2(rtclist, rtclist2);
	}
	
	for(int h=0;h < m_ec->rs.size();h++)
	{
		
		if(FCS.size() > h)
		{
			

			std::vector<add_Rule> ar = m_ec->rs[h].ar;
			
			
			for(int i=0;i < ar.size();i++)
			{
				
				//FCS[h]->cf->addComp(ar[i].name);
				for(int j=0;j < FCS[h]->cf->Cl.size();j++)
				{
					if(FCS[h]->cf->Cl[j]->Name == ar[i].name)
					{
						if(ar[i].state == -1)
						{
							FCS[h]->cf->Cl[j]->c_none->setChecked(true);
						}
						else if(ar[i].state == RTC::CREATED_STATE)
						{
							FCS[h]->cf->Cl[j]->c_created->setChecked(true);
						}
						else if(ar[i].state == RTC::INACTIVE_STATE)
						{
							FCS[h]->cf->Cl[j]->c_inactive->setChecked(true);
						}
						else if(ar[i].state == RTC::ACTIVE_STATE)
						{
							FCS[h]->cf->Cl[j]->c_active->setChecked(true);
						}
						else if(ar[i].state == RTC::ERROR_STATE)
						{
							FCS[h]->cf->Cl[j]->c_error->setChecked(true);
							
						}
					}
				}
			}

			


			std::vector<Rule> rs = m_ec->rs[h].rs;

		
			for(int i=0;i < rs.size();i++)
			{
				if(FCS[h]->Comps.size() > i)
				{
					for(int j=0;j < rs[i].SR.size();j++)
					{
						if(FCS[h]->Comps[i]->VL.size() > j)
						{
							FEComp *fd = dynamic_cast<FEComp*>(FCS[h]->Comps[i]->VL[j]->layout()->itemAt(1)->widget());
							
							for(int k=0;k < rs[i].SR[j].size();k++)
							{
								if(fd->ECS.size() > k)
								{
									
									for(int l=0;l < fd->ECS[k]->CB->count();l++)
									{
										if(fd->ECS[k]->CB->itemText(l) == rs[i].SR[j][k].v.c_str())
										{
											fd->ECS[k]->CB->setCurrentIndex(l);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void SetComp::UpdateComps()
{
	
	
	
	int Size = m_ec->getCompNum();
	

	std::vector<std::string> rtclist3;
	std::vector<CORBA::Object_ptr> rtclist4;

	//std::cout << Size << std::endl;

	

	for(int i=0;i < Size;i++)
	{
		
		rtclist3.push_back(m_ec->getCompName(i));
	}

	if(rtclist == rtclist3)
	{
		

	}
	else
	{
		

		rtclist.clear();
		rtclist = rtclist3;

		
		UpdateComp2();

		
	}
}




bool SetComp::open(const char *Name)
{
	std::vector<main_Rule> mR;

	if(!LoadMainRule(mR, Name))
		return false;

	for(int i=0;i < FCS.size();i++)
	{
		this->removeTab(this->indexOf(FCS[i]));
		this->removeTab(this->indexOf(FCS[i]->cf));

		FCS[i]->cf->close();
		FCS[i]->close();
	}
	
	FCS.clear();
	
	for(int i=0;i < mR.size();i++)
	{
		CreateComp();
		
		//FCS[i]->openb(ifs,mR);
		FCS[i]->SetFrame(mR[i]);
		
	}


	m_ec->LoadRuleGUI(mR);

	

	

	UpdateComps();
	UpdateComp2();
	


	return true;
}

void SetComp::UpdateEC()
{
	for(int h=0;h < m_ec->rs.size();h++)
	{
		std::vector<Rule> rs = m_ec->rs[h].rs;
		if(FCS.size() > h)
		{
			FCS[h]->UpdateEC(rs);
		}
	}

	UpdateComps();
	
}

void SetComp::UpdateSizeSlot()
{
	
	int maxX = 0;
	int maxY = 0;
	/*for(int i=0;i < FCS.size();i++)
	{
		if(maxX < FCS[i]->X)
			maxX = FCS[i]->X;
		if(maxY < FCS[i]->Y)
			maxY = FCS[i]->Y;

		
	}
	if(maxX < 450)
		maxX = 450;
	if(maxY < 600)
		maxY = 600;*/

	if(this->currentIndex()%2 == 0)
	{
		if(this->currentIndex()/2 < FCS.size())
		{
			maxX = FCS[this->currentIndex()/2]->X;
			maxY = FCS[this->currentIndex()/2]->Y;
		}
	}

	if(maxX < 450)
		maxX = 450;
	if(maxY < 600)
		maxY = 600;

	

	/*for(int i=0;i < FCS.size();i++)
	{
		FCS[i]->resize(maxX, maxY);
		FCS[i]->cf->resize(maxX, maxY);
	}
	

	resize(maxX, maxY);*/
	UpdateSizeSignal(maxX, maxY);

	UpdateComps();

	
}

void SetComp::UpdateComp()
{
	for(int i=0;i < FCS.size();i++)
	{
		//FCS[i]->UpdateComp();
	}
}

void SetComp::UpdateRTC(std::vector<Rule> &rs)
{
	FCS[0]->UpdateRTC(rs);
}

void SetComp::newFile()
{
	for(int i=0;i < FCS.size();i++)
	{
		this->removeTab(this->indexOf(FCS[i]));
		this->removeTab(this->indexOf(FCS[i]->cf));

		FCS[i]->cf->close();
		FCS[i]->close();
	}
		

	
	FCS.clear();

	CreateComp();
	
	FCS[0]->newFile();


}