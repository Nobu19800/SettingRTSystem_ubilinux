#include "AddButton2.h"

#include <QtWidgets>


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


void AddButton2::clickedSlot()
{
	clicked(Cl);
}