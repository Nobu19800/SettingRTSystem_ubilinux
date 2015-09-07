/*!
* @file  SetComp.h
* @brief 全実行順序のブロック表示ウィジェット
*
*/

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


/**
* @class SetComp
*@brief 全実行順序のブロック表示ウィジェット
*/
class SetComp : public QTabWidget
{
	Q_OBJECT
public:
	/**
	*@brief コンストラクタ
	* @param ec 実行コンテキストオブジェクト
	* @param parent 親ウィジェット
	*/
    SetComp(RTC::MultipleOrderedEC *ec, QWidget *parent = 0);
	/**
	*@brief 未使用
	*/
	void UpdateComp();
	/**
	*@brief RTCを駆動したときにブロック図に反映するスロット
	* @param rs 並列ブロックのリスト
	*/
	void UpdateRTC(std::vector<Rule> &rs);
	RTC::MultipleOrderedEC *m_ec;
	
	/**
	*@brief 初期化
	*/
	void newFile();
	
	/**
	*@brief 実行順序の削除の関数
	* @param fc 実行順序ウィジェット
	*/
	void DeleteComp(FrameComp *fc);
	std::vector<std::string> rtclist;
	std::vector<CORBA::Object_ptr> rtclist2;
	
	
signals:
	
	/**
	*@brief サイズ変更シグナル
	* @param w 幅
	* @param h 高さ
	*/
	void UpdateSizeSignal(int w, int h);


public slots:
	/**
	*@brief サイズ変更時に呼ばれるスロット
	*/
	void UpdateSizeSlot();
	
	/**
	*@brief ファイル保存スロット
	* @param Name ファイル名
	* @return 成功でTrue、失敗でFalse
	*/
	bool save(const char *Name);
	
	/**
	*@brief ファイル読み込みスロット
	* @param Name ファイル名
	* @return 成功でTrue、失敗でFalse
	*/
	bool open(const char *Name);
	
	/**
	*@brief 実行順序追加のスロット
	*/
	void CreateComp();
	
	/**
	*@brief 実行しているRTCのブロックの色を変えるスロット
	*/
	void UpdateEC();
	
	/**
	*@brief RTCが追加、削除されたときにブロック図に反映するスロット
	*/
	void UpdateComps();
	
	/**
	*@brief ブロック図に現在のRTCのリストを反映するスロット
	*/
	void UpdateComp2();
	
	


protected:
    
private:
	std::vector<FrameComp *> FCS;
	QTextCodec* tc;
	QTimer *time;

	

	




};


#endif
