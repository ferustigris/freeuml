#include "collaborationbody.h"
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
CollaborationBody::CollaborationBody(EnterInputs *parent) :
		ActivityBody(parent)
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
}
/*!\func TGraph::TGraph
 * destructor
 * \param
 * \return
 */
CollaborationBody::~CollaborationBody()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
}
/*!\func
 * show popup menu on node
 * \param no
 * \return
 */
void CollaborationBody::ppMenu()
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
bool CollaborationBody::addRelation(const qint16& index,const qint16& relationWith, const States state)
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
					bool present = false;
					foreach(IEdge*edge, source->edgesOut())
					{
						if(edge->destNode()->getId() == dest->getId())
						{
							present = true;
							break;
						}
					}
					foreach(IEdge*edge, source->edgesIn())
					{
						if(edge->sourceNode()->getId() == dest->getId())
						{
							present = true;
							break;
						}
					}
					if(!present)
					{
						getFactory()->newEdgeLines(source, dest, "");
						change(true);
						return true;
					}
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
qint16 CollaborationBody::addTop(TopTypes type)
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	QString name("");
	qint16 id = 1 + getMax();
	quint32 rand1 = QTime::currentTime().msec();
	quint32 rand2 = rand1*rand1%1000;
	qreal w = - mapToScene(x(), y()).x() + mapToScene(width(), y()).x();
	qreal h = - mapToScene(x(), y()).y() + mapToScene(x(), height()).y();
	qreal posx = mapToScene(x(), y()).x() + w/1000*rand1;
	qreal posy = mapToScene(x(), y()).y() + h/1000*rand2;
	switch(type) {
	default:
		name = QString ("COMPONENT_") + QString::number(id);
		getFactory()->newActivity(id, getCurrentNode(), name, tr("No tool tip now!"), "", QPointF(posx,posy))->show();
	}
	change(true);
	return id;
}
/*!\func
 * down on one level
 * \param
 * \return
 */
void CollaborationBody::on_actionLevel_down_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	GraphBody::on_actionLevel_down_triggered();
}
