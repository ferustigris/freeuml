#include "activitybody.h"
#include "errors.h"
#include "mainwindow.h"
#include <QTime>
#include <QSignalMapper>
#include "nodesfactory.h"
#include <QObject>

/*!\func TGraph::TGraph
 *  constructor
 * \param
 * - parent -
 * \return
 */
ActivityBody::ActivityBody(EnterInputs *parent) :
	GraphBody(parent)
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
}
/*!\func TGraph::TGraph
 * destructor
 * \param
 * \return
 */
ActivityBody::~ActivityBody()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
}
/*!\func
 * show popup menu on node
 * \param no
 * \return
 */
void ActivityBody::ppMenu()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	ppTopMenu.clear();
	if(INode*n = getSelectedNode())
	{
		qint16 items = MENUITEM_ADDSIMPLERELATION | MENUITEM_REMOVENODE;
		if(n->getType() != TOP_SYNC)
		{
			items |= MENUITEM_DOWN | MENUITEM_EDIT;
		}
		setMenuItems(ppTopMenu, items);
	}
	ppTopMenu.exec(QCursor().pos());
}
/*!\func
 * new edge
 * \params
 * - index - index source node
 * - relationWith - index destination node
 * \return
 */
bool ActivityBody::addRelation(const qint16& index,const qint16& relationWith, const State*state)
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
					getFactory()->newEdge(EDGE_LINES, source, dest, "");
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
qint16 ActivityBody::addTop(TopTypes type)
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
	name = QString ("TOP_") + QString::number(id);
	getFactory()->newNode(type, id, getCurrentNode(), name, tr("No tool tip now!"), QPointF(posx,posy))->show();
	change(true);
	return id;
}
/*!\func
 * down on one level
 * \param
 * \return
 */
void ActivityBody::on_actionLevel_down_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(!getCurrentNode())return;
	if(INode*n = getSelectedNode())
	{
		if(n->getType() != TOP_SYNC)
		{
			GraphBody::on_actionLevel_down_triggered();
		}
	}
}
/*!\func
 * show ppmenu
 * \params
 * \return
 */
void ActivityBody::changeEdge(IEdge* e)
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	static QSharedPointer<QAction>actionRemove;
	static QSharedPointer<QAction>actionEdit;
	static QSharedPointer<QSignalMapper>mapperRemove;
	static QSharedPointer<QSignalMapper>mapperEdit;
	actionRemove = QSharedPointer<QAction>(new QAction(QIcon(":/icons/del"), tr("Remove edge"), this));
	actionEdit = QSharedPointer<QAction>(new QAction(QIcon(":/icons/edit"), tr("Edit edge"), this));
	mapperRemove = QSharedPointer<QSignalMapper>(new QSignalMapper);
	mapperEdit = QSharedPointer<QSignalMapper>(new QSignalMapper);
	mapperRemove->setMapping(actionRemove.data(), new Pointer(e));
	mapperEdit->setMapping(actionEdit.data(), new Pointer(e));
	connect(actionRemove.data(), SIGNAL(triggered()), mapperRemove.data(), SLOT (map()));
	connect(actionEdit.data(), SIGNAL(triggered()), mapperEdit.data(), SLOT (map()));
	connect(mapperRemove.data(), SIGNAL(mapped(QObject*)), this, SLOT(on_actionEdgeRemove_triggered(QObject*)));
	connect(mapperEdit.data(), SIGNAL(mapped(QObject*)), this, SLOT(on_actionEdgeEdit_triggered(QObject*)));
	ppTopMenu.clear();
	ppTopMenu.addAction(actionEdit.data());
	ppTopMenu.addAction(actionRemove.data());
	ppTopMenu.exec(QCursor().pos());
}
/*!\func
 * delete edge
 * \params
 * - pointer - pointer to edge
 * \return
 */
void ActivityBody::on_actionEdgeRemove_triggered(QObject*pointer)
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(Pointer *p = qobject_cast<Pointer*>(pointer))
		p->edge()->Remove();
}
/*!\func
 * edit edge
 * \params
 * - pointer - pointer to edge
 * \return
 */
void ActivityBody::on_actionEdgeEdit_triggered(QObject*pointer)
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(Pointer *p = qobject_cast<Pointer*>(pointer))
		p->edge()->Edit();
}
/*!\func
 * return nodes factory
 * \param no
 * \return factory
 */
INodesFactory*ActivityBody::getFactory()
{
	static NodesFactory nodesFactory(this);
	return &nodesFactory;
}
