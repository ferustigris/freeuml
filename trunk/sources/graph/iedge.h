#ifndef IEDGE_H
#define IEDGE_H

#include <QObject>
#include <QGraphicsItem>

class INode;
//! virtual classs for edges
class IEdge : public QGraphicsItem
{
public:
	enum States {
		OFF = 0,
		OK,
		WARNING,
		ALARM,
	};
	virtual INode *sourceNode() const = 0;
	virtual INode *destNode() const = 0;
	virtual void adjust() = 0;
	virtual void Show() = 0;
	virtual void Hide() = 0;
	virtual void Remove() = 0;
	virtual void Edit() = 0;
	virtual void setState (const States newState) = 0;
	virtual States getState () const = 0;
	virtual QString getData() const = 0;
};
#endif // IEDGE_H