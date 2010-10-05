#ifndef NodeActivity_H
#define NodeActivity_H
#include "node.h"
//! node for activity
class NodeActivity : public Node
{
public:
	NodeActivity(GraphBody *graphWidget, INode* _parent, qint16 _id);
	virtual TopTypes getType() const;
	virtual void Show();
private:
	GraphBody *graph;
	qint16 id;
protected:
	QRectF boundingRect() const;
	QPainterPath shape() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // NodeActivity_H
