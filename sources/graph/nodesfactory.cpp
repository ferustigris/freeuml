#include "nodesfactory.h"
#include "inode.h"
#include "iedge.h"
#include "edge.h"
#include "edgeaggregation.h"
#include "edgeline.h"
#include "edgesequence.h"
#include "edgedirectlist.h"
#include "edgeassotiation.h"
#include "node.h"
#include "nodeclass.h"
#include "nodeif.h"
#include "nodeauthor.h"
#include "nodesync.h"
#include "rootnode.h"
#include "nodesequence.h"
#include "nodehost.h"
#include "nodeusecase.h"
#include "nodeactivity.h"

/*!\func
 * set ms for top
 * \params
 * - ms_data - data
 * \return no
 */
NodesFactory::NodesFactory(GraphBody*gb)
{
	this->gb = gb;
}
/*!\func
 * create new root node
 * \params no
 * \return pointer to new node
 */
INode* NodesFactory::newRoot()
{
	RootNode*n = new RootNode(gb);
	gb->setMax(0);
	return n;
}
/*!\func
 * create new  node
 * \params
 * - parent - parent of new node
 * - name - name of node
 * - desc - short description
 * - help - help for node
 * - pos - node position
 * \return pointer to new node
 */
INode* NodesFactory::newNode(const TopTypes type, const qint32 id, INode *parent, const QString&name, const QString&description, const QPointF&pos)
{
	INode*n = NULL;
	switch(type)
	{
	case TOP_SIMPLE:
		n = newSimple(id, parent, name, description, pos);
		break;
	case TOP_USECASE:
		n = newUseCase(id, parent, name, description, pos);
		break;
	case TOP_HOST:
		n = newHost(id, parent, name, description, pos);
		break;
	case TOP_AUTHOR:
		n = newAuthor(id, parent, name, description, pos);
		break;
	case TOP_IF:
		n = newIf(id, parent, name, description, pos);
		break;
	case TOP_SYNC:
		n = newSync(id, parent, pos);
		break;
	case TOP_SEQUENCE:
		n = newSequence(id, parent, name, description);
		break;
	case TOP_CLASS:
		n = newClass(id, parent, name, description, pos);
		break;
	case TOP_ACTIVITY:
	default:
		n = newActivity(id, parent, name, description, pos);
	}
	return n;
}
/*!\func
 * create new edge
 * \params
 * - dest - destination node
 * - source - sources node
 * - name - name of edge
 * \return pointer to new edge
 */
IEdge* NodesFactory::newEdge(const Types type, INode *source, INode *dest, const QString&name)
{
	IEdge*n = NULL;
	switch(type)
	{
	case EDGE_SEQUENCE:
		n = newEdgeSequence(source, dest, name);
		break;
	case EDGE_LIST:
		n = newEdgeList(source, dest, name);
		break;
	case EDGE_LINES:
		n = newEdgeLines(source, dest, name);
		break;
	case EDGE_AGGREGATION:
		n = newEdgeAggregation(source, dest, name);
		break;
	case EDGE_ASSOTIATION:
		n = newEdgeAssotiation(source, dest, name);
		break;
	case EDGE_SIMPLE:
		;;
	default:
		n = newEdgeSimple(source, dest, name);
	}
	return n;
}
//
/*!\func
 * create new use case
 * \params
 * - parent - parent of new node
 * - name - name of node
 * - desc - short description
 * - help - help for node
 * - pos - node position
 * \return pointer to new node
 */
INode* NodesFactory::newUseCase(const qint32 id, INode *parent, const QString&name, const QString&desc, const QPointF&pos)
{
	Node*n = new NodeUseCase(gb, parent, id);
	gb->setMax(id);
	n->setPos(pos);
	n->setToolTip(desc);
	n->setName(name);
	parent->addNode(n);
	return n;
}
/*!\func
 * create new activity
 * \params
 * - parent - parent of new node
 * - name - name of node
 * - desc - short description
 * - help - help for node
 * - pos - node position
 * \return pointer to new node
 */
INode* NodesFactory::newActivity(const qint32 id, INode *parent, const QString&name, const QString&desc, const QPointF&pos)
{
	Node*n = new NodeActivity(gb, parent, id);
	gb->setMax(id);
	n->setPos(pos);
	n->setToolTip(desc);
	n->setName(name);
	parent->addNode(n);
	return n;
}
/*!\func
 * create new activity if (romb)
 * \params
 * - parent - parent of new node
 * - name - name of node
 * - desc - short description
 * - help - help for node
 * - pos - node position
 * \return pointer to new node
 */
INode* NodesFactory::newIf(const qint32 id, INode *parent, const QString&name, const QString&desc, const QPointF&pos)
{
	Node*n = new NodeIf(gb, parent, id);
	gb->setMax(id);
	n->setPos(pos);
	n->setToolTip(desc);
	n->setName(name);
	parent->addNode(n);
	return n;
}
/*!\func
 * create new activity if (romb)
 * \params
 * - parent - parent of new node
 * - name - name of node
 * - desc - short description
 * - help - help for node
 * - pos - node position
 * \return pointer to new node
 */
