#ifndef NodeAuthor_H
#define NodeAuthor_H
#include "node.h"

//! node for activity
class NodeAuthor : public Node
{
public:
	NodeAuthor(GraphBody *graphWidget, INode* _parent, qint16 _id);
	virtual TopTypes getType() const;
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

#endif // NodeAuthor_H
