#include "sequencebody.h"
#include "errors.h"
#include "mainwindow.h"
#include <QTime>
#include "nodesfactory.h"
#include <QObject>

/*!\func TGraph::TGraph
 *  constructor
 * \param
 * - parent -
 * \return
 */
SequenceBody::SequenceBody(EnterInputs *parent) :
		ActivityBody(parent)
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
}
/*!\func TGraph::TGraph
 * destructor
 * \param
 * \return
 */
SequenceBody::~SequenceBody()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
}
/*!\func
 * show popup menu on node
 * \param no
 * \return
 */
void SequenceBody::ppMenu()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	ppTopMenu.clear();
	qint16 items = MENUITEM_ADDSIMPLERELATION | MENUITEM_REMOVENODE | MENUITEM_EDIT | MENUITEM_DOWN;
	setMenuItems(ppTopMenu, items);
	ppTopMenu.exec(QCursor().pos());
}
/*!\func
 * new edge
 * \params
 * - index - index source node
 * - relationWith - index destination node
 * \return
 */
bool SequenceBody::addRelation(const qint16& index,const qint16& relationWith, const State*state)
{
	Q_UNUSED(state);
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(!getCurrentNode())return false;
	if(getCurrentNode()->nodes().contains(index) &&getCurrentNode()->nodes().contains(relationWith))
	{
		INode* source = getCurrentNode()->nodes()[index];
		INode* dest = getCurrentNode()->nodes()[relationWith];
		if(dest && source )
			if((dest->getId() != source->getId()))
				{
					getFactory()->newEdge(EDGE_SEQUENCE, source, dest, "");
					change(true);
					return true;
				}
	}
	return false;
}
/*!\func
 * add new node
 * \params
 * - type - type of new node
 * \return no
 */
qint16 SequenceBody::addTop(TopTypes type)
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	QString name("");
	qint16 id = 1 + getMax();
	switch(type) {
	default:
		name = QString ("MODULE_") + QString::number(id);
	}
	getFactory()->newNode(TOP_SEQUENCE, id, getCurrentNode(), name, tr("No tool tip now!"), QPointF())->show();
	change(true);
	return id;
}
/*!\func
 * return nodes factory
 * \param no
 * \return factory
 */
INodesFactory*SequenceBody::getFactory()
{
	static NodesFactory nodesFactory(this);
	return &nodesFactory;
}
