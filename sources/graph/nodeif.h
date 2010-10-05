#ifndef NodeIf_H
#define NodeIf_H
#include "nodeactivity.h"
//! node for activity
class NodeIf : public NodeActivity
{
public:
	NodeIf(GraphBody *graphWidget, INode* _parent, qint16 _id);
    virtual TopTypes getType() const;
private:
    GraphBody *graph;
    qint16 id;
protected:
	QRectF boundingRect() const;
	QPainterPath shape() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // NodeIf_H
