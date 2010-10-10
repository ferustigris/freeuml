#ifndef EDGEPARAMS_H
#define EDGEPARAMS_H

#include "edgedirectlist.h"
#include "wiremodel.h"
#include <QtGui/QWidget>
#include <QMenu>

namespace Ui {
	class EdgeParams;
}

class EdgeParams : public QWidget {
	Q_OBJECT
	Q_DISABLE_COPY(EdgeParams)
	explicit EdgeParams(EdgeDirectList* e, QWidget *parent = 0);
public:
	virtual ~EdgeParams();
	static void getList(EdgeDirectList* e);
protected:
	virtual void changeEvent(QEvent *e);
	virtual void closeEvent(QCloseEvent *e);
private:
	Ui::EdgeParams *m_ui;
	EdgeDirectList* edge;
	TInputModel wireModel;
	IDelegate wireDelegate;
	QMenu ppmenu;
private slots:
	void on_actionSave_triggered();
	void on_actionClose_triggered();
	void on_wiresList_pressed(QModelIndex index);
	void on_actionRemove_wire_triggered();
	void on_actionAdd_wire_triggered();
	void on_pbOk_clicked();
	void on_pbCancel_clicked();
};

#endif // EDGEPARAMS_H
