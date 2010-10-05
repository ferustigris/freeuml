#ifndef NODESFACTORY_H
#define NODESFACTORY_H
#include "inode.h"
#include "iedge.h"
#include "graphbody.h"
#include <QPointF>

//! class, wich created nodes and link with graphbody
class NodesFactory
{
public:
	NodesFactory(GraphBody*gb);
	INode*newUseCase(const qint32 id, INode *parent, const QString&name, const QString&desc, const QString&help, const QPointF&pos);
	INode*newActivity(const qint32 id, INode *parent, const QString&name, const QString&desc, const QString&help, const QPointF&pos);
	INode*newIf(const qint32 id, INode *parent, const QString&name, const QString&desc, const QString&help, const QPointF&pos);
	INode*newSync(const qint32 id, INode *parent, const QPointF&pos);
	INode*newAuthor(const qint32 id, INode *parent, const QString&name, const QString&desc, const QString&help, const QPointF&pos);
	INode*newSimple(const qint32 id, INode *parent, const QString&name, const QString&desc, const QString&help, const QPointF&pos);
	INode*newHost(const qint32 id, INode *parent, const QString&name, const QString&desc, const QString&help, const QPointF&pos);
	INode*newRoot();
	//edges
	IEdge*newEdgeSimple(INode *source, INode *dest, const QString&name);
private:
	GraphBody*gb;
};

#endif // NODESFACTORY_H
