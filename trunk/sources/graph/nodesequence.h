#ifndef NodeSequence_H
#define NodeSequence_H
#include "node.h"
//! node for activity
class NodeSequence : public Node
{
public:
	NodeSequence(GraphBody *graphWidget, INode* _parent, qint16 _id);
	virtual TopTypes getType() const;
	virtual void Show();
	void setName(const QString&newN);
private:
	GraphBody *graph;
	qint16 id;
protected:
	QRectF boundingRect() const;
	QPainterPath shape() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // NodeSequence_H
