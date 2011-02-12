#ifndef ACTIVITYBODY_H
#define ACTIVITYBODY_H

//#include <QObject>
#include <QMenu>
#include "inode.h"
#include "iedge.h"
#include "graphbody.h"
#include "mainwindow.h"

//! class pointer for edge operations
class Pointer : public QObject {
    Q_OBJECT
public:
	Pointer (IEdge*e) : QObject(0) {this->e = e;}
	IEdge* edge() const {return this->e;}
private:
	IEdge*e;
};

//! canvas for activity diagram
class ActivityBody : public GraphBody {
	Q_OBJECT
public:
	explicit ActivityBody(EnterInputs *parent);
	virtual ~ActivityBody();
	virtual qint16 addTop(TopTypes type);
	virtual void ppMenu();
	virtual void changeEdge(IEdge* e);
	virtual INodesFactory*getFactory();
	virtual QString type() const;
protected:
	virtual bool addRelation(const qint16& index,const qint16& relationWith, const State*state);
private slots:
	virtual void on_actionLevel_down_triggered();
	virtual void on_actionEdgeRemove_triggered(QObject*pointer);
	virtual void on_actionEdgeEdit_triggered(QObject*pointer);
private:
	QMenu ppTopMenu;
	INodesFactory*factory;
};

#endif // ActivityBody_H
