
#include <QtWidgets>
#include "FEComp.h"




using namespace RTC;
using namespace std;


FEComp::FEComp(QWidget *parent)
    : QWidget(parent)
{
	this->CL = new QVBoxLayout();
	this->setLayout(this->CL);
}

