
#include <QtWidgets>
#include "FrameComp.h"
#include "CompSearch.h"




using namespace RTC;
using namespace std;




FrameComp::FrameComp(RTC::MultipleOrderedEC *ec, SetComp *sc, QWidget *parent)
    : QWidget(parent)
{
	tc = QTextCodec::codecForLocale();

	


	m_ec = ec;


	

	mainLayout = new QVBoxLayout();

	
	QPushButton *TB = new QPushButton(tc->toUnicode("追加"));
	connect(TB, SIGNAL(clicked()),
            this, SLOT(AddCompsT()));

	

	mainLayout->addWidget(TB);

	QPushButton *DB = new QPushButton(tc->toUnicode("削除"));
	connect(DB, SIGNAL(clicked()),
            this, SLOT(DeleteFrame()));

	mainLayout->addWidget(DB);



	
	
	

	setLayout(mainLayout);

	
	

	
	cf = new Configs();

	Sc = sc;

	X = 0;
	Y = 0;



	
}


void FrameComp::DeleteFrame()
{
	Sc->DeleteComp(this);
}


void FrameComp::AddCompSlot3(CompLayout *c)
{
	AddButton *AB2 = new AddButton(tc->toUnicode("追加"));
	

	connect(AB2, SIGNAL(clicked(FEComp *)),
            this, SLOT(AddCompSlot1(FEComp *)));


	FEComp *FC = new FEComp();

	AB2->Fc = FC;



	AddComp(FC);


	

	CLS.push_back(FC);

	
	QVBoxLayout *Vl = new QVBoxLayout();
	c->VL.push_back(Vl);

	

	QWidget *VD = new QWidget();
	QHBoxLayout *CP = new QHBoxLayout();
	CP->addWidget(AB2->PB);
	VD->setLayout(CP);

	

	VD->setMaximumWidth(100);
	VD->setMinimumWidth(100);

	

	Vl->addWidget(VD);
	Vl->addWidget(FC);

	QWidget *VW = new QWidget();
	VW->setLayout(Vl);

	AddButton3 *mBT = new AddButton3(tc->toUnicode("削除"));
	mBT->Vl = VW;
	mBT->c = c;

	Vl->addStretch();
	Vl->addWidget(mBT->PB);


	

	connect(mBT, SIGNAL(clicked(QWidget *, CompLayout *)),
            this, SLOT(DeleteComp(QWidget *, CompLayout *)));

	

	QPalette palette = QPalette();
	palette.setColor(QPalette::Background, QColor(0, 140, 140));
	VW->setPalette(palette);
	VW->setForegroundRole(QPalette::Dark);

	VW->setAutoFillBackground(true);

	VW->setFixedWidth(150);



	c->subLayout->insertWidget(0, VW);


	UpdateSize();

	//Sc->UpdateComp2();

	
}


void FrameComp::DeleteComp(QWidget *Vl, CompLayout *c)
{
	
	c->subLayout->removeWidget(Vl);
	Vl->close();

	
	

	{
		std::vector<QVBoxLayout *>::iterator it = c->VL.begin();

		while (it != c->VL.end()) {
			if (*it == Vl->layout()) {
				it = c->VL.erase(it);
			}
			else {
				++it;
			}
		}
	}

	


	


	if(c->VL.size() == 0 && Comps.size() > 1)
	{
		std::vector<CompLayout *>::iterator it = Comps.begin();

		while (it != Comps.end()) {
			if (*it == c) {
				it = Comps.erase(it);
			}
			else {
				++it;
			}
		}

		mainLayout->removeWidget(c->mainWidget);

	}


	UpdateSize();

	//Sc->UpdateComp2();
}

