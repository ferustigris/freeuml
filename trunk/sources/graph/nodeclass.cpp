#include "nodeclass.h"
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
NodeClass::NodeClass(GraphBody *graphWidget, INode* _parent, qint16 _id) : Node(graphWidget, _parent, _id)
{
	graph = graphWidget;
	id = _id;
	width = 5;
	height = 15;
}
/*!\func
 * какую площадь займете?
 * \param нет
 * \return занимема€ пл-дь
 */
QRectF NodeClass::boundingRect() const
{
	return QRectF(-width/2-3, -3, width+6, height+6);
}
/*!\func
 * перерисовка
 * \param
 * - устройство отрисовки
 * - стиль
 * - при кэшировании не используетс€
 * \return нет
 */
void NodeClass::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
	if(graph->getCurIndex() == id)
	{
		painter->setPen(Qt::NoPen);
		painter->setBrush(QColor(0xd0, 0xd0, 0xd0, 100));
		painter->drawRoundedRect(-width/2-3, -3, width+6, height+6, 5, 5);
	}
	painter->setPen(Qt::black);
	painter->setBrush(Qt::yellow);
	if (option->state & QStyle::State_Sunken) {
	} else {
	}
	QPainterPath path;
	//body
	path.moveTo(0, 0);
	path.lineTo(0, 3*height/4);
	//legs
	path.lineTo(-width/2, height);
	path.moveTo(0, 3*height/4);
	path.lineTo(width/2, height);
	//hands
	path.moveTo(-width/2, height/2);
	path.lineTo(width/2, height/2);
	painter->setBrush(Qt::NoBrush);
	painter->drawPath(path);
	painter->setBrush(Qt::yellow);
	painter->drawEllipse(QPointF(0,height/4), width/2 + 1, width/2 + 1);
	if(!nodes().isEmpty())painter->drawImage(QRect(width/2-height/2, 0, height/2, height/2), QImage(":/icons/down"));
}
/*!\func
 * type of node
 * \params no
 * \return type of node
 */
TopTypes NodeClass::getType() const
{
		return TOP_AUTHOR;
}
/*!\func
 * фигура дл€ определени€ занимаемой пло-ди
 * \params нет
 * \return фигура
 */
QPainterPath NodeClass::shape() const
{
	QPainterPath path;
	qreal width = name->boundingRect().width()*1.1 + 10;
	qreal height = width/2;
	path.addRect(-width/2-3, -3, width+6, height+6);
	return path;
}
/*!\func
 * edit node
 * \params no
 * \return type of node
 */
void NodeClass::Edit()
{
}
