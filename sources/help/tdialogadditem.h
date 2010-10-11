#ifndef TDIALOGADDITEM_H
#define TDIALOGADDITEM_H

#include <QtGui/QDialog>
#include "inode.h"
#include "textedit.h"

namespace Ui {
	class TDialogAddItem;
}

class TDialogAddItem : public QDialog {
	Q_OBJECT
	explicit TDialogAddItem(INode *mi, const QString &dbPath, QWidget *parent = 0);
public:
	virtual ~TDialogAddItem();
	static void getHelp(INode *mi);
protected:
	virtual void changeEvent(QEvent *e);
private:
	Ui::TDialogAddItem *m_ui;
	INode *n;
	QString oldName;
private slots:
	void on_leName_textChanged(QString );
	void on_pbOk_pressed();
	void on_pbCancel_pressed();
};

#endif // TDIALOGADDITEM_H
