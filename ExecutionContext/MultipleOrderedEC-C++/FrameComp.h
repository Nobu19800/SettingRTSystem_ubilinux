
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


/*
*実行順序のブロックを表示するウィジェット
*/


class FrameComp : public QWidget
{
	Q_OBJECT
public:
	
    FrameComp(RTC::MultipleOrderedEC *ec, SetComp *sc, QWidget *parent = 0);
	/*
	*並列ブロックの初期化の関数
	*/
	void AddComp(FEComp *FC);
	/*
	*並列ブロックの追加の関数
	*/
	void InsertComp(int num, FEComp *FC);
	/*
	*サイズ変更の関数
	*/
	void UpdateSize();
	/*
	*バイナリファイル保存の関数
	*/
	bool save(std::ofstream &ofs2, std::vector<main_Rule> &mR);
	
	bool open(std::vector<std::string> &Str, int &an, std::vector<main_Rule> &mR);
	
	bool openb(std::ifstream &ifs, std::vector<main_Rule> &mR);
	void UpdateRTC(std::vector<Rule> &rs);
	/*
	*初期化の関数
	*/
	void newFile();
	/*
    *RTCが追加、削除されたときに実行条件に反映する関数
    */
	void SetFrame(main_Rule &mR);
	RTC::MultipleOrderedEC *m_ec;
	Configs *cf;
	int X;
	int Y;
	std::vector<CompLayout *> Comps;
	/*
    *RTCが追加、削除されたときにブロックに反映する関数
    */
	void UpdateComp2(std::vector<std::string> rtclist, std::vector<CORBA::Object_ptr> rtclist2);
	

signals:
	/*
	*サイズ変更時に発行するシグナル
	*/
	void UpdateSizeSignal();

	






public slots:
   /*
   *直列ブロックにブロック追加するスロット
   */
   void AddCompSlot(ExComp *ec, FEComp *fc);
   /*
   *直列ブロックを追加するスロット
   */
   void AddCompSlot1(FEComp *fc);
   /*
   *直列ブロックを追加するスロット
   */
   void AddCompSlot2(CompLayout *c);
   void AddCompSlot3(CompLayout *c);
   void AddComps2();
   /*
   *直列ブロックを指定位置に追加するスロット
   */
   void InsertComps2(int num);
   /*
   *並列ブロックを先頭に追加するスロット
   */
   void AddCompsT();
   /*
   *並列ブロックをこのウィジェットの次に追加するスロット
   */
   void AddCompsU(CompLayout *c);
   /*
   *直列ブロックを削除するスロット
   */
   void DeleteComp(QWidget *Vl, CompLayout *c);
   /*
   *ブロックの色を変えるスロット
   */
   void UpdateEC(std::vector<Rule> &rs);
   /*
   *このブロックを削除するスロット
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
