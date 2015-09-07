/*!
* @file  mainwindow.h
* @brief メインウインドウ
*
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QSlider>

#include "SetComp.h"
#include "MPComp.h"
#include "MultipleOrderedEC.h"

class DiagramScene;

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
class QPushButton;
QT_END_NAMESPACE


/**
* @class MainWindow
*@brief メインウインドウ
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	/**
	*@brief コンストラクタ
	* @param ec 実行コンテキストオブジェクト
	*/
	MainWindow(RTC::MultipleOrderedEC *ec);
   
	/**
	*@brief 実行順序をGUIに反映させる関数
	* @param rs 並列ブロックのリスト
	*/
   void UpdateRTC(std::vector<Rule> &rs);
   RTC::MultipleOrderedEC *m_ec;

private slots:
	
	/**
	*@brief RTCが追加、削除されたときに呼び出されるスロット
	*/
	void UpdateComp();
	
	/**
	*@brief サイズを変更するときに呼び出されるスロット
	* @param w 幅
	* @param h 高さ
	*/
	void m_resize(int w, int h);
	/**
	*@brief ファイル保存のスロット
	* @return 成功でTrue、失敗でFalse
	*/
	bool save();
	/**
	*@brief 別のファイル保存のスロット
	* @return 成功でTrue、失敗でFalse
	*/
	bool saveAs();
	
	/**
	*@brief ファイル読み込みスロット
	*/
	void open();
	
	/**
	*@brief 初期化のスロット
	*/
	void newFile();

protected:


private:
	
	/**
	*@brief メニューの作成の関数
	*/
	void createMenus();
	
	/**
	*@brief アクションの作成の関数
	*/
	void createAction();
	SetComp *SC;
	QPushButton *UB;
	QAction *newAct;
	QAction *openAct;
	QAction *saveAct;
	QAction *saveAsAct;
	QWidget *widget;

	QMenu *fileMenu;

	QTextCodec* tc;
	



};

#endif
