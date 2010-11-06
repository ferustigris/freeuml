#ifndef EdgeSequence_H
#define EdgeSequence_H
#include "edge.h"

class GraphBody;

class EdgeSequence : public Edge
{
public:

	EdgeSequence(GraphBody *graphWidget, INode *sourceNode, INode *destNode, const QString& name);
	~EdgeSequence();
	virtual void adjust();
	virtual Types getType() const;
	virtual QString getData () const;
	void Edit();
protected:
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );
	QPainterPath shape() const;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
private:
	QPointF position;
	QRectF rect;
	qreal arrowSize;
	qint32 shift;
	QString name;
};

#endif
