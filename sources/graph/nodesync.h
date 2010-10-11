#ifndef NodeSync_H
#define NodeSync_H
#include "nodeactivity.h"
//! node for activity
class NodeSync : public NodeActivity
{
public:
	NodeSync(GraphBody *graphWidget, INode* _parent, qint16 _id);
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

#endif // NodeSync_H
