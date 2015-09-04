#include "AddButton3.h"

#include <QtWidgets>


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


void AddButton3::clickedSlot()
{
	clicked(Vl, c);
}