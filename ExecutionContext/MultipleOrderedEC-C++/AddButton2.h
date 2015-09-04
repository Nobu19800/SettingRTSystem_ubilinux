#ifndef ADDBUTTON2_H
#define ADDBUTTON2_H

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

class CompLayout;


/*
*直列ブロック追加ボタンを含むウィジェット
*/

class AddButton2 : public QWidget
{
	Q_OBJECT
public:
	AddButton2(QString text,QWidget *parent = 0);
	CompLayout *Cl;
	QPushButton *PB;

signals:
	/*
	*ボタンクリック時に発行するシグナル
	*/
	void clicked(CompLayout *cl);

public slots:
	/*
	*ボタンクリック時に呼び出すスロット
	*/
	void clickedSlot();

};

#endif