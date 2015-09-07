/*!
* @file  FEComp.cpp
* @brief 直列ブロックのウィジェット
*
*/

#include <QtWidgets>
#include "FEComp.h"




using namespace RTC;
using namespace std;


/**
*@brief 直列ブロックのウィジェットのコンストラクタ
* @param parent 親ウィジェット
*/
FEComp::FEComp(QWidget *parent)
    : QWidget(parent)
{
	this->CL = new QVBoxLayout();
	this->setLayout(this->CL);
}

