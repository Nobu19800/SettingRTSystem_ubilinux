#ifndef ADDBUTTON_H
#define ADDBUTTON_H

#include "ExComp.h"

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>



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

/*
*ブロック追加ボタンを含むウィジェット
*/

class AddButton : public QWidget
{
	Q_OBJECT
public:
	AddButton(QString text,QWidget *parent = 0);
	FEComp *Fc;
	QPushButton *PB;

signals:
	/*
	*ボタンクリック時に発行するシグナル
	*/
	void clicked(FEComp *fc);

public slots:
	/*
	*ボタンクリック時に呼び出すスロット
	*/
	void clickedSlot();

};

#endif