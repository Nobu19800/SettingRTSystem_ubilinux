/*!
* @file  AddButton3.cpp
* @brief 並列ブロック削除ボタンを含むウィジェット
*
*/

#include "AddButton3.h"

#include <QtWidgets>


/**
*@brief 並列ブロック削除ボタンを含むウィジェットのコンストラクタ
* @param text 表示テキスト
* @param parent 親ウィジェット
*/
AddButton3::AddButton3(QString text, QWidget *parent)
    : QWidget(parent)
{
	PB = new QPushButton(text);

	QVBoxLayout *mainLayout = new QVBoxLayout;


	connect(PB, SIGNAL(clicked()),
            this, SLOT(clickedSlot()));

	mainLayout->addWidget(PB);
	



	setLayout(mainLayout);
}

/**
*@brief ボタンクリック時に呼び出すスロット
*/
void AddButton3::clickedSlot()
{
	clicked(Vl, c);
}