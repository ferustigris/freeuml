#ifndef SequenceBody_H
#define SequenceBody_H

//#include <QObject>
#include <QMenu>
#include "inode.h"
#include "iedge.h"
#include "activitybody.h"

//! canvas for activity diagram
class SequenceBody : public ActivityBody {
	Q_OBJECT
public:
	explicit SequenceBody(EnterInputs *parent);
	virtual ~SequenceBody();
	virtual qint16 addTop(TopTypes type);
	virtual void ppMenu();
	virtual INodesFactory*getFactory();
	virtual QString type() const;
protected:
	virtual bool addRelation(const qint16& index,const qint16& relationWith, const State*state);
private:
	QMenu ppTopMenu;
	INodesFactory*factory;
};

#endif // SequenceBody_H
