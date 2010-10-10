#include <QPainter>
#include "edgesequence.h"
#include <math.h>
#include <QGraphicsSceneMouseEvent>
#include "inode.h"
#include <graphbody.h>
#include <QInputDialog>
#include <QMessageBox>
#include <QApplication>

static const double Pi = 3.14159265358979323846264338327950288419717;
/*! \func
 * constructor
 * \params
 * - graphWidget - scene
 * - sourceNode - first node
 * - destNode - second node
 * - name - name of edge
 * \return no
 */
EdgeSequence::EdgeSequence(GraphBody *graphWidget, INode *sourceNode, INode *destNode, const QString& name)
	: Edge(graphWidget, sourceNode, destNode, ""), arrowSize(10)
{
	shift = 0;
	QString str(name.section(".", -1));
	QString num(name.section(".", 0, 0));
	//QMessageBox::information(0, str, num);
	if(!num.isEmpty())
	{
		bool ok = false;
		int sh = num.toInt(&ok);
		if(ok)
		{
			shift = sh;
		}
	}
	if(!shift)
		foreach(INode*n, sourceNode->getParent()->nodes())
			shift += n->edgesIn().count();
	this->name = str;
	setFlags(flags() | QGraphicsItem::ItemSendsGeometryChanges | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsScenePositionChanges);
}
/*! \func
 * destructor
 * \params no
 * \return no
 */
EdgeSequence::~EdgeSequence()
{
}
/*! \func
 * change
 * \params no
 * \return no
 */
void EdgeSequence::adjust()
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
	sourcePoint = QPointF(sourcePoint.x(), sourcePoint.y() + (1+shift)*2*arrowSize);
	destPoint = QPointF(destPoint.x(), destPoint.y() + (1+shift)*2*arrowSize);
}
/*!\func
 * type of relation
 * \params no
 * \return type of EdgeSequence
 */
Types EdgeSequence::getType() const
{
	return EDGE_SEQUENCE;
}
/*!\func
 * type of relation
 * \params no
 * \return type of EdgeSequence
 */
 QRectF EdgeSequence::boundingRect() const
{
	if (!sourceNode() || !destNode())
		return QRectF();
	if(sourcePoint == destPoint)
	{
		return QRectF(destPoint.x() - 28, destPoint.y() - 28, 30, 30);
	}
	qreal penWidth = 1;
	qreal extra = (penWidth + arrowSize) / 2.0;
	return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(), destPoint.y() - sourcePoint.y())).normalized().adjusted(-extra, -extra, extra, extra);
}
 /*! \func
  * paint edge
  * \params
  * - painter - painter device
  * \return no
  */
void EdgeSequence::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
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
			angle = 2*Pi - angle;
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
/*! \func
 * get data
 * \params no
 * \return no
 */
QString EdgeSequence::getData () const
{
	return QString::number(shift) + "." + name;
}
/*! \func
 * edit
 * \params no
 * \return no
 */
void EdgeSequence::Edit()
{
	QString tmp = QInputDialog::getText(0, QApplication::translate("Edge", "Change edge name"), QApplication::translate("Edge", "new name:"),QLineEdit::Normal, name);
	if(!tmp.isEmpty())
		name = tmp;
}
/*! \func
 * move item handler
 * \params
 * - event - event params
 * \return no
 */
void EdgeSequence::hoverMoveEvent ( QGraphicsSceneHoverEvent * event )
{
	QMessageBox::information(0, "1", "2");
}
/*!\func
 * edge changed
 * \param
 * - тип изменения
 * - новое значение
 * \return нет
 */
QVariant EdgeSequence::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == ItemPositionChange)
	{
		// value is the new position.
		QPointF newPos = value.toPointF();
		newPos.setX(pos().x());
		//newPos.setY(((int)newPos.y())%(int)(2*arrowSize));
		//QMessageBox::information(0, ",", QString::number(newPos.y()/(2*arrowSize)));
		return newPos;
	}
	return QGraphicsItem::itemChange(change, value);
}
/*!\func
 * отпустить мышь
 * \param
 * - тип изменения
 * \return нет
 */
void EdgeSequence::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
	int newShift = event->scenePos().y()/(2*arrowSize) - 1;
	QMessageBox::information(0, ",", QString::number(newShift));
	EdgeSequence*edge1 = NULL, *edge2 = NULL;
	foreach(INode*n, sourceNode()->getParent()->nodes())
	{
		foreach(IEdge*e, n->edgesIn())
		{
			EdgeSequence*edge = static_cast<EdgeSequence*>(e);
			if(edge)
			{
				if(edge->shift == newShift)continue;
				if(edge->shift < newShift)
				{
					if(edge1)
					{
						if(edge1->pos().y() < y)
							edge1 = edge;
					}
					else edge1 = edge;
				}
				if(y > event->pos().y())
				{
					if(edge2)
					{
						if(edge2->pos().y() > y)
							edge2 = edge;
					}
					else edge2 = edge;
				}
			}
		}
	}
	if(edge1&&edge2)
	{
		QMessageBox::information(0, edge1->name, edge2->name);
	}

}
