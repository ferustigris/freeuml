#ifndef GRAPHBODY_H
#define GRAPHBODY_H

#include <QtGui/QWidget>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QSettings>
#include "inode.h"
#include "iedge.h"

class NodesFactory;
class EnterInputs;

namespace Ui {
	class GraphBody;
}
enum States {
	STATE_IDLE = 0,
	STATE_ADD_RELATION,
	STATE_LEVEL_DOWN,
};
//виджет для отображения графа
class GraphBody : public QGraphicsView {
	Q_OBJECT
public:
	explicit GraphBody(EnterInputs *parent);
	virtual ~GraphBody();
	virtual qint16 addTop(TopTypes type);
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
	NodesFactory*getFactory() const;
protected:
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual bool addRelation(const qint16& index,const qint16& relationWith);
	void change(const bool ch);
protected:
	void drawBackground(QPainter *painter, const QRectF &rect);
	void wheelEvent(QWheelEvent *event);
	void scaleView(qreal scaleFactor);
	void setLevelsPath() const;
	enum ItemTypes {
		MENUITEM_DOWN = 0x01,
		MENUITEM_ADDSIMPLERELATION = 0x02,
		MENUITEM_EDIT = 0x04,
		MENUITEM_REMOVENODE = 0x08,
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
	quint8 state;
	QGraphicsLineItem* line;
	qreal factor;
	NodesFactory *nodesFactory;
protected slots:
	void on_actionRemove_state_triggered();
	void on_actionAdd_relation_triggered();
protected slots:
	virtual void on_actionLevel_down_triggered();
public slots:
	virtual void on_actionHelp_triggered();
};

#endif // GRAPHBODY_H
