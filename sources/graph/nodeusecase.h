#ifndef NodeUseCase_H
#define NodeUseCase_H
#include "nodeactivity.h"
//! node for use case
class NodeUseCase : public NodeActivity
{
public:
	NodeUseCase(GraphBody *graphWidget, INode* _parent, qint16 _id);
	virtual TopTypes getType() const;
private:
	GraphBody *graph;
	qint16 id;
};

#endif // NodeUseCase_H
