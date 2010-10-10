#include "nodesequence.h"
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
NodeSequence::NodeSequence(GraphBody *graphWidget, INode* _parent, qint16 _id) : Node(graphWidget, _parent, _id)
{
	graph = graphWidget;
	id = _id;
	setFlags(QGraphicsItem::ItemIsSelectable);
}
/*!\func
 * какую площадь займете?
 * \param нет
 * \return занимемая пл-дь
 */
QRectF NodeSequence::boundingRect() const
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
 * - при кэшировании не используется
 * \return нет
 */
void NodeSequence::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
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
TopTypes NodeSequence::getType() const
{
	return TOP_SEQUENCE;
}
/*!\func
 * reimplement Show function
 * \params no
 * \return no
 */
void NodeSequence::Show()
{
	Node::Show();
	name->setPos(pos());
	name->setZValue(13);
	name->moveBy(-name->boundingRect().width()/2, -name->boundingRect().height()/2);
	name->show();
	name->hide();
}
/*!\func
 * фигура для определения занимаемой пло-ди
 * \params нет
 * \return фигура
 */
QPainterPath NodeSequence::shape() const
{
	QPainterPath path;
	qreal width = name->boundingRect().width() + 10;
	qreal height = name->boundingRect().height() + 5;
	path.addRect(-width/2-3, -height/2-3, width+6, height+6);
	return path;
}
/*!\func TShape::setName
 * установить имя
 * \param
 * - newN - новое имя
 * \return нет
 */
void NodeSequence::setName(const QString&newN) {
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	Node::setName(newN);
	qreal posx = 0;
	foreach(INode*n, getParent()->nodes())
	{
		n->setPos(posx + n->boundingRect().width()/2 , n->y());
		posx += n->boundingRect().width() + 10;
	}
}
