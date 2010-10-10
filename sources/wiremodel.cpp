#include "wiremodel.h"
#include "QStringList"
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QApplication>
#include <errors.h>

/*!\func
 *
 * \param no
 * \return no
 */
TInputModel::TInputModel()
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    rows = 0;
	columns = 2;
}
/*!\func
 *
 * \param no
 * \return no
 */
int TInputModel::rowCount ( const QModelIndex & ) const
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    return rows;
}
/*!\func
 *
 * \param no
 * \return no
 */
int TInputModel::columnCount ( const QModelIndex &) const
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    return columns;
}
/*!\func
 *
 * \param no
 * \return no
 */
QVariant TInputModel::data ( const QModelIndex &index, int role) const
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if (!index.isValid())
		return QVariant();
	if (role != Qt::DisplayRole && role != Qt::EditRole)
		return QVariant();
	switch(index.column())
	{
	case 0:
		if(role == Qt::DisplayRole)
			return  inputs[index.row()].direct ? "+" : "-";
		else
			return  inputs[index.row()].direct;
	case 1:
		return  inputs[index.row()].name;
	}
	return inputs[index.row()].name;
}
/*!\func
 *
 * \param no
 * \return no
 */
bool TInputModel::insertRow ( int row, const QModelIndex & parent)
{
		LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
		beginInsertRows(parent,rows,rows);
		inputs.insert(row, TItem("no name",0));
		rows++;
		endInsertRows();
		return true;
}
/*!\func
 *
 * \param no
 * \return no
 */
bool TInputModel::setData ( const QModelIndex & index, const QVariant & value, int role)
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if (role != Qt::EditRole)
		return false;
	bool result = false;
	switch(index.column())
	{
	case 0:
		inputs[index.row()].direct = value.toInt();
		result = true;
		break;
	case 1:
		if(value.toString() == "")return false;
		inputs[index.row()].name = value.toString();
		result = true;
		break;
    }
    if (result)
		emit dataChanged(index, index);
    return result;
}
/*!\func
 *
 * \param no
 * \return no
 */
Qt::ItemFlags TInputModel::flags(const QModelIndex &index) const
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
     if (!index.isValid())
	 return 0;

     return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
/*!\func
 *
 * \param no
 * \return no
 */
QVariant TInputModel::headerData ( int section, Qt::Orientation orientation, int role) const
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    if (role != Qt::DisplayRole)
	 return QVariant();
    if (orientation == Qt::Vertical)
	 return QVariant();
    switch(section)
    {
	case 0:
		return qApp->translate("EnterInputs", "Direction");
	case 1:
		return qApp->translate("EnterInputs", "Name");
    }
    return QVariant();
}
/*!\func
 *
 * \param no
 * \return no
 */
const QList<TItem>& TInputModel::getList()
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    return inputs;
}
/*!\func
 *
 * \param no
 * \return no
 */
bool TInputModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    bool success = true;
    if (rows < 1)return false;
    beginRemoveRows(parent, position, position + rows - 1);
    for(int i = position; i < position + rows; i++)
		if(inputs.count() > position)
		{
			inputs.removeAt(position);
			this->rows--;
		}
    endRemoveRows();
    return success;
}

/*!\func IDelegate::IDelegate
 * конструктор
 * \param нет
 * \return нет
 */
IDelegate::IDelegate(QObject *)
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
}
/*!\func IDelegate::createEditor
 * создает редактор ячейки
 * \param нет
 * \return нет
 */
QWidget *IDelegate::createEditor(QWidget *parent,
     const QStyleOptionViewItem &/* option */,
     const QModelIndex & index) const
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	switch(index.column()) {
	case 0:
	{
			QComboBox *editor = new QComboBox(parent);
			editor->addItem("-");
			editor->addItem("+");
			return editor;
	}
	case 1:
	{
			IdentificatorEdit *editor = new IdentificatorEdit(parent);
			return editor;
	}
	}
    return 0;
}
/*!\func IDelegate::createEditor
 * установить данные в виджет
 * \param нет
 * \return нет
 */
void IDelegate::setEditorData(QWidget *editor,
				     const QModelIndex &index) const
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	switch(index.column()) {
	case 0:
	{
			LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
			int value = index.model()->data(index, Qt::EditRole).toInt();
			QComboBox *spinBox = static_cast<QComboBox*>(editor);
			spinBox->setCurrentIndex(value);
	}
	break;
	case 1:
	{
		QString value = index.model()->data(index, Qt::EditRole).toString();
		IdentificatorEdit *spinBox = static_cast<IdentificatorEdit*>(editor);
		spinBox->setText(value);
	}
	break;
	}
}
/*!\func IDelegate::setModelData
 * установить данные в модель
 * \param нет
 * \return нет
 */
void IDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
				    const QModelIndex &index) const
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	switch(index.column()) {
	case 0:
	{
		QComboBox *spinBox = static_cast<QComboBox*>(editor);
		int value = spinBox->currentIndex();
		model->setData(index, value, Qt::EditRole);
	}
	break;
	case 1:
	{
		IdentificatorEdit *spinBox = static_cast<IdentificatorEdit*>(editor);
		QString value = spinBox->text();
		model->setData(index, value, Qt::EditRole);
	}
	break;
	}
}
/*!\func IDelegate::updateEditorGeometry
 * изменить геометрию
 * \param нет
 * \return нет
 */
void IDelegate::updateEditorGeometry(QWidget *editor,
     const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	editor->setGeometry(option.rect);
}

