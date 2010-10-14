#ifndef NodeClass_H
#define NodeClass_H
#include "nodeactivity.h"

//! node for activity
class NodeClass : public NodeActivity
{
public:
	NodeClass(GraphBody *graphWidget, INode* _parent, qint16 _id);
	virtual TopTypes getType() const;
	virtual void Edit();
	void setMethods(const QStringList&methods);
	void setFields(const QStringList&fields);
	QStringList getMethods()const;
	QStringList getFields()const;
	virtual void setName(const QString&);
	virtual QString getName() const;
private:
	GraphBody *graph;
	qint16 id;
	qreal width;
	qreal height;
	qreal signHeight;
	qreal signWidth;
	QStringList methods;//list of methods
	QStringList fields;//list of fields
protected:
	QRectF boundingRect() const;
	QPainterPath shape() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // NodeClass_H
