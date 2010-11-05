#include "nodesync.h"
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
NodeSync::NodeSync(GraphBody *graphWidget, INode* _parent, qint16 _id) : NodeActivity(graphWidget, _parent, _id)
{
	graph = graphWidget;
	id = _id;
	width = 40;
	height = 5;
}
/*!\func
 * какую площадь займете?
 * \param нет
 * \return занимема€ пл-дь
 */
QRectF NodeSync::boundingRect() const
{
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
void NodeSync::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
	Q_UNUSED(option);
	if(graph->getCurIndex() == id)
	{
		painter->setPen(Qt::NoPen);
		painter->setBrush(QColor(0xd0, 0xd0, 0xd0, 100));
		painter->drawRoundedRect(-width/2-3, -height/2-3, width+6, height+6, 5, 5);
	}
	painter->setPen(Qt::black);
	painter->setBrush(Qt::black);
	painter->drawRect(-width/2, -height/2, width, height);
}
/*!\func
 * type of node
 * \params no
 * \return type of node
 */
TopTypes NodeSync::getType() const
{
	return TOP_SYNC;
}
/*!\func
 * фигура дл€ определени€ занимаемой пло-ди
 * \params нет
 * \return фигура
 */
QPainterPath NodeSync::shape() const
{
	QPainterPath path;
	path.addRect(-width/2-3, -height/2-3, width+6, height+6);
	return path;
}
/*!\func
 * edit node
 * \params no
 * \return type of node
 */
void NodeSync::Edit()
{
}
