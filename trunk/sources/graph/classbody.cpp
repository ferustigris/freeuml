#include "classbody.h"
#include "errors.h"
#include "mainwindow.h"
#include <QTime>
#include "nodesfactory.h"
#include <QObject>
#include <QMessageBox>
/*! \func
 *  constructor
 * \param no
 * \return no
 */
ClassState::ClassState() : State(), type("")
{
}
/*! \func
 *  constructor
 * \param
 * - state - initial state
 * \return no
 */
ClassState::ClassState(const int state, const QString &type) : State(state)
{
	this->type = type;
}
/*! \func
 *  are current type is equal type?
 * \param no
 * \return no
 */
bool ClassState::isType(const QString &type) const
{
	return this->type == type;
}
/*!\func TGraph::TGraph
 *  constructor
 * \param
 * - parent -
 * \return
 */
ClassBody::ClassBody(EnterInputs *parent) :
		ActivityBody(parent)
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	factory = 0;
}
/*!\func TGraph::TGraph
 * destructor
 * \param
 * \return
 */
ClassBody::~ClassBody()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(factory)delete factory;
}
/*!\func
 * show popup menu on node
 * \param no
 * \return
 */
void ClassBody::ppMenu()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	ppTopMenu.clear();
	ppTopMenu.addAction(QIcon(), tr("Add assotiation"), this, SLOT(on_actionAdd_relation_triggered()));
	ppTopMenu.addAction(QIcon(), tr("Add aggregation"), this, SLOT(on_actionAdd_agrigation_triggered()));
	ppTopMenu.addSeparator();
	ppTopMenu.addAction(QIcon(":/icon/cancel"), tr("Remove"), this, SLOT(on_actionRemove_state_triggered()));
	ppTopMenu.addAction(QIcon(":/icons/help"), tr("Edit"), this, SLOT(on_actionHelp_triggered()));
	ppTopMenu.addAction(QIcon(":/icon/down"), tr("On down level"), this, SLOT(on_actionLevel_down_triggered()));
	/*qint16 items = MENUITEM_ADDSIMPLERELATION | MENUITEM_REMOVENODE | MENUITEM_EDIT | MENUITEM_DOWN;
	setMenuItems(ppTopMenu, items);*/
	ppTopMenu.exec(QCursor().pos());
}
/*!\func
 * new edge
 * \params
 * - index - index source node
 * - relationWith - index destination node
 * \return
 */
bool ClassBody::addRelation(const qint16& index,const qint16& relationWith, const State*state)
{
	ClassState*st = static_cast<ClassState*>((State*)state);
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(!getCurrentNode())return false;
	if(getCurrentNode()->nodes().contains(index) &&getCurrentNode()->nodes().contains(relationWith))
	{
		INode* source = getCurrentNode()->nodes()[index];
		INode* dest = getCurrentNode()->nodes()[relationWith];
		if(dest && source && (dest != source) )
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
						if(st)
						{
							if(st->isType("SIMPLE"))
								getFactory()->newEdge(EDGE_ASSOTIATION, source, dest, "");
							else
								getFactory()->newEdge(EDGE_AGGREGATION, source, dest, "");
							change(true);
						}
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
qint16 ClassBody::addTop(TopTypes type)
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
		name = QString ("STATE_") + QString::number(id);
	}
	getFactory()->newNode(type, id, getCurrentNode(), name, tr("No tool tip now!"), QPointF(posx,posy))->show();
	change(true);
	return id;
}
/*!\func
 * return nodes factory
 * \param no
 * \return factory
 */
INodesFactory*ClassBody::getFactory()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(!factory)factory = new NodesFactory(this);
	return factory;
}
/*!\func
 * add relation state
 * \param no
 * \return factory
 */
void ClassBody::on_actionAdd_relation_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	GraphBody::on_actionAdd_relation_triggered();
	setState(new ClassState(State::STATE_ADD_RELATION, "SIMPLE"));
}
/*!\func
 * add aggregation state
 * \param no
 * \return factory
 */
void ClassBody::on_actionAdd_agrigation_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	GraphBody::on_actionAdd_relation_triggered();
	setState(new ClassState(State::STATE_ADD_RELATION, "AGGREGATION"));
}
/*! \func
 * return type of diagramm
 * \param no
 * \return type of diagramm
 */
QString ClassBody::type() const
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	return "ClassBody";
}

