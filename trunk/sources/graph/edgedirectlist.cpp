#include <QPainter>
#include "edgedirectlist.h"
#include "edgeparams.h"
#include <math.h>
#include <QGraphicsSceneMouseEvent>
#include "inode.h"
#include <graphbody.h>
#include <QInputDialog>
#include <QApplication>

static const double Pi = 3.14159265358979323846264338327950288419717;

/*!\func
 * constructor
 * \params no
 * \return no
 */
EdgeDirectList::EdgeDirectList(GraphBody *graphWidget, INode *sourceNode, INode *destNode, const QString&data)
	: Edge(graphWidget, sourceNode, destNode, "")
{
	QStringList listData = data.split("\n");
	foreach(QString data, listData)
	{
		QStringList list = data.split("|");
		if(list.count() == 2)
		{
			relations.append(Relation(list[0].toInt(), list[1]));
		}
	}
}
/*!\func
 * destructor
 * \params no
 * \return no
 */
EdgeDirectList::~EdgeDirectList()
{
}
/*!\func
 * draw edge on canvas
 * \params
 * - painter - device io
 * \return no
 */
void EdgeDirectList::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
	Edge::paint(painter, item, widget);
	int i = 0;
	QPointF pos((sourceNode()->pos() + destNode()->pos())/2);
	foreach(Relation item, relations)
		painter->drawText(pos.x(),pos.y() + 10*i++, QString(item.direction ? "+" : "-") + " " + item.name);
}
/*!\func
 * edit edge
 * \params no
 * \return no
 */
void EdgeDirectList::Edit()
{
	EdgeParams::getList(this);
}
/*!\func
 * return data in string
 * \params no
 * \return string of data
 */
QString EdgeDirectList::getData () const
{
	QString res("");
	foreach(Relation rel, relations)
		res += QString::number(rel.direction) + "|" + rel.name + "\n";
	return res;
}
/*!\func
 * set data
 * \params
 * - relatons - list o relations
 * \return no
 */
void EdgeDirectList::setData(const QList <Relation> relations)
{
	this->relations = relations;
}
/*!\func
 * type of relation
 * \params no
 * \return type of edge
 */
Types EdgeDirectList::getType() const
{
	return EDGE_LIST;
}
