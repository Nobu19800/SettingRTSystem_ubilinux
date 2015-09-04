#ifndef FECOMP_H
#define FECOMP_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include "ExComp.h"



QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
QT_END_NAMESPACE

class ExComp;

/*
*直列ブロックのウィジェット
*/

class FEComp : public QWidget
{
	Q_OBJECT
public:
	FEComp(QWidget *parent = 0);
	std::vector<ExComp *> ECS;
	QVBoxLayout *CL;

};

#endif