#include "edgeaggregation.h"
#include "inode.h"
#include <QPainter>
#include <math.h>

/*!\func
 * constructor
 * \params no
 * \return no
 */
EdgeAggregation::EdgeAggregation(GraphBody *graphWidget, INode *sourceNode, INode *destNode, const QString& name)
	: Edge(graphWidget, sourceNode, destNode, name), arrowSize(15)
{
	if(this->sourceNode())
		this->sourceNode()->show();
	setState(OFF);
}
/*!\func
 * destructor
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
	prepareGeometryChange();
	sourcePoint = sourceNode()->pos() + QPointF(sourceNode()->boundingRect().width()/2, sourceNode()->boundingRect().height()/2);
	destPoint = destNode()->pos() + QPointF(destNode()->boundingRect().width()/2, destNode()->boundingRect().height()/2);
	middlePoint = QPointF(destPoint.x(),sourcePoint.y());
}
/*! \func
 * figure
 * \param no
 * \return no
 */
QPainterPath EdgeAggregation::shape() const
{
	QPainterPath path;
	path.moveTo(destPoint + QPointF(arrowSize,0));
	path.lineTo(middlePoint + QPointF(arrowSize,arrowSize));
	path.lineTo(sourcePoint + QPointF(0,arrowSize));
	path.lineTo(sourcePoint + QPointF(0,-arrowSize));
	path.lineTo(middlePoint + QPointF(-arrowSize,-arrowSize));
	path.lineTo(destPoint + QPointF(-arrowSize,0));
	return path;
}
/*! \func
 * rect
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
	QPointF leftTop(qMin(sourcePoint.x(), destPoint.x())-arrowSize, qMin(sourcePoint.y(), destPoint.y())-arrowSize);
	QSizeF size(abs(sourcePoint.x() - destPoint.x())+2*arrowSize, abs(sourcePoint.y() - destPoint.y())+2*arrowSize);
	return QRectF(leftTop, size);
}
/*!\func
 * draw edge
 * \params no
 * \return no
 */
void EdgeAggregation::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (!sourceNode() || !destNode())
		return;
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
	painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	float width = destNode()->boundingRect().width();
	float height = destNode()->boundingRect().height();
	QRectF rect(destNode()->pos().x() , destNode()->pos().y(), width, height);
	width = sourceNode()->boundingRect().width();
	height = sourceNode()->boundingRect().height();
	QRectF rects(sourceNode()->pos().x(), sourceNode()->pos().y(), width, height);
	painter->setBrush(color);
	QPen pen(Qt::DashLine);
	pen.setColor(color);
	painter->setPen(pen);
	painter->drawLine(destPoint, middlePoint);
	painter->drawLine(middlePoint, sourcePoint);
	pen.setStyle(Qt::SolidLine);
	painter->setPen(pen);
	if(rect.contains(middlePoint))
	{//arrow enter in node by left or right
		int sign = destPoint.x() > sourcePoint.x() ? 1 : -1;
		//QMessageBox::information(0,"","arrow enter in node by left or right");
		QPointF destArrowP1 = QPointF(middlePoint.x() - sign*rect.width()/2, middlePoint.y());
		QPointF destArrowP2 = QPointF(middlePoint.x() - sign*(rect.width()/2 + arrowSize), middlePoint.y()-arrowSize/2);
		QPointF destArrowP3 = QPointF(middlePoint.x() - sign*(rect.width()/2 + arrowSize), middlePoint.y()+arrowSize/2);
		painter->setBrush(Qt::white);
		painter->drawPolygon(QPolygonF() << destArrowP3 << destArrowP1 << destArrowP2);
	}
	else
	{//arrow enter in node by top or bottom
		int sign = destPoint.y() > sourcePoint.y() ? 1 : -1;
		//QMessageBox::information(0,"","arrow enter in node by left or right");
		QPointF destArrowP1 = QPointF(destPoint.x(), destPoint.y()-sign*rect.height()/2);
		QPointF destArrowP2 = QPointF(destPoint.x()-arrowSize/2, destPoint.y() - sign*(rect.height()/2 + arrowSize));
		QPointF destArrowP3 = QPointF(destPoint.x()+arrowSize/2, destPoint.y() - sign*(rect.height()/2 + arrowSize));
		painter->setBrush(Qt::white);
		painter->drawPolygon(QPolygonF() << destArrowP3 << destArrowP1 << destArrowP2);
	}
	if(rects.contains(middlePoint))
		name->setPos((sourcePoint + destPoint)/2);
	else
	{
		if(sourcePoint.x() < destPoint.x())
			name->setPos(sourcePoint + QPointF(sourceNode()->boundingRect().width()/2,-name->boundingRect().height()));
		else
			name->setPos(sourcePoint + QPointF(-name->boundingRect().width()-sourceNode()->boundingRect().width()/2,-name->boundingRect().height()));
	}
	//painter->drawText((destPoint + sourcePoint)/2, getData());
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
