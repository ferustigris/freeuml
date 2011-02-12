#ifndef EdgeDirectList_H
#define EdgeDirectList_H
#include "edge.h"

class GraphBody;
//! struct of one relation
class Relation {
public:
	Relation(const bool direction, const QString&name){
		this->direction = direction;
		this->name = name;
	}
	QString name;
	bool direction;
};
//! edge with list of relation
class EdgeDirectList : public Edge
{
public:
	EdgeDirectList(GraphBody *graphWidget, INode *sourceNode, INode *destNode, const QString&data);
	virtual ~EdgeDirectList();
	void Edit();
	virtual QString getData () const;
	void setData(const QList <Relation> relations);
	virtual Types getType() const;
protected:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
	GraphBody *graph;
	QList <Relation> relations;
	/*
	QPointF sourcePoint;
	QPointF destPoint;
	qreal arrowSize;*/
};

#endif