INode* NodesFactory::newSync(const qint32 id, INode *parent, const QPointF&pos)
{
	Node*n = new NodeSync(gb, parent, id);
	gb->setMax(id);
	n->setPos(pos);
	//n->setToolTip(desc);
	parent->addNode(n);
	return n;
}
/*!\func
 * create new edge
 * \params
 * - dest - destination node
 * - source - sources node
 * - name - name of edge
 * \return pointer to new edge
 */
IEdge* NodesFactory::newEdgeSimple(INode *source, INode *dest, const QString&name)
{
	IEdge *e = new Edge(gb, source, dest, name);
	return e;
}
/*!\func
 * create new edge
 * \params
 * - dest - destination node
 * - source - sources node
 * - name - name of edge
 * \return pointer to new edge
 */
IEdge* NodesFactory::newEdgeLines(INode *source, INode *dest, const QString&name)
{
	IEdge *e = new EdgeLines(gb, source, dest, name);
	return e;
}
/*!\func
 * create new edge
 * \params
 * - dest - destination node
 * - source - sources node
 * - name - name of edge
 * \return pointer to new edge
 */
IEdge* NodesFactory::newEdgeAggregation(INode *source, INode *dest, const QString&name)
{
	IEdge *e = new EdgeAggregation(gb, source, dest, name);
	return e;
}
/*!\func
 * create new edge
 * \params
 * - dest - destination node
 * - source - sources node
 * - name - name of edge
 * \return pointer to new edge
 */
IEdge* NodesFactory::newEdgeAssotiation(INode *source, INode *dest, const QString&name)
{
	IEdge *e = new EdgeAssotiation(gb, source, dest, name);
	return e;
}
/*!\func
 * create new sequence edge
 * \params
 * - dest - destination node
 * - source - sources node
 * - name - name of edge
 * \return pointer to new edge
 */
IEdge* NodesFactory::newEdgeSequence(INode *source, INode *dest, const QString&name)
{
	IEdge *e = new EdgeSequence(gb, source, dest, name);
	return e;
}
/*!\func
 * create new edge with list directions
 * \params
 * - dest - destination node
 * - source - sources node
 * \return pointer to new edge
 */
IEdge* NodesFactory::newEdgeList(INode *source, INode *dest, const QString&data)
{
	IEdge *e = new EdgeDirectList(gb, source, dest, data);
	return e;
}
/*!\func
 * create new author (men)
 * \params
 * - parent - parent of new node
 * - name - name of node
 * - desc - short description
 * - help - help for node
 * - pos - node position
 * \return pointer to new node
 */
INode* NodesFactory::newAuthor(const qint32 id, INode *parent, const QString&name, const QString&desc, const QPointF&pos)
{
	Node*n = new NodeAuthor(gb, parent, id);
	gb->setMax(id);
	n->setPos(pos);
	n->setToolTip(desc);
	n->setName(name);
	parent->addNode(n);
	return n;
}
/*!\func
 * create new class
 * \params
 * - parent - parent of new node
 * - name - name of node
 * - desc - short description
 * - help - help for node
 * - pos - node position
 * \return pointer to new node
 */
INode* NodesFactory::newClass(const qint32 id, INode *parent, const QString&name, const QString&desc, const QPointF&pos)
{
	Node*n = new NodeClass(gb, parent, id);
	gb->setMax(id);
	n->setPos(pos);
	n->setToolTip(desc);
	n->setName(name);
	parent->addNode(n);
	return n;
}
/*!\func
 * create new simple node (ellipse)
 * \params
 * - parent - parent of new node
 * - name - name of node
 * - desc - short description
 * - help - help for node
 * - pos - node position
 * \return pointer to new node
 */
INode* NodesFactory::newSimple(const qint32 id, INode *parent, const QString&name, const QString&desc, const QPointF&pos)
{
	Node*n = new Node(gb, parent, id);
	gb->setMax(id);
	n->setPos(pos);
	n->setToolTip(desc);
	n->setName(name);
	parent->addNode(n);
	return n;
}
/*!\func
 * create new simple node (ellipse)
 * \params
 * - parent - parent of new node
 * - name - name of node
 * - desc - short description
 * - help - help for node
 * - pos - node position
 * \return pointer to new node
 */
INode* NodesFactory::newSequence(const qint32 id, INode *parent, const QString&name, const QString&desc)
{
	NodeSequence*n = new NodeSequence(gb, parent, id);
	gb->setMax(id);
	n->setToolTip(desc);
	parent->addNode(n);
	n->setName(name);
	return n;
}
/*!\func
 * create new node (host) to topology diagram
 * \params
 * - parent - parent of new node
 * - name - name of node
 * - desc - short description
 * - help - help for node
 * - pos - node position
 * \return pointer to new node
 */
INode* NodesFactory::newHost(const qint32 id, INode *parent, const QString&name, const QString&desc, const QPointF&pos)
{
	Node*n = new NodeHost(gb, parent, id);
	gb->setMax(id);
	n->setPos(pos);
	n->setToolTip(desc);
	n->setName(name);
	parent->addNode(n);
	return n;
}
