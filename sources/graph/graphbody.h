#ifndef GRAPHBODY_H
#define GRAPHBODY_H

#include <QtGui/QWidget>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QSettings>
#include "inodesfactory.h"

class EnterInputs;

namespace Ui {
	class GraphBody;
}
//! class for states of body
class State {
public:
	enum States {
		STATE_IDLE = 0,
		STATE_ADD_RELATION,
		STATE_LEVEL_DOWN,
	};
	State();
	State(const int state);
	State& operator =(const int state);
	bool isState(int state) const;
private:
	int state;
};
//виджет для отображения графа
class GraphBody : public QGraphicsView {
	Q_OBJECT
public:
	explicit GraphBody(EnterInputs *parent);
	virtual ~GraphBody();
	virtual qint16 addTop(TopTypes type) = 0;
	virtual void ppMenu();
	virtual void changeEdge(IEdge* e);
public:
	void clear();
	void setMax(const qint16 max);
	qint16 getMax() const;
	void setCurIndex(qint16 newInd);
	qint16 getCurIndex();
	bool levelUp();
	void reflesh();
	INode* getParentNode();
	void addItem(QGraphicsItem* item);
	virtual INodesFactory*getFactory();
protected:
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual bool addRelation(const qint16& index,const qint16& relationWith, const State *state = NULL) = 0;
	void change(const bool ch);
protected:
	void drawBackground(QPainter *painter, const QRectF &rect);
	void wheelEvent(QWheelEvent *event);
	void scaleView(qreal scaleFactor);
	void setLevelsPath() const;
	void setState(State*state);
	enum ItemTypes {
#warning: pattern posetitel
		MENUITEM_DOWN = 0x01,
		MENUITEM_ADDSIMPLERELATION = 0x02,
		MENUITEM_EDIT = 0x04,
		MENUITEM_REMOVENODE = 0x08,
		MENUITEM_ADDAGGREGATION = 0x10,
	};
	void setMenuItems(QMenu&menu, const qint16 items) const;
	INode*getCurrentNode() const;
	INode*getSelectedNode() const;
private:
	EnterInputs *parent;
	Ui::GraphBody *m_ui;
	QGraphicsScene scene;
	qint16 currentIndex;
	qint16 max_id;
	INode* rootNode;
	INode* node;
	QSharedPointer<State> state;
	QGraphicsLineItem* line;
	qreal factor;
protected slots:
	void on_actionRemove_state_triggered();
	virtual void on_actionAdd_relation_triggered();
protected slots:
	virtual void on_actionLevel_down_triggered();
	virtual void on_actionHelp_triggered();
};

#endif // GRAPHBODY_H
