#ifndef UseCaseBody_H
#define UseCaseBody_H

//#include <QObject>
#include <QMenu>
#include "inode.h"
#include "iedge.h"
#include "activitybody.h"

//! canvas for activity diagram
class UseCaseBody : public ActivityBody {
	Q_OBJECT
public:
	explicit UseCaseBody(EnterInputs *parent);
	virtual ~UseCaseBody();
	virtual qint16 addTop(TopTypes type);
	virtual void ppMenu();
	virtual INodesFactory*getFactory();
protected:
	virtual bool addRelation(const qint16& index,const qint16& relationWith, const States state);
private slots:
	virtual void on_actionLevel_down_triggered();
private:
	QMenu ppTopMenu;
};

#endif // UseCaseBody_H
