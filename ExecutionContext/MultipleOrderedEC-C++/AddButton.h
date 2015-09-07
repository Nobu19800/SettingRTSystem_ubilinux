/*!
* @file  AddButton.h
* @brief 直列ブロックの先頭にブロックを追加するボタン
*
*/


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


/**
* @class AddButton
*@brief 直列ブロックの先頭にブロックを追加するボタン
*/
class AddButton : public QWidget
{
	Q_OBJECT
public:
	/**
	*@brief コンストラクタ
	* @param text 表示テキスト
	* @param parent 親ウィジェット
	*/
	AddButton(QString text,QWidget *parent = 0);
	FEComp *Fc;
	QPushButton *PB;

signals:
	
	/**
	*@brief ボタンクリック時に呼び出すシグナル
	* @param fc 直列ブロックウィジェット
	*/
	void clicked(FEComp *fc);

public slots:
	/**
	*@brief ボタンクリック時に呼び出すスロット
	*/
	void clickedSlot();

};

#endif