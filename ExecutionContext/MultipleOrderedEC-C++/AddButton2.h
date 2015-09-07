/*!
* @file  AddButton2.h
* @brief 並列ブロック追加ボタン、並列ブロックの先頭に直列ブロック追加ボタン
*
*/

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


/**
* @class AddButton2
*@brief 並列ブロック追加ボタン、並列ブロックの先頭に直列ブロック追加ボタン
*/
class AddButton2 : public QWidget
{
	Q_OBJECT
public:
	/**
	*@brief コンストラクタ
	* @param text 表示テキスト
	* @param parent 親ウィジェット
	*/
	AddButton2(QString text,QWidget *parent = 0);
	CompLayout *Cl;
	QPushButton *PB;

signals:
	
	/**
	*@brief ボタンクリック時に呼び出すシグナル
	* @param cl 並列ブロックレイアウト
	*/
	void clicked(CompLayout *cl);

public slots:
	/**
	*@brief ボタンクリック時に呼び出すスロット
	*/
	void clickedSlot();

};

#endif