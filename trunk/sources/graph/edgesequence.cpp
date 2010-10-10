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
	setFlags(QGraphicsItem::ItemSendsGeometryChanges | QGraphicsItem::ItemIsMovable);
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
	sourcePoint = QPointF(sourceNode()->x(), sourceNode()->y() + (1+shift)*2*arrowSize);
	destPoint = QPointF(destNode()->x(), destNode()->y() + (1+shift)*2*arrowSize);
	rect = QRectF(0,-arrowSize,destPoint.x()-sourcePoint.x(), 2*arrowSize);
	setPos(sourcePoint);
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
	return rect;
}
 /*! \func
  * paint edge
  * \params
  * - painter - painter device
  * \return no
  */
void EdgeSequence::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->setPen(Qt::black);
	painter->drawLine(0, 0, rect.width(), 0);
	if(destPoint.x() < sourcePoint.x())
	{
		painter->drawText(rect.width(),0, name);
		painter->setPen(Qt::NoPen);
		QPointF destArrowP1 = QPointF(rect.width() + arrowSize, -arrowSize/2);
		QPointF destArrowP2 = QPointF(rect.width() + arrowSize,  arrowSize/2);
		QPointF destArrowP3 = QPointF(rect.width(),  0);
		painter->setBrush(Qt::gray);
		painter->drawPolygon(QPolygonF() << destArrowP3<< destArrowP1 << destArrowP2 << destArrowP3);
	}
	if(destPoint.x() > sourcePoint.x())
	{
		painter->drawText(0,0, name);
		painter->setPen(Qt::NoPen);
		QPointF destArrowP1 = QPointF(rect.width() - arrowSize, -arrowSize/2);
		QPointF destArrowP2 = QPointF(rect.width() - arrowSize,  arrowSize/2);
		QPointF destArrowP3 = QPointF(rect.width(),  0);
		painter->setBrush(Qt::gray);
		painter->drawPolygon(QPolygonF() << destArrowP3<< destArrowP1 << destArrowP2 << destArrowP3);
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
/*!\func
 * отпустить мышь
 * \param
 * - тип изменения
 * \return нет
 */
void EdgeSequence::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
	int newShift = (event->scenePos().y()/(2*arrowSize) - 1), max = 0;
	if(newShift < shift)newShift++;
	if(newShift < 1)newShift = 1;
	if(newShift == shift)return;
	foreach(INode*n, sourceNode()->getParent()->nodes())
	{
		foreach(IEdge*e, n->edgesIn())
		{
			EdgeSequence*edge = static_cast<EdgeSequence*>(e);
			if(edge)
			{
				if(edge->shift > max)max = edge->shift;
				if(shift < newShift)
				{
					if((edge->shift > shift)&&(edge->shift <= newShift))
						edge->shift--;
				}
				if(shift > newShift)
				{
					if((edge->shift >= newShift)&&(edge->shift < shift))
						edge->shift++;
				}
				edge->adjust();
			}
		}
	}
	if(max < newShift)
		newShift = max;
	shift = newShift;
	adjust();
}
/*!\func
 * фигура для определения занимаемой пло-ди
 * \param нет
 * \return фигура
 */
QPainterPath EdgeSequence::shape() const
{
	QPainterPath path;
	path.addRect(rect);
	return path;
}
