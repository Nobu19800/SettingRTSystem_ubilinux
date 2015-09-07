/*!
* @file  AddButton.cpp
* @brief 直列ブロックの先頭にブロックを追加するボタン
*
*/

#include "AddButton.h"

#include <QtWidgets>


/**
*@brief 直列ブロックの先頭にブロックを追加するボタンのコンストラクタ
* @param text 表示テキスト
* @param parent 親ウィジェット
*/
AddButton::AddButton(QString text, QWidget *parent)
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
void AddButton::clickedSlot()
{
	clicked(Fc);
}