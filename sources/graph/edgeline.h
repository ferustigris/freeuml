#ifndef EdgeLines_H
#define EdgeLines_H
#include "edge.h"

class GraphBody;
//! class for aggregation relation
class EdgeLines : public Edge
{
public:
	EdgeLines(GraphBody *graphWidget, INode *sourceNode, INode *destNode, const QString& name);
	~EdgeLines();
	virtual void adjust();
	virtual Types getType() const;
protected:
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QPainterPath shape() const;
private:
	QPointF sourcePoint;
	QPointF destPoint;
	QPointF middle;
	qreal arrowSize;
};

#endif

