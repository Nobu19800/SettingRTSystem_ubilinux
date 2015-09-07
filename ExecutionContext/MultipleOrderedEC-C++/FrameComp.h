/*!
* @file  FrameComp.h
* @brief 実行順序のブロックを表示するウィジェット
*
*/

#ifndef FRAMECOMP_H
#define FRAMECOMP_H

#define SEL 0
#define PAL 1

#include "ExComp.h"

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include <rtm/CorbaNaming.h>
#include <rtm/RTObject.h>
#include <rtm/CorbaConsumer.h>
#include <assert.h>
#include <string>
#include <vector>
//#include <QBasicTimer>

#include "SetComp.h"
#include "AddButton.h"
#include "AddButton2.h"
#include "AddButton3.h"
#include "MPComp.h"

#include "MultipleOrderedEC.h"

#include "Config.h"


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
class QTimeLine;
QT_END_NAMESPACE


class SetComp;




/**
* @class FrameComp
*@brief 実行順序のブロックを表示するウィジェット
*/
class FrameComp : public QWidget
{
	Q_OBJECT
public:
	/**
	*@brief コンストラクタ
	* @param ec 実行コンテキストオブジェクト
	* @param sc 全実行順序のブロック表示ウィジェット
	* @param parent 親ウィジェット
	*/
    	FrameComp(RTC::MultipleOrderedEC *ec, SetComp *sc, QWidget *parent = 0);
	
	/**
	*@brief 直列ブロック初期化
	* @param FC 直列ブロックウィジェット
	*/
	void AddComp(FEComp *FC);
	
	/**
	*@brief 直列ブロック追加
	* @param num 指定位置
	* @param FC 直列ブロックウィジェット
	*/
	void InsertComp(int num, FEComp *FC);
	
	/**
	*@brief サイズ変更の関数
	*/
	void UpdateSize();
	
	/**
	*@brief バイナリファイル保存の関数
	* @param ofs2 ファイルストリーム
	* @param mR 実行順序
	* @return 成功でTrue、失敗でFalse
	*/
	bool save(std::ofstream &ofs2, std::vector<main_Rule> &mR);
	
	/**
	*@brief 削除予定
	* @param Str
	* @param an
	* @param mR
	* @return
	*/
	bool open(std::vector<std::string> &Str, int &an, std::vector<main_Rule> &mR);
	
	/**
	*@brief 削除予定
	* @param ifs
	* @param mR
	* @return 成功でTrue、失敗でFalse
	*/
	bool openb(std::ifstream &ifs, std::vector<main_Rule> &mR);

	/**
	*@brief 未使用
	* @param rs
	*/
	void UpdateRTC(std::vector<Rule> &rs);
	
	/**
	*@brief 初期化
	*/
	void newFile();
	
	/**
	*@brief RTCが追加、削除されたときに実行条件に反映する関数
	* @param mR 実行順序
	*/
	void SetFrame(main_Rule &mR);
	RTC::MultipleOrderedEC *m_ec;
	Configs *cf;
	int X;
	int Y;
	std::vector<CompLayout *> Comps;
	
	/**
	*@brief RTCが追加、削除されたときにブロックに反映する関数
	* @param rtclist RTCのリスト
	* @param rtclist2 未使用
	*/
	void UpdateComp2(std::vector<std::string> rtclist, std::vector<CORBA::Object_ptr> rtclist2);
	

signals:
	
	/**
	*@brief サイズ変更時のシグナル
	*/
	void UpdateSizeSignal();

	






public slots:
   
	/**
	*@brief 直列ブロックの指定位置にブロック追加するスロット
	* @param ec 挿入箇所手前のブロックウィジェット
	* @param fc 直列ブロックウィジェット
	*/
   void AddCompSlot(ExComp *ec, FEComp *fc);
   
   /**
   *@brief 直列ブロックの先頭にブロックを追加するスロット
   * @param fc 直列ブロックウィジェット
   */
   void AddCompSlot1(FEComp *fc);
   
   /**
   *@brief 並列ブロック初期化
   * @param c 並列ブロックレイアウト
   */
   void AddCompSlot2(CompLayout *c);
   /**
   *@brief 並列ブロックの先頭に直列ブロックを追加
   * @param c 並列ブロックレイアウト
   */
   void AddCompSlot3(CompLayout *c);
   /**
   *@brief 並列ブロック追加
   */
   void AddComps2();
   
   /**
   *@brief 並列ブロックを指定位置に追加
   * @param num 指定位置
   */
   void InsertComps2(int num);
   
   /**
   *@brief 並列ブロックを先頭に追加するスロット
   */
   void AddCompsT();
   
   /**
   *@brief 並列ブロックを指定並列ブロックの後に追加するスロット
   * @param c 指定並列ブロック
   */
   void AddCompsU(CompLayout *c);
   
   /**
   *@brief 並列ブロック削除
   * @param Vl 並列ブロック追加ボタンのウィジェット
   * @param c 並列ブロック削除
   */
   void DeleteComp(QWidget *Vl, CompLayout *c);
   
   /**
   *@brief ブロックの色を変えるスロット
   * @param rs 並列ブロックのリスト
   */
   void UpdateEC(std::vector<Rule> &rs);
   
   /**
   *@brief このブロックを削除する関数
   */
   void DeleteFrame();
   

   



protected:
	
    
private:
	std::vector<FEComp *> CLS;
	QTextCodec* tc;

	QVBoxLayout *mainLayout;
	
	
	

	
	

	

	

	SetComp *Sc;

	




};


#endif
