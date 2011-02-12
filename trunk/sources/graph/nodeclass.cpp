#include "nodeclass.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include "errors.h"
#include "graphbody.h"
#include "editclass.h"


/*!\func
 * constructor
 * \params no
 * \return no
 */
NodeClass::NodeClass(GraphBody *graphWidget, INode* _parent, qint16 _id) : NodeActivity(graphWidget, _parent, _id)
{
	graph = graphWidget;
	id = _id;
	width = 40;
	signWidth = 10;
	signHeight = 20;
	height = signHeight;
}
/*!\func
 * какую площадь займете?
 * \param нет
 * \return занимемая пл-дь
 */
QRectF NodeClass::boundingRect() const
{
	return QRectF(-3, -3, width+6, height+6);
}
/*!\func
 * перерисовка
 * \param
 * - устройство отрисовки
 * - стиль
 * - при кэшировании не используется
 * \return нет
 */
void NodeClass::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
	if(graph->getCurIndex() == id)
	{
		painter->setPen(Qt::NoPen);
		painter->setBrush(QColor(0xd0, 0xd0, 0xd0, 100));
		painter->drawRoundedRect(-3, -3, width+6, height+6, 5, 5);
	}
	painter->setPen(Qt::black);
	painter->setBrush(Qt::yellow);
	if (option->state & QStyle::State_Sunken) {
	} else {
	}
	QFont font("Arial", 10, QFont::Normal);
	font.setStyleStrategy(QFont::PreferAntialias);
	painter->setFont(font);
	painter->setPen(Qt::black);
	painter->setBrush(Qt::yellow);
	painter->drawRect(0, 0, width, height);
	qreal i = signHeight;
	painter->drawLine(0, i, width, i);
	painter->drawText(10, i-4, name->toPlainText());
	foreach(QString text, fields)
	{
		i += signHeight;
		painter->drawText(10, i-4, text);
	}
	painter->drawLine(0, i, width, i);
	foreach(QString text, methods)
	{
		i += signHeight;
		painter->drawText(10, i-4, text);
	}
	if(!nodes().isEmpty())painter->drawImage(QRectF(0, 0, 20, 20), QImage(":/icons/down"));
}
/*!\func
 * type of node
 * \params no
 * \return type of node
 */
TopTypes NodeClass::getType() const
{
		return TOP_CLASS;
}
/*!\func
 * фигура для определения занимаемой пло-ди
 * \params нет
 * \return фигура
 */
QPainterPath NodeClass::shape() const
{
	QPainterPath path;
	path.addRect(-3, -3, width+6, height+6);
	return path;
}
/*!\func
 * edit node
 * \params no
 * \return type of node
 */
void NodeClass::Edit()
{
	EditClass::getClass(this);
}
/*!\func
 * set methods
 * \params
 * - methods - list of methods
 * \return no
 */
void NodeClass::setMethods(const QStringList&methods)
{
	width = 40;
	foreach(QString text, methods)
	{
		qreal newWidth = text.length()*signWidth + 20;
		if(newWidth > width)width = newWidth;
	}
	foreach(QString text, fields)
	{
		qreal newWidth = text.length()*signWidth + 20;
		if(newWidth > width)width = newWidth;
	}
	{
		qreal newWidth = name->toPlainText().length()*signWidth + 20;
		if(newWidth > width)width = newWidth;
	}
	height = (methods.count() + fields.count() + 1)*signHeight;
	this->methods = methods;
}
/*!\func
 * set fields
 * \params no
 * - fields - list of fields
 * \return type of node
 */
void NodeClass::setFields(const QStringList&fields)
{
	width = 40;
	foreach(QString text, methods)
	{
		if(text.isEmpty())continue;
		qreal newWidth = text.length()*signWidth + 20;
		if(newWidth > width)width = newWidth;
	}
	foreach(QString text, fields)
	{
		if(text.isEmpty())continue;
		qreal newWidth = text.length()*signWidth + 20;
		if(newWidth > width)width = newWidth;
	}
	{
		qreal newWidth = name->toPlainText().length()*signWidth + 20;
		if(newWidth > width)width = newWidth;
	}
	height = (methods.count() + fields.count() + 1)*signHeight;
	this->fields = fields;
}
/*!\func
 * get methods
 * \params no
 * \return list of methods
 */
QStringList NodeClass::getMethods()const
{
	return methods;
}
/*!\func
 * get fields
 * \params no
 * \return list of fields
 */
QStringList NodeClass::getFields()const
{
	return fields;
}
/*!\func
 * установить имя
 * \param
 * - newN - новое имя
 * \return нет
 */
void NodeClass::setName(const QString&data) {
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	QStringList list = data.split("#", QString::KeepEmptyParts);
	if(list.count())
	{
		if(list.count() > 2)
		{
			QString name = list[0];
			this->name->setPlainText(name);
			QStringList fields = (list[1].split("|", QString::KeepEmptyParts)).filter(".+");
			setFields(fields);
			QStringList methods = (list[2].split("|", QString::KeepEmptyParts)).filter(".+");
			setMethods(methods);
		}
		else name->setPlainText(data);
		qreal newWidth = name->toPlainText().length()*signWidth + 20;
		if(newWidth > width)width = newWidth;
	}
}
/*!\func
 * get data
 * \param no
 * \return data
 */
QString NodeClass::getName() const
{
		LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
		QString data(name->toPlainText() + "#");
		foreach(QString text, fields)
		{
			data += text + "|";
		}
		data += "#";
		foreach(QString text, methods)
		{
			data += text + "|";
		}
		return data;
}