void FrameComp::AddCompSlot2(CompLayout *c)
{
	c->subLayout = new QHBoxLayout;
	AddCompSlot3(c);
	

	
	c->AB = new AddButton2(tc->toUnicode("追\n加"));
	c->AB->Cl = c;

	
	c->AB->PB->setMaximumSize(25, 100);
	c->AB->PB->setMinimumSize(25, 100);

	connect(c->AB, SIGNAL(clicked(CompLayout *)),
            this, SLOT(AddCompSlot3(CompLayout *)));

	
	
	c->subLayout->addWidget(c->AB->PB);
	c->subLayout->addStretch();
	




	


	
	AddButton2 *UB = new AddButton2(tc->toUnicode("追加"));
	UB->Cl = c;
	connect(UB, SIGNAL(clicked(CompLayout *)),
            this, SLOT(AddCompsU(CompLayout *)));

	
	
	

	c->mainLayout = new QVBoxLayout;
	c->mainWidget = new QWidget;
	c->mainWidget->setLayout(c->mainLayout);

	QWidget *sL = new QWidget();
	sL->setLayout(c->subLayout);

	QPalette palette = QPalette();
	palette.setColor(QPalette::Background, QColor(140, 0, 140));
	sL->setPalette(palette);
	sL->setForegroundRole(QPalette::Dark);

	sL->setAutoFillBackground(true);

	c->Lb = new QLabel();

	c->mainLayout->addWidget(sL);
	c->mainLayout->addWidget(c->Lb);
	c->mainLayout->addWidget(UB->PB);


	
	
	


	UpdateSize();

	//Sc->UpdateComp2();
}


void FrameComp::UpdateSize()
{
	int Ws = 0;
	int Hs = 0;
	int Ks = 0;
	for(int i=0;i < Comps.size();i++)
	{
		
		Ks += 1;
		int tHs = 0;
		if(Ws < Comps[i]->VL.size())
		{
			Ws = Comps[i]->VL.size();
		}
		for(int j=0;j < Comps[i]->VL.size();j++)
		{
			if(tHs < Comps[i]->VL[j]->itemAt(1)->widget()->layout()->count())
			{
				tHs = Comps[i]->VL[j]->itemAt(1)->widget()->layout()->count();
				//std::cout << tHs << std::endl;
			}
		}
		Hs += tHs;
	}
	int ws = Ws*180+90;
	int hs = Hs*200+70+Ks*200;

	X = ws;
	Y = hs;

	//std::cout << Ws << "\t" << Hs << "\t" << Ks << std::endl;

	
	UpdateSizeSignal();
	

	for(int i=0;i < Comps.size();i++)
		Comps[i]->Lb->setPixmap(QPixmap(":/images/arrow.png").scaled(Ws*180,30));
}

void FrameComp::AddCompsT()
{
	InsertComps2(2);


}

void FrameComp::AddCompsU(CompLayout *c)
{
	int t = mainLayout->indexOf(c->mainWidget);
	InsertComps2(t+1);
}



void FrameComp::AddComps2()
{
	CompLayout *CL = new CompLayout();
	AddCompSlot2(CL);
	Comps.push_back(CL);
	mainLayout->addWidget(CL->mainWidget);

	UpdateSize();

	//Sc->UpdateComp2();


	

}

void FrameComp::InsertComps2(int num)
{
	CompLayout *CL = new CompLayout();
	AddCompSlot2(CL);
	Comps.push_back(CL);
	
	mainLayout->insertWidget(num, CL->mainWidget);

	UpdateSize();

	//Sc->UpdateComp2();


}

void FrameComp::AddComp(FEComp *FC)
{
	ExComp *EC = new ExComp();
	
	FC->ECS.push_back(EC);
	FC->CL->addWidget(EC);
	EC->Fc = FC;
	
	connect(EC, SIGNAL(AddCompSignal(ExComp *, FEComp *)),
            this, SLOT(AddCompSlot(ExComp *, FEComp *)));


	EC->UpdateComp(Sc->rtclist, Sc->rtclist2);
	
	UpdateSize();

	//Sc->UpdateComp2();
}

void FrameComp::InsertComp(int num, FEComp *FC)
{
	ExComp *EC = new ExComp();
	
	FC->ECS.push_back(EC);
	FC->CL->insertWidget(num, EC);
	EC->Fc = FC;
	connect(EC, SIGNAL(AddCompSignal(ExComp *, FEComp *)),
            this, SLOT(AddCompSlot(ExComp *, FEComp *)));

	EC->UpdateComp(Sc->rtclist, Sc->rtclist2);


	UpdateSize();

	//Sc->UpdateComp2();
}

void FrameComp::UpdateComp2(std::vector<std::string> rtclist, std::vector<CORBA::Object_ptr> rtclist2)
{
	for(int i=0;i < CLS.size();i++)
	{
		for(int j=0;j < CLS[i]->ECS.size();j++)
		{
			CLS[i]->ECS[j]->UpdateComp(rtclist,rtclist2);
		}
	}
}



void FrameComp::AddCompSlot(ExComp *ec, FEComp *fc)
{
	InsertComp(fc->CL->indexOf(ec)+1, fc);
}

