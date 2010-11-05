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
protected:
	virtual bool addRelation(const qint16& index,const qint16& relationWith, const States state);
private slots:
	virtual void on_actionLevel_down_triggered();
private:
	QMenu ppTopMenu;
};

#endif // SequenceBody_H
