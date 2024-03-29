#ifndef NODESFACTORY_H
#define NODESFACTORY_H
#include "inode.h"
#include "iedge.h"
#include "graphbody.h"
#include "inodesfactory.h"
#include <QPointF>

//! class, wich created nodes and link with graphbody
class NodesFactory : public INodesFactory
{
public:
	NodesFactory(GraphBody*gb);
	virtual INode* newNode(const TopTypes type, const qint32 id, INode *parent, const QString&name, const QString&description, const QPointF&pos);
	virtual IEdge* newEdge(const Types type, INode *source, INode *dest, const QString&data);
	INode*newRoot();
private:
	INode*newUseCase(const qint32 id, INode *parent, const QString&name, const QString&desc, const QPointF&pos);
	INode*newActivity(const qint32 id, INode *parent, const QString&name, const QString&desc, const QPointF&pos);
	INode*newIf(const qint32 id, INode *parent, const QString&name, const QString&desc, const QPointF&pos);
	INode*newSync(const qint32 id, INode *parent, const QPointF&pos);
	INode*newAuthor(const qint32 id, INode *parent, const QString&name, const QString&desc, const QPointF&pos);
	INode*newClass(const qint32 id, INode *parent, const QString&name, const QString&desc, const QPointF&pos);
	INode*newSequence(const qint32 id, INode *parent, const QString&name, const QString&desc);
	INode*newSimple(const qint32 id, INode *parent, const QString&name, const QString&desc, const QPointF&pos);
	INode*newHost(const qint32 id, INode *parent, const QString&name, const QString&desc, const QPointF&pos);
	//edges
	IEdge*newEdgeSimple(INode *source, INode *dest, const QString&name);
	IEdge*newEdgeLines(INode *source, INode *dest, const QString&name);
	IEdge*newEdgeAggregation(INode *source, INode *dest, const QString&name);
	IEdge*newEdgeAssotiation(INode *source, INode *dest, const QString&name);
	IEdge*newEdgeSequence(INode *source, INode *dest, const QString&name);
	IEdge*newEdgeList(INode *source, INode *dest, const QString&data);
private:
	GraphBody*gb;
};

#endif // NODESFACTORY_H
