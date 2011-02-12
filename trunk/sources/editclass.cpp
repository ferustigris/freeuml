#include "editclass.h"
#include "nodeclass.h"
#include "ui_editclass.h"

/*!\func
 * constructor
 * \params
 * - classNode - class of class
 * - parent - parent widget
 * \return no
 */
EditClass::EditClass(NodeClass *node, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::EditClass)
{
	ui->setupUi(this);
	this->classNode = node;
	if(classNode)
	{
		QStringList listName = node->getName().split("\n");
		if(!listName.isEmpty())
			ui->name->setText(listName.first());
		QStringList list = classNode->getMethods();
		foreach(QString method, list)
		{
			QListWidgetItem *item = new QListWidgetItem(QIcon(), method);
			item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			ui->methodsList->addItem(item);
		}
		list = classNode->getFields();
		foreach(QString method, list)
		{
			QListWidgetItem *item = new QListWidgetItem(QIcon(), method);
			item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			ui->fieldsList->addItem(item);
		}
		ui->desc->setText(classNode->getShortDesc());
	}
}
/*!\func
 * destructor
 * \params no
 * \return no
 */
EditClass::~EditClass()
{
	delete ui;
}
/*!\func
 * change form
 * \params
 * - e - event
 * \return no
 */
void EditClass::changeEvent(QEvent *e)
{
		QWidget::changeEvent(e);
		switch (e->type()) {
		case QEvent::LanguageChange:
			ui->retranslateUi(this);
			break;
		default:
			break;
		}
}
/*!\func
 * cancel
 * \params no
 * \return no
 */
void EditClass::on_Cancel_clicked()
{
	close();
}
/*!\func
 * save
 * \params no
 * \return no
 */
void EditClass::on_Save_clicked()
{
	if(classNode)
	{
		classNode->setName(ui->name->text());
		QStringList list;
		for(int i = 0; i < ui->methodsList->count(); i++)
			list<<ui->methodsList->item(i)->data(Qt::DisplayRole).toString();
		classNode->setMethods(list);
		list.clear();
		for(int i = 0; i < ui->fieldsList->count(); i++)
			list<<ui->fieldsList->item(i)->data(Qt::DisplayRole).toString();
		classNode->setFields(list);
		classNode->setShortDesc(ui->desc->toPlainText());
		classNode->show();
	}
	close();
}
/*!\func
 * static show edit form
 * \params
 * - classNode - class of class
 * \return no
 */
void EditClass::getClass(NodeClass *classNode)
{
	static EditClass*editClass = NULL;
	if(editClass)
	{
		delete editClass;
		editClass = NULL;
	}
	editClass = new EditClass(classNode);
	editClass->show();
}
/*!\func
 * add empty field
 * \params no
 * \return no
 */
void EditClass::on_addField_clicked()
{
	QListWidgetItem *item = new QListWidgetItem(QIcon(), "<!--empty-->");
	item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	ui->fieldsList->addItem(item);
}
/*!\func
 * del field
 * \params no
 * \return no
 */
void EditClass::on_delField_clicked()
{
	while(!ui->fieldsList->selectedItems().isEmpty())
	{
		delete ui->fieldsList->selectedItems().takeAt(0);
	}
}
/*!\func
 * add empty method
 * \params no
 * \return no
 */
void EditClass::on_addMethod_clicked()
{
	QListWidgetItem *item = new QListWidgetItem(QIcon(), "<!--empty-->");
	item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	ui->methodsList->addItem(item);
}
/*!\func
 * del method
 * \params no
 * \return no
 */
void EditClass::on_delMethod_clicked()
{
	while(!ui->methodsList->selectedItems().isEmpty())
	{
		delete ui->methodsList->selectedItems().takeAt(0);
	}
}
