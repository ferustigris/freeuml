#include <QPainter>
#include "edge.h"
#include <math.h>
#include <QGraphicsSceneMouseEvent>
#include "inode.h"
#include <graphbody.h>
#include <QInputDialog>
#include <QApplication>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

Edge::Edge(GraphBody *graphWidget, INode *sourceNode, INode *destNode, const QString& name)
    : arrowSize(10)
{
    //setAcceptedMouseButtons(0)
	this->name = name;
    source = sourceNode;
    dest = destNode;
    source->addEdge(this);
    dest->addEdge(this);
    setZValue(10);
    setFlag(ItemIsSelectable);
    adjust();
    graph = graphWidget;
    state = OFF;
    graph->addItem(this);
}

Edge::~Edge()
{
}

INode *Edge::sourceNode() const
{
    return source;
}
INode *Edge::destNode() const
{
    return dest;
}
void Edge::adjust()
{
    if (!source || !dest)
	return;
    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();
    prepareGeometryChange();
    if (!qFuzzyCompare(length, qreal(0.0))) {
	QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
	sourcePoint = line.p1() + edgeOffset;
	destPoint = line.p2() - edgeOffset;
    } else {
	sourcePoint = destPoint = line.p1();
    }
}

QRectF Edge::boundingRect() const
{
    if (!source || !dest)
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

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
	return;
    QColor color (Qt::black);
    switch (state) {
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
		painter->drawText(destPoint+QPoint(-28,-14), name);
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
		painter->setBrush(color);
		painter->drawPolygon(QPolygonF() << destArrowP3 << destArrowP1 << destArrowP2);
		painter->setPen(Qt::black);
		painter->drawText((destPoint + sourcePoint)/2, name);
	}
}
void Edge::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event )
{
	Edit();
	QGraphicsItem::mouseDoubleClickEvent(event);
}
//! show on scene
void Edge::Show()
{
    adjust();
    show();
}
//! hide on scene
void Edge::Hide()
{
	hide();
}
//! remove
void Edge::Remove()
{
	hide();
	sourceNode()->delEdge(this);
	destNode()->delEdge(this);
}
//! remove
void Edge::Edit()
{
	name = QInputDialog::getText(0, QApplication::translate("Edge", "Change edge name"), QApplication::translate("Edge", "new name:"),QLineEdit::Normal, name);
}
//! state of edge
void Edge::setState (const States newState)
{
	state = newState;
	this->adjust();
}
//! get cur state
Edge::States Edge::getState () const
{
	return state;
}
QString Edge::getData () const
{
	return name;
}
/*!\func
 * подцепить мышью
 * \param
 * - event - событие
 * \return нет
 */
void Edge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if(event->buttons() & Qt::RightButton)
	{
		graph->changeEdge(this);
	} else {
		update();
	}
	QGraphicsItem::mousePressEvent(event);
}
