#include "nodehost.h"
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
NodeHost::NodeHost(GraphBody *graphWidget, INode* _parent, qint16 _id) : Node(graphWidget, _parent, _id), image(":/icons/host")
{
	graph = graphWidget;
	id = _id;
	width = image.width();
	height = image.height();
}
/*!\func
 * какую площадь займете?
 * \param нет
 * \return занимема€ пл-дь
 */
QRectF NodeHost::boundingRect() const
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
void NodeHost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
	if(graph->getCurIndex() == id)
	{
		painter->setPen(Qt::NoPen);
		painter->setBrush(QColor(0xd0, 0xd0, 0xd0, 100));
		painter->drawRoundedRect(-width/2-3, -height/2-3, width+6, height+6, 5, 5);
	}
	painter->drawImage(QRect(-width/2, -height/2, width,  height), image);
	if(!nodes().isEmpty())painter->drawImage(QRect(width/2-height/2, 0, height/2, height/2), QImage(":/icons/down"));
}
/*!\func
 * type of node
 * \params no
 * \return type of node
 */
TopTypes NodeHost::getType() const
{
	return TOP_HOST;
}
/*!\func
 * фигура дл€ определени€ занимаемой пло-ди
 * \params нет
 * \return фигура
 */
QPainterPath NodeHost::shape() const
{
	QPainterPath path;
	path.addRect(-width/2-3, -height/2-3, width+6, height+6);
	return path;
}
