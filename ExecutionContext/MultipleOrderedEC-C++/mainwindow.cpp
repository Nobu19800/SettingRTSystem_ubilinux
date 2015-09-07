/*!
* @file  mainwindow.cpp
* @brief メインウインドウ
*
*/

#include <QLabel>
#include <QtWidgets>

#include "mainwindow.h"
#include "FileStreamFunc.h"






/**
*@brief メインウインドウのコンストラクタ
* @param ec 実行コンテキストオブジェクト
*/
MainWindow::MainWindow(RTC::MultipleOrderedEC *ec)
{
	
	
	tc = QTextCodec::codecForLocale();

	
	
    QVBoxLayout *layout = new QVBoxLayout;

	 
	

	this->m_ec = ec;
	SC = new SetComp(ec);
	connect(SC, SIGNAL(UpdateSizeSignal(int , int )),
            this, SLOT(m_resize(int , int )));

	layout->addWidget(SC);

	layout->addStretch();
	UB = new QPushButton(tc->toUnicode("更新"));
	layout->addWidget(UB);

	connect(UB, SIGNAL(clicked()),
            this, SLOT(UpdateComp()));

	QPushButton *DB = new QPushButton(tc->toUnicode("追加"));
	layout->addWidget(DB);

	connect(DB, SIGNAL(clicked()),
            SC, SLOT(CreateComp()));

	

    widget = new QWidget;
    widget->setLayout(layout);

	
	QScrollArea *area = new QScrollArea();
	area->setWidget(widget);
	
	

    setCentralWidget(area);
    setWindowTitle(tr("MultipleOrderedECGUI"));
    setUnifiedTitleAndToolBarOnMac(true);

	
	SC->UpdateSizeSlot();


	createAction();
	createMenus();
}

/**
*@brief サイズを変更するときに呼び出されるスロット
* @param w 幅
* @param h 高さ
*/
void MainWindow::m_resize(int w, int h)
{
	widget->resize(w, h);
}

/**
*@brief RTCが追加、削除されたときに呼び出されるスロット
*/
void MainWindow::UpdateComp()
{
	SC->UpdateComps();
	SC->UpdateComp2();
}

/**
*@brief アクションの作成の関数
*/
void MainWindow::createAction()
{
	newAct = new QAction(tr("&New..."),this);
	newAct->setShortcuts(QKeySequence::New);
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));


	openAct = new QAction(tr("&Open..."),this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));


    saveAct = new QAction(tr("&Save"),this);
    saveAct->setShortcuts(QKeySequence::Save);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

	saveAsAct = new QAction(tr("&Save &As"), this);
	saveAsAct->setShortcuts(QKeySequence::SaveAs);
	connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));
}

/**
*@brief メニューの作成の関数
*/
void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
	fileMenu->addAction(saveAsAct);
	

}

/**
*@brief ファイル読み込みスロット
*/
void MainWindow::open()
{
	QString fileName = QFileDialog::getOpenFileName(this,
							tc->toUnicode("開く"), "",
							tr("Config File (*.conf);;Lua File (*.lua);;All Files (*)"));
	

	QByteArray ba = fileName.toLocal8Bit();
	SC->open(ba);

	m_ec->FileName = ba;

}

/**
*@brief ファイル保存のスロット
* @return 成功でTrue、失敗でFalse
*/
bool MainWindow::save()
{
	
	
	if (m_ec->FileName == "")
	{
		
		return saveAs();
	}
	else
	{
		PathList pl = PathList(m_ec->FileName);
		if (pl.cxt == "lua")
		{
			return saveAs();
		}
		else
		{
			return SC->save(m_ec->FileName.c_str());
		}
		
		
	}
}

/**
*@brief 別のファイル保存のスロット
* @return 成功でTrue、失敗でFalse
*/
bool MainWindow::saveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this,
							tc->toUnicode("保存"), "",
							tr("Config File (*.conf);;All Files (*)"));
	if (fileName.isEmpty())
        return false;

	QByteArray ba = fileName.toLocal8Bit();
	

	m_ec->FileName = ba;
    return SC->save(ba);
}

/**
*@brief 初期化のスロット
*/
void MainWindow::newFile()
{
	SC->newFile();

	m_ec->FileName = "";
    
}

/**
*@brief 実行順序をGUIに反映させる関数
* @param rs 並列ブロックのリスト
*/
void MainWindow::UpdateRTC(std::vector<Rule> &rs)
{
	SC->UpdateRTC(rs);
	
}