#ifndef ClassBody_H
#define ClassBody_H

//#include <QObject>
#include <QMenu>
#include "inode.h"
#include "iedge.h"
#include "activitybody.h"

//! canvas for activity diagram
class ClassBody : public ActivityBody {
	Q_OBJECT
public:
	explicit ClassBody(EnterInputs *parent);
	virtual ~ClassBody();
	virtual qint16 addTop(TopTypes type);
	virtual void ppMenu();
protected:
	virtual bool addRelation(const qint16& index,const qint16& relationWith);
private slots:
	virtual void on_actionLevel_down_triggered();
private:
	QMenu ppTopMenu;
};

#endif // ClassBody_H
