
#ifndef SETCOMP_H
#define SETCOMP_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTabWidget>

#include "ExComp.h"
#include "FrameComp.h"
#include "FEComp.h"
#include "MPComp.h"

#include "MultipleOrderedEC.h"



QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
class QTabWidget;
QT_END_NAMESPACE

class FrameComp;

/*
*全実行順序のブロック表示ウィジェット
*/

class SetComp : public QTabWidget
{
	Q_OBJECT
public:
	
    SetComp(RTC::MultipleOrderedEC *ec, QWidget *parent = 0);
	void UpdateComp();
	void UpdateRTC(std::vector<Rule> &rs);
	RTC::MultipleOrderedEC *m_ec;
	/*
	*初期化の関数
	*/
	void newFile();
	/*
	*実行順序の削除の関数
	*/
	void DeleteComp(FrameComp *fc);
	std::vector<std::string> rtclist;
	std::vector<CORBA::Object_ptr> rtclist2;
	
	
signals:
	/*
	*サイズ変更時の発行するシグナル
	*/
	void UpdateSizeSignal(int w, int h);


public slots:
	/*
	*サイズ変更時に呼ばれるスロット
	*/
	void UpdateSizeSlot();
	/*
	*ファイル読み込みスロット
	*/
	bool save(const char *Name);
	/*
	*ファイル保存のスロット
	*/
	bool open(const char *Name);
	/*
	*実行順序追加のスロット
	*/
	void CreateComp();
	/*
	*実行しているRTCのブロックの色を変えるスロット
	*/
	void UpdateEC();
	/*
	*RTCが追加、削除されたときにブロック図に反映するスロット
	*/
	void UpdateComps();
	/*
	*RTCが追加、削除されたときに実行条件に反映するスロット
	*/
	void UpdateComp2();
	
	


protected:
    
private:
	std::vector<FrameComp *> FCS;
	QTextCodec* tc;
	QTimer *time;

	

	




};


#endif
