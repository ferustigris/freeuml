#include "nodesfactory.h"
#include "inode.h"
#include "iedge.h"
#include "edge.h"
#include "edgesequence.h"
#include "edgedirectlist.h"
#include "node.h"
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
 * create new use case
 * \params
 * - parent - parent of new node
 * - name - name of node
 * - desc - short description
 * - help - help for node
 * - pos - node position
 * \return pointer to new node
 */
INode* NodesFactory::newUseCase(const qint32 id, INode *parent, const QString&name, const QString&desc, const QString&help, const QPointF&pos)
{
	Node*n = new NodeUseCase(gb, parent, id);
	gb->setMax(id);
	n->setPos(pos);
	n->setToolTip(desc);
	n->setName(name);
	n->setHelpFile(help);
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
INode* NodesFactory::newActivity(const qint32 id, INode *parent, const QString&name, const QString&desc, const QString&help, const QPointF&pos)
{
	Node*n = new NodeActivity(gb, parent, id);
	gb->setMax(id);
	n->setPos(pos);
	n->setToolTip(desc);
	n->setName(name);
	n->setHelpFile(help);
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
INode* NodesFactory::newIf(const qint32 id, INode *parent, const QString&name, const QString&desc, const QString&help, const QPointF&pos)
{
	Node*n = new NodeIf(gb, parent, id);
	gb->setMax(id);
	n->setPos(pos);
	n->setToolTip(desc);
	n->setName(name);
	n->setHelpFile(help);
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
INode* NodesFactory::newAuthor(const qint32 id, INode *parent, const QString&name, const QString&desc, const QString&help, const QPointF&pos)
{
	Node*n = new NodeAuthor(gb, parent, id);
	gb->setMax(id);
	n->setPos(pos);
	n->setToolTip(desc);
	n->setName(name);
	n->setHelpFile(help);
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
INode* NodesFactory::newSimple(const qint32 id, INode *parent, const QString&name, const QString&desc, const QString&help, const QPointF&pos)
{
	Node*n = new Node(gb, parent, id);
	gb->setMax(id);
	n->setPos(pos);
	n->setToolTip(desc);
	n->setName(name);
	n->setHelpFile(help);
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
INode* NodesFactory::newSequence(const qint32 id, INode *parent, const QString&name, const QString&desc, const QString&help)
{
	NodeSequence*n = new NodeSequence(gb, parent, id);
	gb->setMax(id);
	n->setToolTip(desc);
	n->setHelpFile(help);
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
INode* NodesFactory::newHost(const qint32 id, INode *parent, const QString&name, const QString&desc, const QString&help, const QPointF&pos)
{
	Node*n = new NodeHost(gb, parent, id);
	gb->setMax(id);
	n->setPos(pos);
	n->setToolTip(desc);
	n->setName(name);
	n->setHelpFile(help);
	parent->addNode(n);
	return n;
}
