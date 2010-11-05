#ifndef TopologyBody_H
#define TopologyBody_H

//#include <QObject>
#include <QMenu>
#include "inode.h"
#include "iedge.h"
#include "activitybody.h"

//! canvas for activity diagram
class TopologyBody : public ActivityBody {
	Q_OBJECT
public:
	explicit TopologyBody(EnterInputs *parent);
	virtual ~TopologyBody();
	virtual qint16 addTop(TopTypes type);
	virtual void ppMenu();
protected:
	virtual bool addRelation(const qint16& index,const qint16& relationWith, const States state);
private slots:
	virtual void on_actionLevel_down_triggered();
private:
	QMenu ppTopMenu;
};

#endif // TopologyBody_H
