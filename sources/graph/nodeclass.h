#ifndef NodeClass_H
#define NodeClass_H
#include "node.h"

//! node for activity
class NodeClass : public Node
{
public:
	NodeClass(GraphBody *graphWidget, INode* _parent, qint16 _id);
	virtual TopTypes getType() const;
	virtual void Edit();
private:
	GraphBody *graph;
	qint16 id;
	qreal width;
	qreal height;
protected:
	QRectF boundingRect() const;
	QPainterPath shape() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // NodeClass_H
