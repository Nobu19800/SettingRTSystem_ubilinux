#include "AddButton.h"

#include <QtWidgets>


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


void AddButton::clickedSlot()
{
	clicked(Fc);
}