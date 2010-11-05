#include "edgeline.h"
#include "inode.h"
#include <QPainter>
#include <math.h>
#include <QMessageBox>
static const double Pi = 3.14159265358979323846264338327950288419717;

/*!\func
 * конструктор
 * \params no
 * \return no
 */
EdgeLines::EdgeLines(GraphBody *graphWidget, INode *sourceNode, INode *destNode, const QString& name)
	: Edge(graphWidget, sourceNode, destNode, name)
{
	arrowSize = 10;
}
/*!\func
 * деструктор
 * \params no
 * \return no
 */
EdgeLines::~EdgeLines()
{
}
/*!\func
 * calc size
 * \params no
 * \return no
 */
void EdgeLines::adjust()
{
	if (!sourceNode() || !destNode())
		return;
	prepareGeometryChange();
	sourcePoint = sourceNode()->pos();//line.p1() + edgeOffset;
	destPoint = destNode()->pos();//line.p2() - edgeOffset;
	middle = QPointF(destPoint.x(), sourcePoint.y());
}
/*!\func
 * деструктор
 * \params no
 * \return no
 */
QRectF EdgeLines::boundingRect() const
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
 * figure of edge
 * \param нет
 * \return figure
 */
QPainterPath EdgeLines::shape() const
{
	QPainterPath path;
	path.moveTo(destPoint + QPointF(arrowSize,0));
	path.lineTo(middle + QPointF(arrowSize,arrowSize));
	path.lineTo(sourcePoint + QPointF(0,arrowSize));
	path.lineTo(sourcePoint + QPointF(0,-arrowSize));
	path.lineTo(middle + QPointF(-arrowSize,-arrowSize));
	path.lineTo(destPoint + QPointF(-arrowSize,0));
	return path;
}
/*!\func
 * draw edge
 * \params no
 * \return no
 */
void EdgeLines::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
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
		//painter->drawText(destPoint+QPoint(-28,-14), getData());
	}
	else
	{
		painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		float width = destNode()->boundingRect().width();
		float height = destNode()->boundingRect().height();
		QRectF rect(destNode()->pos().x() - width/2, destNode()->pos().y() - height/2, width, height);
		width = sourceNode()->boundingRect().width();
		height = sourceNode()->boundingRect().height();
		QRectF rects(sourceNode()->pos().x() - width/2, sourceNode()->pos().y() - height/2, width, height);
		painter->setBrush(color);
		if(rect.contains(middle))
		{//arrow enter in node by left or right
			int sign = destPoint.x() > sourcePoint.x() ? 1 : -1;
			//QMessageBox::information(0,"","arrow enter in node by left or right");
			QPointF destArrowP1 = QPointF(middle.x() - sign*rect.width()/2, middle.y());
			QPointF destArrowP2 = QPointF(middle.x() - sign*(rect.width()/2 + arrowSize), middle.y()-arrowSize/2);
			QPointF destArrowP3 = QPointF(middle.x() - sign*(rect.width()/2 + arrowSize), middle.y()+arrowSize/2);
			painter->drawPolygon(QPolygonF() << destArrowP3 << destArrowP1 << destArrowP2);
		}
		else
		{//arrow enter in node by top or bottom
			int sign = destPoint.y() > sourcePoint.y() ? 1 : -1;
			//QMessageBox::information(0,"","arrow enter in node by left or right");
			QPointF destArrowP1 = QPointF(middle.x(), destPoint.y()-sign*rect.height()/2);
			QPointF destArrowP2 = QPointF(middle.x()-arrowSize/2, destPoint.y() - sign*(rect.height()/2 + arrowSize));
			QPointF destArrowP3 = QPointF(middle.x()+arrowSize/2, destPoint.y() - sign*(rect.height()/2 + arrowSize));
			painter->drawPolygon(QPolygonF() << destArrowP3 << destArrowP1 << destArrowP2);
		}
		if(rects.contains(middle))
			name->setPos((sourcePoint + destPoint)/2);
		else
		{
			if(sourcePoint.x() < destPoint.x())
				name->setPos(sourcePoint + QPointF(sourceNode()->boundingRect().width()/2,-name->boundingRect().height()));
			else
				name->setPos(sourcePoint + QPointF(-name->boundingRect().width()-sourceNode()->boundingRect().width()/2,-name->boundingRect().height()));
		}
		//painter->drawText((destPoint + sourcePoint)/2, getData());
		painter->drawLine(destPoint, middle);
		painter->drawLine(middle, sourcePoint);


	}
}
/*!\func
 * type of relation
 * \params no
 * \return type of edge
 */
Types EdgeLines::getType() const
{
	return EDGE_LINES;
}
