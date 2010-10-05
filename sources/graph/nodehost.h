#ifndef NodeHost_H
#define NodeHost_H
#include "node.h"

//! node for activity
class NodeHost : public Node
{
public:
	NodeHost(GraphBody *graphWidget, INode* _parent, qint16 _id);
	virtual TopTypes getType() const;
private:
	GraphBody *graph;
	qint16 id;
	qreal width;
	qreal height;
	QImage image;
protected:
	QRectF boundingRect() const;
	QPainterPath shape() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // NodeHost_H
