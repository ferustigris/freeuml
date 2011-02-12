#ifndef CollaborationBody_H
#define CollaborationBody_H

//#include <QObject>
#include <QMenu>
#include "inode.h"
#include "iedge.h"
#include "activitybody.h"

//! canvas for activity diagram
class CollaborationBody : public ActivityBody {
	Q_OBJECT
public:
	explicit CollaborationBody(EnterInputs *parent);
	virtual ~CollaborationBody();
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

#endif // CollaborationBody_H
