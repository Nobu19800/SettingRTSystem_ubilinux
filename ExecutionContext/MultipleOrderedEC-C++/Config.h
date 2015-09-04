
#ifndef CONFIG_H
#define CONFIG_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include <rtm/CorbaNaming.h>
#include <rtm/RTObject.h>
#include <rtm/CorbaConsumer.h>
#include <assert.h>
#include <string>
#include <vector>




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
class QLabel;
class QRadioButton;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
QT_END_NAMESPACE



/*
*実行条件の初期化の関数
*/
void CrearLayout(QLayout *lt);

/*
*実行条件のウィジェットに表示するRTCのクラス
*/

class CompList
{
public:
	CompList(){};
	QLabel *name;
	std::string Name;
	QRadioButton *c_none;
	QRadioButton *c_created;
	QRadioButton *c_inactive;
	QRadioButton *c_active;
	QRadioButton *c_error;
	QHBoxLayout *Lo;
	QWidget *Lw;
};

/*
*実行条件のウィジェット
*/


class Configs : public QWidget
{
	Q_OBJECT
public:
	
    Configs(QWidget *parent = 0);
	/*
	*RTCが追加されたときに反映する関数
	*/
	void addComp(std::string name);
	/*
	*初期化の関数
	*/
	void resetComp();
	std::vector<CompList *> Cl;
	

signals:

public slots:

protected:
	
    
private:
	QTextCodec* tc;
	QHBoxLayout *Dl;
	QVBoxLayout *Nlist;
	QVBoxLayout *CRlist;
	QLabel *componentName;
	QLabel *noneName;
	QLabel *createdName;
	QLabel *inactiveName;
	QLabel *activeName; 
	QLabel *errorName;


	

};


#endif
