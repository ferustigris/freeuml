#include "edgeparams.h"
#include "ui_edgeparams.h"
#include "inode.h"
/*!\func
 * конструктор
 * \param no
 * \return no
 */
EdgeParams::EdgeParams(EdgeDirectList* e, QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::EdgeParams)
{
	edge = e;
	m_ui->setupUi(this);
	//setWindowFlags(Qt::Tool);
	m_ui->wiresList->setModel(&wireModel);
	m_ui->wiresList->setItemDelegate(&wireDelegate);
	ppmenu.addAction(m_ui->actionAdd_wire);
	ppmenu.addAction(m_ui->actionRemove_wire);
}
/*!\func
 * деструктор
 * \param no
 * \return no
 */
EdgeParams::~EdgeParams()
{
	delete m_ui;
}

void EdgeParams::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		m_ui->retranslateUi(this);
		break;
	default:
		break;
	}
}
void EdgeParams::closeEvent(QCloseEvent *e)
{
	Q_UNUSED(e);
	wireModel.removeRows(0, wireModel.rowCount(), QModelIndex());
}
/*!\func
 * отмена
 * \param no
 * \return no
 */
void EdgeParams::on_pbCancel_clicked()
{
	close();
}
/*!\func
 * сохранить
 * \param no
 * \return no
 */
void EdgeParams::on_pbOk_clicked()
{
	if(edge)
	{
		QList<Relation> list;
		QAbstractItemModel *model = m_ui->wiresList->model();
		for(int row = 0; row < model->rowCount(); row++)
		{
			QString name = model->data(model->index(row, 1), Qt::DisplayRole).toString();
			int direct = model->data(model->index(row, 0), Qt::EditRole).toInt();
			if(name.isEmpty())continue;
			list.append(Relation(direct, name));
		}
		if(list.isEmpty())
		{
			edge->Remove();
		}
		else
		{
			edge->setData(list);
		}
	}
	close();
}
/*!\func
 * показать
 * \param no
 * \return no
 */
void EdgeParams::getList(EdgeDirectList* e)
{
	static QSharedPointer<EdgeParams> window;
	if(!e)return;
	window = QSharedPointer<EdgeParams>(new EdgeParams(e, 0));
	if(window->edge)
	{
		QStringList datalist = window->edge->getData().split("\n");
		foreach(QString data, datalist)
		{
			QStringList list = data.split("|");
			if(list.count() == 2)
			{
				window->wireModel.insertRow(0);
				QModelIndex child = window->wireModel.index(0, 0);
				window->wireModel.setData(child, list[0] == "0" ? 0 : 1, Qt::EditRole);
				child = window->wireModel.index(0, 1);
				window->wireModel.setData(child, list[1], Qt::EditRole);
			}
		}
	}
	window->setWindowModality(Qt::ApplicationModal);
	window->show();
}
//! add wire
void EdgeParams::on_actionAdd_wire_triggered()
{
	static int id = 0;
	QModelIndex index = m_ui->wiresList->selectionModel()->currentIndex();
	wireModel.insertRow(index.row()+1);
	QModelIndex child = wireModel.index(index.row()+1, 0, index.parent());
	QString name("");
	name = "Wire" + QString::number(id++);
	wireModel.setData(child, QVariant(name), Qt::EditRole);
	child = wireModel.index(index.row()+1, 2, index.parent());
	wireModel.setData(child, "wire", Qt::EditRole);
}
//! del selected wire
void EdgeParams::on_actionRemove_wire_triggered()
{
		if (m_ui->wiresList->selectionModel()->selectedRows().isEmpty()) return;
		QModelIndex index = m_ui->wiresList->selectionModel()->selectedRows().first();
		if (!index.isValid())return;
		QAbstractItemModel *model = m_ui->wiresList->model();
		model->removeRows(index.row(), m_ui->wiresList->selectionModel()->selectedRows().count(), index.parent());
}
/*!\func
 * popup menu
 * \params
 * - index - model index
 * \return no
 */
void EdgeParams::on_wiresList_pressed(QModelIndex index)
{
		QCursor cursor;
		if(index.isValid()&&(qApp->mouseButtons() & Qt::RightButton))
			ppmenu.exec(cursor.pos());
}
/*!\func
 * close
 * \param no
 * \return no
 */
void EdgeParams::on_actionClose_triggered()
{
		close();
}
/*!\func
 * save all
 * \param no
 * \return no
 */
void EdgeParams::on_actionSave_triggered()
{
		on_pbOk_clicked();
}
