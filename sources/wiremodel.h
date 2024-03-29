#ifndef TINPUTMODEL_H
#define TINPUTMODEL_H

#include <QAbstractTableModel>
#include <QItemDelegate>
#include "identificatoredit.h"

class TItem {
public:
	TItem(const QString& name, const bool direct) {
		this->name = name;
		this->direct = direct;
	}
	TItem() {
		name = "";
		direct = 0;
	}
public:
	QString name;
	bool direct;
};

class TInputModel : public QAbstractTableModel
{
public:
	TInputModel();
	virtual int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
	virtual int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
	virtual QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
	bool insertRow ( int row, const QModelIndex & parent = QModelIndex() );
	virtual bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
	Qt::ItemFlags flags(const QModelIndex &index) const;
	virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
	const QList<TItem>& getList();
	bool removeRows(int position, int rows, const QModelIndex &parent);
private:
    int rows;
    int columns;
	QList<TItem> inputs;
};
class IDelegate : public QItemDelegate
{
public:
    IDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // TINPUTMODEL_H
