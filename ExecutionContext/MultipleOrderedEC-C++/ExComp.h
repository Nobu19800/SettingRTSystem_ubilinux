/*!
* @file  ExComp.h
* @brief RTCのブロックのウィジェット
*
*/

#ifndef EXCOMP_H
#define EXCOMP_H

#include <stdio.h>


#include <iostream>

#include <rtm/CorbaNaming.h>
#include <rtm/RTObject.h>
#include <rtm/CorbaConsumer.h>
#include <assert.h>
#include <string>
#include <vector>

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include "AddButton2.h"

#include "FEComp.h"


QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
class QComboBox;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QGroupBox;
class QLabel;
QT_END_NAMESPACE


class FEComp;

class AddButton2;


/**
* @class ExComp
*@brief RTCのブロックのウィジェット
*/
class ExComp : public QWidget
{
	Q_OBJECT
public:
	/**
	*@brief コンストラクタ
	* @param parent 親ウィジェット
	*/
    	ExComp(QWidget *parent = 0);
	
	/**
	*@brief RTCが追加、削除されたときに実行条件に反映する関数
	* @param rtclist RTCのリスト
	* @param rtclist2 未使用
	*/
	void UpdateComp(std::vector<std::string> &rtclist, std::vector<CORBA::Object_ptr> &rtclist2);
	FEComp *Fc;
	QComboBox *CB;
	QWidget *subWidget;

signals:
	
	/**
	*@brief RTCを追加ボタンを押したときに呼び出すシグナル
	* @param ec RTCのブロックのウィジェット
	* @param fc 直列ブロックのウィジェット
	*/
	void AddCompSignal(ExComp *ec, FEComp *fc);


public slots:
	
	/**
	*@brief ブロック削除ボタンのスロット
	*/
	void DeleteComp();
	
	/**
	*@brief RTCを追加ボタンを押したときに呼び出されるスロット
	*/
	void AddCompSlot();


protected:
    
private:
	QPushButton *BT;
	QPushButton *DT;
	QTextCodec* tc;
	
	

	
	

	



};




/**
* @class CompLayout
*@brief 並列ブロックのレイアウト
*/
class CompLayout
{
public:
	/**
	*@brief コンストラクタ
	*/
	CompLayout();
	std::vector<QVBoxLayout *> VL;
	QHBoxLayout * subLayout;
	AddButton2 *AB;
	QVBoxLayout *mainLayout;
	QWidget *mainWidget;
	QWidget *subWidget;
	QLabel *Lb;



};


#endif
