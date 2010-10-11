#ifndef StateBody_H
#define StateBody_H

//#include <QObject>
#include <QMenu>
#include "inode.h"
#include "iedge.h"
#include "activitybody.h"

//! canvas for activity diagram
class StateBody : public ActivityBody {
	Q_OBJECT
public:
	explicit StateBody(EnterInputs *parent);
	virtual ~StateBody();
	virtual qint16 addTop(TopTypes type);
	virtual void ppMenu();
protected:
	virtual bool addRelation(const qint16& index,const qint16& relationWith);
private slots:
	virtual void on_actionLevel_down_triggered();
private:
	QMenu ppTopMenu;
};

#endif // StateBody_H
