
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

/*
*メインウィンドウのウィジェット
*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	MainWindow(RTC::MultipleOrderedEC *ec);
   /*
   *実行順序をGUIに反映させる関数
   */
   void UpdateRTC(std::vector<Rule> &rs);
   RTC::MultipleOrderedEC *m_ec;

private slots:
	/*
	*RTCが追加、削除されたときに呼び出されるスロット
	*/
	void UpdateComp();
	/*
	*サイズを変更するときに呼び出されるスロット
	*/
	void m_resize(int w, int h);
	/*
	*ファイル保存のスロット
	*/
	bool save();
	bool saveAs();
	/*
	*ファイル読み込みスロット
	*/
	void open();
	/*
	*初期化のスロット
	*/
	void newFile();

protected:


private:
	/*
	*メニューの作成の関数
	*/
	void createMenus();
	/*
	*アクションの作成の関数
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
