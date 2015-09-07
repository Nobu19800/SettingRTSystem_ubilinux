/*!
* @file  AddButton2.cpp
* @brief 並列ブロック追加ボタン、並列ブロックの先頭に直列ブロック追加ボタン
*
*/

#include "AddButton2.h"

#include <QtWidgets>



/**
*@brief 並列ブロック追加ボタン、並列ブロックの先頭に直列ブロック追加ボタンのコンストラクタ
* @param text 表示テキスト
* @param parent 親ウィジェット
*/
AddButton2::AddButton2(QString text, QWidget *parent)
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
void AddButton2::clickedSlot()
{
	clicked(Cl);
}