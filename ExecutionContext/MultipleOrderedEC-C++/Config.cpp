/*!
* @file  Config.cpp
* @brief 実行条件のウィジェット
*
*/

#include <QtWidgets>
#include "Config.h"




using namespace RTC;
using namespace std;


/**
*@brief 実行条件のレイアウト内のウィジェットを全て削除する関数
* @param lt 実行条件のレイアウト
*/
void CrearLayout(QLayout *lt)
{
	QLayoutItem* item;
	while ((item = lt->takeAt(1)) != NULL)
	{
		item->widget()->close();
		delete item->widget();
		delete item;
	}

}

/**
*@brief 実行条件のウィジェットのコンストラクタ
*/
Configs::Configs(QWidget *parent)
    : QWidget(parent)
{
	tc = QTextCodec::codecForLocale();

	
	componentName = new QLabel(tc->toUnicode("コンポーネント"));
	noneName = new QLabel(tc->toUnicode("条件なし"));
	createdName = new QLabel(tc->toUnicode("CREATED"));
	inactiveName = new QLabel(tc->toUnicode("INACTIVE"));
	activeName = new QLabel(tc->toUnicode("ACTIVE"));
	errorName = new QLabel(tc->toUnicode("ERROR"));

	componentName->setFrameStyle( QFrame::Box);
	noneName->setFrameStyle( QFrame::Box);
	createdName->setFrameStyle( QFrame::Box);
	inactiveName->setFrameStyle( QFrame::Box);
	activeName->setFrameStyle( QFrame::Box);
	errorName->setFrameStyle( QFrame::Box);

	Nlist = new QVBoxLayout();
	

	

	


	Nlist->addWidget(componentName);

	Dl = new QHBoxLayout();
	Dl->addWidget(noneName);
	Dl->addWidget(createdName);
	Dl->addWidget(inactiveName);
	Dl->addWidget(activeName);
	Dl->addWidget(errorName);

	QWidget *Dw = new QWidget();
	Dw->setLayout(Dl);


	CRlist = new QVBoxLayout();

	CRlist->addWidget(Dw);

	QHBoxLayout *subLayout = new QHBoxLayout();
	subLayout->addLayout(Nlist);
	subLayout->addLayout(CRlist);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(subLayout);
	mainLayout->addStretch();


	setLayout(mainLayout);

	resetComp();
	
	
	

}

/**
*@brief RTCが追加されたときに反映する関数
* @param name RTC名
*/
void Configs::addComp(std::string name)
{
	CompList *cl = new CompList();
	cl->Name = name;
	cl->name = new QLabel(tc->toUnicode(name.c_str()));
	cl->c_none = new QRadioButton();
	cl->c_created = new QRadioButton();
	cl->c_inactive = new QRadioButton();
	cl->c_active = new QRadioButton();
	cl->c_error = new QRadioButton();

	cl->c_none->setChecked(true);
	
	cl->Lo = new QHBoxLayout();
	cl->Lw = new QWidget();
	


	Nlist->addWidget(cl->name);
	cl->Lo->addWidget(cl->c_none,0,Qt::AlignCenter);
	cl->Lo->addWidget(cl->c_created,0,Qt::AlignCenter);
	cl->Lo->addWidget(cl->c_inactive,0,Qt::AlignCenter);
	cl->Lo->addWidget(cl->c_active,0,Qt::AlignCenter);
	cl->Lo->addWidget(cl->c_error,0,Qt::AlignCenter);
	cl->Lw->setLayout(cl->Lo);
	CRlist->addWidget(cl->Lw);

	Cl.push_back(cl);

	

}


/**
*@brief 初期化
*/
void Configs::resetComp()
{
	Cl.clear();
	CrearLayout(Nlist);
	CrearLayout(CRlist);
	
	

}