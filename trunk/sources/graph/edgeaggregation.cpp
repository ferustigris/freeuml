#include "edgeaggregation.h"
#include "inode.h"
#include <QPainter>
#include <math.h>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

/*!\func
 * конструктор
 * \params no
 * \return no
 */
EdgeAggregation::EdgeAggregation(GraphBody *graphWidget, INode *sourceNode, INode *destNode, const QString& name)
	: Edge(graphWidget, sourceNode, destNode, name)
{
}
/*!\func
 * деструктор
 * \params no
 * \return no
 */
EdgeAggregation::~EdgeAggregation()
{
}
/*!\func
 * calc size
 * \params no
 * \return no
 */
void EdgeAggregation::adjust()
{
	if (!sourceNode() || !destNode())
		return;
	QLineF line(mapFromItem(sourceNode(), 0, 0), mapFromItem(destNode(), 0, 0));
	qreal length = line.length();
	prepareGeometryChange();
	if (!qFuzzyCompare(length, qreal(0.0)))
	{
		QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
		sourcePoint = line.p1() + edgeOffset;
		destPoint = line.p2() - edgeOffset;
	} else {
		sourcePoint = destPoint = line.p1();
	}
}
/*!\func
 * деструктор
 * \params no
 * \return no
 */
QRectF EdgeAggregation::boundingRect() const
{
	if (!sourceNode() || !destNode())
	return QRectF();
	if(sourcePoint == destPoint)
	{
	return QRectF(destPoint.x() - 28, destPoint.y() - 28, 30, 30);
	}
	qreal penWidth = 1;
	qreal extra = (penWidth + arrowSize) / 2.0;
	return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
					  destPoint.y() - sourcePoint.y()))
	.normalized()
	.adjusted(-extra, -extra, extra, extra);
}
/*!\func
 * draw edge
 * \params no
 * \return no
 */
void EdgeAggregation::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (!sourceNode() || !destNode())return;
	QColor color (Qt::black);
	switch (getState()) {
	case OFF:
		color = Qt::gray;
		break;
	case OK:
		color = Qt::green;
		break;
	case WARNING:
	default:
		color = Qt::red;
	}

	// Draw the line itself
	if(sourceNode()->getId() == destNode()->getId())
	{
		painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		painter->drawEllipse(destPoint.x() - 28, destPoint.y() - 28, 30, 30);
		painter->setPen(Qt::black);
		painter->drawText(destPoint+QPoint(-28,-14), getData());
	}
	else
	{
		QLineF line(sourcePoint, destPoint);
		painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		painter->drawLine(line);
		// Draw the arrows if there's enough room
		double angle = ::acos(line.dx() / line.length());
		if (line.dy() >= 0)
			angle = TwoPi - angle;
		QPointF destArrowP1 = (destPoint + sourcePoint)/2 + QPointF(sin(angle - Pi / 3) * arrowSize,
							  cos(angle - Pi / 3) * arrowSize);
		QPointF destArrowP2 = (destPoint + sourcePoint)/2 + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
							  cos(angle - Pi + Pi / 3) * arrowSize);
		QPointF destArrowP3 = (destPoint + sourcePoint)/2 + QPointF(sin(angle + Pi / 2) * arrowSize,
							  cos(angle + Pi / 2) * arrowSize);
		painter->setBrush(Qt::NoBrush);
		painter->drawPolygon(QPolygonF() << destArrowP3 << destArrowP1 << destArrowP2);
		painter->setPen(Qt::black);
		painter->drawText((destPoint + sourcePoint)/2, getData());
	}
}
/*!\func
 * type of relation
 * \params no
 * \return type of edge
 */
Types EdgeAggregation::getType() const
{
	return EDGE_AGGREGATION;
}