void FrameComp::AddCompSlot1(FEComp *fc)
{
	InsertComp(0, fc);
}


void FrameComp::SetFrame(main_Rule &mR)
{
	
	int r = mR.ar.size();
	for(int i=0;i < r;i++)
	{
		
		for(int j=0;j < this->cf->Cl.size();j++)
		{
			
			int v = mR.ar[i].state;
			if(this->cf->Cl[j]->Name == mR.ar[i].name)
			{
				

				if(v == -1)
				{
					this->cf->Cl[j]->c_none->setChecked(true);
				}
				else if(v == RTC::CREATED_STATE)
				{
					this->cf->Cl[j]->c_created->setChecked(true);
				}
				else if(v == RTC::INACTIVE_STATE)
				{
					this->cf->Cl[j]->c_inactive->setChecked(true);
				}
				else if(v == RTC::ACTIVE_STATE)
				{
					this->cf->Cl[j]->c_active->setChecked(true);
				}
				else if(v == RTC::ERROR_STATE)
				{
					this->cf->Cl[j]->c_error->setChecked(true);
				}

			}
		}
	}

		
	

	for(int i=0;i < mR.rs.size();i++)
	{
		AddComps2();
		
		
		
		for(int j=0;j < mR.rs[i].SR.size();j++)
		{
			

			if(j != 0)
				AddCompSlot3(Comps[i]);



			FEComp *fd = dynamic_cast<FEComp*>(Comps[i]->VL[j]->layout()->itemAt(1)->widget());

			for(int k=0;k < mR.rs[i].SR[j].size();k++)
			{
				if(k != 0)
					AddComp(fd);
				

				for(int l=0;l < fd->ECS[k]->CB->count();l++)
				{
					if(fd->ECS[k]->CB->itemText(l) == mR.rs[i].SR[j][k].v.c_str())
						fd->ECS[k]->CB->setCurrentIndex(l);
				}
				
			}
			
		}
		
	}
}

bool FrameComp::openb(std::ifstream &ifs, std::vector<main_Rule> &mR)
{
	main_Rule rs;
	
	for(int i=0;i < Comps.size();i++)
	{
		Comps[i]->mainWidget->close();
	}
	Comps.clear();

	int r;
	ifs.read( (char*)&r, sizeof(r) );
	for(int i=0;i < r;i++)
	{
		add_Rule ar;

		string s;
		s = ReadString( ifs );

		ar.name = s;

		int v;
		ifs.read( (char*)&v, sizeof(v) );

		ar.state = v;

		

		for(int j=0;j < this->cf->Cl.size();j++)
		{
			if(this->cf->Cl[j]->Name == s)
			{
				

				if(v == -1)
				{
					this->cf->Cl[i]->c_none->setChecked(true);
				}
				else if(v == RTC::CREATED_STATE)
				{
					this->cf->Cl[i]->c_created->setChecked(true);
				}
				else if(v == RTC::INACTIVE_STATE)
				{
					this->cf->Cl[i]->c_inactive->setChecked(true);
				}
				else if(v == RTC::ACTIVE_STATE)
				{
					this->cf->Cl[i]->c_active->setChecked(true);
				}
				else if(v == RTC::ERROR_STATE)
				{
					this->cf->Cl[i]->c_error->setChecked(true);
				}

			}
		}


		rs.ar.push_back(ar);
		
	}




	
	int c;
	ifs.read( (char*)&c, sizeof(c) );

	for(int i=0;i < c;i++)
	{
		Rule r;

		AddComps2();
		
		
		int d;
		ifs.read( (char*)&d, sizeof(d) );
		for(int j=0;j < d;j++)
		{
			vector<sub_Rule> SRs;

			if(j != 0)
				AddCompSlot3(Comps[i]);
			

			int e;
			ifs.read( (char*)&e, sizeof(e) );



			FEComp *fd = dynamic_cast<FEComp*>(Comps[i]->VL[j]->layout()->itemAt(1)->widget());

			for(int k=0;k < e;k++)
			{
				if(k != 0)
					AddComp(fd);
				string s;
				s = ReadString( ifs );

				for(int l=0;l < fd->ECS[k]->CB->count();l++)
				{
					if(fd->ECS[k]->CB->itemText(l) == s.c_str())
						fd->ECS[k]->CB->setCurrentIndex(l);
				}


				sub_Rule SR;
				SR.v = s;
				SR.s = 0;
				SRs.push_back(SR);
				
			}
			r.SR.push_back(SRs);
		}
		rs.rs.push_back(r);

		
		
		
	}

	mR.push_back(rs);

	

	return true;

	
}


