#include "nodeactivity.h"
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
NodeActivity::NodeActivity(GraphBody *graphWidget, INode* _parent, qint16 _id) : Node(graphWidget, _parent, _id)
{
	graph = graphWidget;
	id = _id;
}
/*!\func
 * какую площадь займете?
 * \param нет
 * \return занимема€ пл-дь
 */
QRectF NodeActivity::boundingRect() const
{
	qreal width = name->boundingRect().width() + 10;
	qreal height = name->boundingRect().height() + 5;
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
void NodeActivity::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
	qreal width = name->boundingRect().width() + 10;
	qreal height = name->boundingRect().height() + 5;
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
	painter->drawRoundedRect(-width/2, -height/2, width, height, 5, 5);
	if(!nodes().isEmpty())painter->drawImage(QRect(width/2-height/2, 0, height/2, height/2), QImage(":/icons/down"));
	painter->drawText(-width/2,-height/2, width, height, Qt::AlignCenter, name->toPlainText());
}
/*!\func
 * type of node
 * \params no
 * \return type of node
 */
TopTypes NodeActivity::getType() const
{
	return TOP_ACTIVITY;
}
/*!\func
 * reimplement Show function
 * \params no
 * \return no
 */
void NodeActivity::Show()
{
	Node::Show();
	name->setPos(pos());
	name->setZValue(13);
	name->moveBy(-name->boundingRect().width()/2, -name->boundingRect().height()/2);
	name->show();
	name->hide();
}
/*!\func
 * фигура дл€ определени€ занимаемой пло-ди
 * \params нет
 * \return фигура
 */
QPainterPath NodeActivity::shape() const
{
	QPainterPath path;
	qreal width = name->boundingRect().width() + 10;
	qreal height = name->boundingRect().height() + 5;
	path.addRect(-width/2-3, -height/2-3, width+6, height+6);
	return path;
}
