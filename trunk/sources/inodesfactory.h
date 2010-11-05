#ifndef INODESFACTORY_H
#define INODESFACTORY_H
#include "inode.h"
#include "iedge.h"
#include "graphbody.h"

//! abstract class for nodes factory
class INodesFactory
{
public:
	virtual INode* newNode(const TopTypes type, const qint32 id, INode *parent, const QString&name, const QString&description, const QPointF&pos) = 0;
	virtual IEdge* newEdge(const Types type, INode *source, INode *dest, const QString&data) = 0;
	virtual INode*newRoot() = 0;
};

#endif // INODESFACTORY_H
