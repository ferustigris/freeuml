#ifndef IEDGE_H
#define IEDGE_H

#include <QObject>
#include <QGraphicsItem>

enum Types {
	EDGE_SIMPLE = 0,
	EDGE_LIST,
	EDGE_SEQUENCE,
	EDGE_AGGREGATION,
	EDGE_LINES,
};

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
	virtual void show() = 0;
	virtual void hide() = 0;
	virtual void Remove() = 0;
	virtual void Edit() = 0;
	virtual void setState (const States newState) = 0;
	virtual States getState () const = 0;
	virtual QString getData() const = 0;
	virtual Types getType() const = 0;
};
#endif // IEDGE_H
