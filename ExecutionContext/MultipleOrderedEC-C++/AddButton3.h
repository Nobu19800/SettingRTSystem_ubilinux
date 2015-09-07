/*!
* @file  AddButton3.h
* @brief 並列ブロック削除ボタンを含むウィジェット
*
*/

#ifndef ADDBUTTON3_H
#define ADDBUTTON3_H

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


/**
* @class AddButton3
*@brief 並列ブロック削除ボタンを含むウィジェット
*/
class AddButton3 : public QWidget
{
	Q_OBJECT
public:
	/**
	*@brief コンストラクタ
	* @param text 表示テキスト
	* @param parent 親ウィジェット
	*/
	AddButton3(QString text,QWidget *parent = 0);
	QWidget *Vl;
	QPushButton *PB;
	CompLayout *c;

signals:
	
	/**
	*@brief 
	* @param Vl ウィジェット
	* @param cl 並列ブロックのレイアウト
	*/
	void clicked(QWidget *Vl, CompLayout *cl);

public slots:
	/**
	*@brief ボタンクリック時に呼び出すスロット
	*/
	void clickedSlot();

};

#endif