#ifndef EDITCLASS_H
#define EDITCLASS_H

#include <QWidget>
#include <QPointer>

namespace Ui {
	class EditClass;
}

class NodeClass;

class EditClass : public QWidget
{
	Q_OBJECT

	explicit EditClass(NodeClass *node, QWidget *parent = 0);
public:
	~EditClass();
	static void getClass(NodeClass *classNode);
protected:
	void changeEvent(QEvent *e);

private:
	Ui::EditClass *ui;
	NodeClass* classNode;
private slots:
	void on_delMethod_clicked();
	void on_addMethod_clicked();
	void on_delField_clicked();
	void on_addField_clicked();
	void on_Save_clicked();
	void on_Cancel_clicked();
};

#endif // EDITCLASS_H
