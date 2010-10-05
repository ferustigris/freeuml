#include "nodeif.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include "errors.h"
#include "graphbody.h"


/*!\func
 * constructor
 * \params no
 * \return no
 */
NodeIf::NodeIf(GraphBody *graphWidget, INode* _parent, qint16 _id) : NodeActivity(graphWidget, _parent, _id)
{
	graph = graphWidget;
	id = _id;
}
/*!\func
 * какую площадь займете?
 * \param нет
 * \return занимема€ пл-дь
 */
QRectF NodeIf::boundingRect() const
{
	qreal width = name->boundingRect().width()*1.1 + 10;
	qreal height = width/2;
	return QRectF(-width/2-3, -height/2-3, width+6, height+6);
}
/*!\func
 * перерисовка
 * \param
 * - устройство отрисовки
 * - стиль
 * - при кэшировании не используетс€
 * \return нет
 */
void NodeIf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
	qreal width = name->boundingRect().width()*1.1 + 10;
	qreal height = width/2;
	if(graph->getCurIndex() == id)
	{
		painter->setPen(Qt::NoPen);
		painter->setBrush(QColor(0xd0, 0xd0, 0xd0, 100));
		painter->drawRoundedRect(-width/2-3, -height/2-3, width+6, height+6, 5, 5);
	}
	painter->setPen(Qt::black);
	painter->setBrush(Qt::yellow);
	if (option->state & QStyle::State_Sunken) {
	} else {
	}
	QVector<QPoint> points(5);
	points[0] = QPoint(-width/2, 0);
	points[1] = QPoint(0,-height/2);
	points[2] = QPoint(width/2,0);
	points[3] = QPoint(0,height/2);
	points[4] = QPoint(-width/2,0);
	QPolygon polygon(points);
	painter->drawPolygon(polygon);
	if(!nodes().isEmpty())painter->drawImage(QRect(width/2-height/2, 0, height/2, height/2), QImage(":/icons/down"));
	painter->drawText(-width/2,-height/2, width, height, Qt::AlignCenter, name->toPlainText());
}
/*!\func
 * type of node
 * \params no
 * \return type of node
 */
TopTypes NodeIf::getType() const
{
	return TOP_IF;
}
/*!\func
 * фигура дл€ определени€ занимаемой пло-ди
 * \params нет
 * \return фигура
 */
QPainterPath NodeIf::shape() const
{
	QPainterPath path;
	qreal width = name->boundingRect().width()*1.1 + 10;
	qreal height = width/2;
	path.addRect(-width/2-3, -height/2-3, width+6, height+6);
	return path;
}
