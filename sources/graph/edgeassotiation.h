#ifndef EdgeAssotiation_H
#define EdgeAssotiation_H
#include "edgeaggregation.h"

class GraphBody;
//! class for aggregation relation
class EdgeAssotiation : public EdgeAggregation
{
public:
	EdgeAssotiation(GraphBody *graphWidget, INode *sourceNode, INode *destNode, const QString& name);
	~EdgeAssotiation();
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

