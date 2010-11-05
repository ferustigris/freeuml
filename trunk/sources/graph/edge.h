#ifndef EDGE_H
#define EDGE_H
#include "iedge.h"

class GraphBody;

class Edge : public IEdge
{
public:

	Edge(GraphBody *graphWidget, INode *sourceNode, INode *destNode, const QString& name);
	~Edge();
	INode *sourceNode() const;
	INode *destNode() const;
	virtual void adjust();
	void show();
	void hide();
	void Remove();
	void Edit();
	void setState (const States newState);
	States getState () const;
	virtual QString getData () const;
	virtual Types getType() const;
protected:
	virtual QRectF boundingRect() const;
	QPainterPath shape() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	virtual void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event );
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
	GraphBody *graph;
	INode *source, *dest;
	QPointF sourcePoint;
	QPointF destPoint;
	qreal arrowSize;
	States state;
protected:
	QGraphicsTextItem *name;
};

#endif
