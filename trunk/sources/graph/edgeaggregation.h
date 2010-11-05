#ifndef EDGEAGGREGATION_H
#define EDGEAGGREGATION_H
#include "edge.h"

class GraphBody;
//! class for aggregation relation
class EdgeAggregation : public Edge
{
public:
	EdgeAggregation(GraphBody *graphWidget, INode *sourceNode, INode *destNode, const QString& name);
	~EdgeAggregation();
	virtual void adjust();
	virtual Types getType() const;
protected:
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
	QPointF sourcePoint;
	QPointF destPoint;
	qreal arrowSize;
};

#endif