bool FrameComp::open(std::vector<std::string> &Str, int &an, std::vector<main_Rule> &mR)
{
	main_Rule rs;

	bool flag = true;
	while(flag)
	{
		
	}

	return true;
}


bool FrameComp::save(ofstream &ofs2, std::vector<main_Rule> &mR)
{
	main_Rule rs;
	
	
	int r = this->cf->Cl.size();
	ofs2.write( (char*)&r, sizeof(r) );
	for(int i=0;i < r;i++)
	{
		 
		
		std::string cn = this->cf->Cl[i]->Name;
		
		
		
		WriteString(cn , ofs2 );
		
		int a = -1;
		

		if(this->cf->Cl[i]->c_none->isChecked())
		{
			a = -1;
		}
		else if(this->cf->Cl[i]->c_created->isChecked())
		{
			a = RTC::CREATED_STATE;
		}
		else if(this->cf->Cl[i]->c_inactive->isChecked())
		{
			a = RTC::INACTIVE_STATE;
		}
		else if(this->cf->Cl[i]->c_active->isChecked())
		{
			a = RTC::ACTIVE_STATE;
		}
		else if(this->cf->Cl[i]->c_error->isChecked())
		{
			a = RTC::ERROR_STATE;
		}

		
		
		ofs2.write( (char*)&a, sizeof(a) );

		add_Rule ar;
		ar.name = this->cf->Cl[i]->Name;
		ar.state = a;

		rs.ar.push_back(ar);

		
		
		
	}
	
	
	
	int c = Comps.size();
	ofs2.write( (char*)&c, sizeof(c) );
	

	for(int i=0;i < Comps.size();i++)
	{	


		Rule r;


		int d = Comps[i]->VL.size();
		

		ofs2.write( (char*)&d, sizeof(d) );
		

		for(int j=0;j < d;j++)
		{

			vector<sub_Rule> SRs;


			FEComp *fd = dynamic_cast<FEComp*>(Comps[i]->VL[j]->layout()->itemAt(1)->widget());
			int e = fd->ECS.size();
			ofs2.write( (char*)&e, sizeof(e) );
			
			for(int k=0;k < e;k++)
			{

				QString fd_text = fd->ECS[k]->CB->currentText();
				
				const char *N = fd_text.toLocal8Bit();
				WriteString(N , ofs2 );
				


				sub_Rule SR;

				SR.v = N;
				
				SR.s = 0;

				
				SRs.push_back(SR);


			}

			r.SR.push_back(SRs);
			
		}
		rs.rs.push_back(r);
	}

	

	
	mR.push_back(rs);
	//m_ec->LoadRuleGUI(rs);
	
	

	


	return true;
}



void FrameComp::UpdateEC(std::vector<Rule> &rs)
{				
	for(int i=0;i < rs.size();i++)
	{
		
		
		

		
		if(Comps.size() > i)
		{
			
			
			for(int j=0;j < rs[i].SR.size();j++)
			{
				
				if(Comps[i]->VL.size() > j)
				{
					FEComp *fd = dynamic_cast<FEComp*>(Comps[i]->VL[j]->layout()->itemAt(1)->widget());
					for(int k=0;k < rs[i].SR[j].size();k++)
					{
						
						if(fd->ECS.size() > k)
						{
							QPalette palette = QPalette();
							if(rs[i].SR[j][k].s == 0)
								palette.setColor(QPalette::Background, QColor(140, 140, 140));
							else
								palette.setColor(QPalette::Background, QColor(140, 140, 0));
							
							
							fd->ECS[k]->subWidget->setPalette(palette);
							fd->ECS[k]->subWidget->setForegroundRole(QPalette::Dark);

							fd->ECS[k]->subWidget->setAutoFillBackground(true);

							
							
							
						}
					}
				}

			}
			
		}
		
	}


	
}

void FrameComp::UpdateRTC(std::vector<Rule> &rs)
{
	
	
}

void FrameComp::newFile()
{
	for(int i=0;i < Comps.size();i++)
	{
		Comps[i]->mainWidget->close();
	}
	Comps.clear();

	

	AddComps2();
	

	
}