#ifndef EDGEAGGREGATION_H
#define EDGEAGGREGATION_H
#include "edge.h"

class GraphBody;
//! class for aggregation relation
class EdgeAggregation : public Edge
{
public:
	EdgeAggregation(GraphBody *graphWidget, INode *sourceNode, INode *destNode, const QString& name);
	virtual ~EdgeAggregation();
	virtual void adjust();
	virtual Types getType() const;
protected:
	virtual QPainterPath shape() const;
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
	QPointF sourcePoint;
	QPointF destPoint;
	QPointF middlePoint;
	qreal arrowSize;
};

#endif

