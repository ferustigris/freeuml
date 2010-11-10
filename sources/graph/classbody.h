#ifndef ClassBody_H
#define ClassBody_H

//#include <QObject>
#include <QMenu>
#include "inode.h"
#include "iedge.h"
#include "activitybody.h"

//! class for states of body
class ClassState : public State {
public:
	ClassState();
	ClassState(const int state, const QString& type);
	bool isType(const QString&type) const;
private:
	QString type;
};

//! canvas for activity diagram
class ClassBody : public ActivityBody {
	Q_OBJECT
public:
	explicit ClassBody(EnterInputs *parent);
	virtual ~ClassBody();
	virtual qint16 addTop(TopTypes type);
	virtual void ppMenu();
	virtual INodesFactory*getFactory();
protected:
	virtual bool addRelation(const qint16& index,const qint16& relationWith, const State*state);
private slots:
	virtual void on_actionAdd_agrigation_triggered();
	virtual void on_actionAdd_relation_triggered();
private:
	QMenu ppTopMenu;
};

#endif // ClassBody_H
