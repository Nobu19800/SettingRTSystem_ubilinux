
#include <QtWidgets>
#include "ExComp.h"


using namespace RTC;
using namespace std;


ExComp::ExComp(QWidget *parent)
    : QWidget(parent)
{
	tc = QTextCodec::codecForLocale();
	CB = new QComboBox();

	this->setMaximumSize(100, 160);
	this->setMinimumSize(100, 160);


	QVBoxLayout *subLayout = new QVBoxLayout();
	subWidget = new QWidget(this);
	subWidget->setLayout(subLayout);
	QPalette palette = QPalette();
	palette.setColor(QPalette::Background, QColor(140, 140, 140));
	subWidget->setPalette(palette);
	subWidget->setForegroundRole(QPalette::Dark);

	subWidget->setAutoFillBackground(true);

	

	/*connect(CB, SIGNAL(currentIndexChanged(int)),
            this, SLOT(SelectComp()));*/

	

	BT = new QPushButton(tc->toUnicode("削除"));

	connect(BT, SIGNAL(clicked()),
            this, SLOT(DeleteComp()));


	DT = new QPushButton(tc->toUnicode("追加"));

	connect(DT, SIGNAL(clicked()),
            this, SLOT(AddCompSlot()));

	
	QLabel *Lb = new QLabel();


	QVBoxLayout *mainLayout = new QVBoxLayout;
	subLayout->addStretch();
	subLayout->addWidget(CB);
	subLayout->addWidget(BT);
	subLayout->addStretch();
	mainLayout->addWidget(subWidget);
	mainLayout->addWidget(Lb);
	mainLayout->addWidget(DT);
	mainLayout->addStretch();

	Lb->setPixmap(QPixmap(":/images/arrow.png").scaled(DT->sizeHint()));

	
	

	
	setLayout(mainLayout);
	
}



void ExComp::AddCompSlot()
{
	AddCompSignal(this, Fc);
}

void ExComp::UpdateComp(std::vector<std::string> &rtclist, std::vector<CORBA::Object_ptr> &rtclist2)
{
	int Id = CB->currentIndex();
	CB->clear();
	
	for(int i=0;i < rtclist.size();i++)
	{
		CB->addItem(tr(rtclist[i].c_str()));
	}

	if(Id < rtclist.size())
		CB->setCurrentIndex(Id);

	

}

void ExComp::DeleteComp()
{

	std::vector<ExComp *>::iterator it = Fc->ECS.begin();
	while (it != Fc->ECS.end()) {
		if (*it == this) {
			it = Fc->ECS.erase(it);
		}
		else {
			++it;
		}
	}


	Fc->CL->removeWidget(this);

	this->close();


}




CompLayout::CompLayout()
{

}