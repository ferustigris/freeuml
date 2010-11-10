#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include "graphbody.h"
#include "errors.h"
#include "ui_graphbody.h"
#include "mainwindow.h"
#include "node.h"
#include <math.h>
#include <QProcess>
#include <QTextStream>
#include <QTime>
#include "nodesfactory.h"


/*! \func
 *  constructor
 * \param no
 * \return no
 */
State::State()
{
	state = STATE_IDLE;
}
/*! \func
 *  constructor with argument
 * \param
 * - state - start state
 * \return no
 */
State::State(const int state)
{
	this->state = state;
}
/*! \func
 * operator =
 * \param no
 * \return no
 */
State& State::operator =(const int state)
{
	this->state = state;
}
/*! \func
 * operator equals
 * \param no
 * \return yes/no
 */
bool State::isState(const int state)const
{
	return this->state == state;
}
/*!\func TGraph::TGraph
 *  --,
 * \param
 * - parent -
 * \return
 */
GraphBody::GraphBody(EnterInputs *parent) :
	QGraphicsView(parent),
	m_ui(new Ui::GraphBody)
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	setState(new State());
	m_ui->setupUi(this);
	this->parent = parent;
	line = new QGraphicsLineItem;
	scene.setItemIndexMethod(QGraphicsScene::NoIndex);
	setScene(&scene);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(AnchorUnderMouse);
	setResizeAnchor(AnchorViewCenter);
	scaleView(1);
	//scene.setSceneRect(200*factor, 100*factor, width(), height());
	setMinimumSize(400, 400);
	currentIndex = -1;
	scene.addItem(line);
	rootNode = getFactory()->newRoot();
	node = rootNode;
	max_id = 0;
	foreach(INode* n, node->nodes())
		n->show();
	setLevelsPath();
	change(false);
}
/*!\func TGraph::TGraph
 *
 * \param
 * \return
 */
GraphBody::~GraphBody()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	delete m_ui;
}
/*!\func
 * show popup menu (virtual)
 * \param no
 * \return
 */
void GraphBody::ppMenu()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
}
/*!\func TGraph::clear
 *
 * \param no
 * \return
 */
void GraphBody::clear()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	QMapIterator<qint16, INode* > i(node->nodes());
	while(i.hasNext()) {
		i.next();
		i.value()->hide();
	}
}
/*!\func TGraph::mousePressEvent
 *
 * \param
 * - event -
 * \return
 */
void GraphBody::mousePressEvent(QMouseEvent *event) {
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(state->isState(State::STATE_ADD_RELATION))
	{
		if(node->nodes().contains(currentIndex))
		{
			qint16 index = currentIndex;
			QGraphicsView::mousePressEvent(event);
			addRelation(index, currentIndex, state.data());
		}
	}
	setState(new State());
	QGraphicsView::mousePressEvent(event);
}
/*!\func GraphBody::mouseMoveEvent
 *
 * \param
 * - event -
 * \return
 */
void GraphBody::mouseMoveEvent(QMouseEvent *event) {
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(state->isState(State::STATE_IDLE))
	{
		line->hide();
		if(parent&&(event->buttons()&Qt::LeftButton)&&(node->nodes().contains(currentIndex)))
			parent->change(true);
	}
	else if(state->isState(State::STATE_ADD_RELATION))
	{
		LOG(LOG_DEBUG, QString(__FUNCTION__)+": add relation");
		if(node->nodes().contains(currentIndex))
		{
			line->show();
			QPointF p1(mapToScene(event->pos()));
			INode*n = node->nodes()[currentIndex];
			if(!n)return;
			line->setLine(n->pos().x(), n->pos().y(), p1.x(), p1.y());
		}
	}
	QGraphicsView::mouseMoveEvent(event);
}
/*!\func
 *
 * \param
 * \return
 */
void GraphBody::on_actionAdd_relation_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	setState(new State(State::STATE_ADD_RELATION));
	line->show();
}
/*!\func
 *
 * \param
 * -
 * -
 * \return
 */
void GraphBody::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    // Fill
    return;
    QLinearGradient gradient(rect.topLeft(), rect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersect(rect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(rect);
}
/*!\func
 *
 * \param
 * -
 * \return
 */
void GraphBody::wheelEvent(QWheelEvent *event)
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(event->modifiers() & Qt::ControlModifier)
		scaleView(pow((double)2, -event->delta() / 240.0));
}
/*!\func
 *
 * \param
 * -
 * \return
 */
void GraphBody::scaleView(qreal scaleFactor)
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    factor = scaleFactor;//matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
	return;

    scale(scaleFactor, scaleFactor);
}
/*!\func
 *
 * \param
 * -
 * \return
 */
void GraphBody::setCurIndex(qint16 newInd)
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    currentIndex = newInd;
}
/*!\func
 *
 * \param
 * -
 * \return
 */
qint16 GraphBody::getCurIndex( )
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    return currentIndex;
}
/*!\func
 *
 * \param
 * \return
 */
void GraphBody::on_actionLevel_down_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(node->nodes().contains(currentIndex))
	{
		clear();
		node = node->nodes()[currentIndex];
		QMapIterator<qint16, INode* > i(node->nodes());
		while(i.hasNext()) {
			i.next();
			i.value()->show();
		}
		if(parent)
		{
			parent->setEnableUpLevel(true);
			setLevelsPath();
		}
	}
}
/*!\func
 *
 * \param
 * \return
 */
bool GraphBody::levelUp()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(!node->getParent())return false;
	clear();
	node = node->getParent();
	QMapIterator<qint16, INode* > i(node->nodes());
	while(i.hasNext()) {
		i.next();
		i.value()->show();
	}
	setLevelsPath();
	return node->getParent() != NULL;
}
/*!\func
 * reflesh scene
 * \param
 * \return
 */
void GraphBody::reflesh()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	clear();
	QMapIterator<qint16, INode* > i(node->nodes());
	while(i.hasNext())
	{
		i.next();
		i.value()->show();
	}
	setLevelsPath();
}
/*!\func
 * sety levels path in status bar
 * \param
 * \return
 */
void GraphBody::setLevelsPath() const
{
	QString path("");
	INode*n = node;
	while(n)
	{
		path = "->" + n->getName() + path;
		n = n->getParent();
	}
	if(parent)
	{
		parent->setLevelPath(path);
	}
	parent->setEnableUpLevel(node->getParent());
}
/*!\func
 *
 * \param
 * \return
 */
INode* GraphBody::getParentNode()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	while(node->getParent())
		levelUp();
	return node;
}
/*!\func
 *     \
 * \param
 * \return
 */
void GraphBody::changeEdge(IEdge* e)
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	Q_UNUSED(e);
	change(true);
}
/*!\func
 *
 * \param
 * \return
 */
void GraphBody::on_actionHelp_triggered()
{
	if(INode*n = getSelectedNode())
	{
		n->Edit();
		change(true);
	}
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
}
/*!\func
 * add item to scene
 * \param
 * \return
 */
void GraphBody::addItem(QGraphicsItem* n)
{
	scene.addItem(n);
}
/*!\func
 * remove state
 * \param no
 * \return no
 */
void GraphBody::on_actionRemove_state_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(node->nodes().contains(currentIndex))
	{
		qint32 id = currentIndex;
		currentIndex = -1;
		node->removeNode(id);
		change(true);
	}
}
/*!\func
 * return nodes factory
 * \param no
 * \return factory
 */
INodesFactory*GraphBody::getFactory()
{
	static NodesFactory nodesFactory(this);
	return &nodesFactory;
}
/*!\func
 * set max id
 * \params
 * - max - max id
 * \return no
 */
void GraphBody::setMax(const qint16 max)
{
	max_id = max;
}
/*!\func
 * set menu items
 * \params
 * - menu - menu object
 * - items - menu items
 * \return no
 */
void GraphBody::setMenuItems(QMenu&menu, const qint16 items) const
{
	if(items & MENUITEM_ADDSIMPLERELATION)
		menu.addAction(m_ui->actionAdd_relation);
	if(items & MENUITEM_DOWN)
		menu.addAction(m_ui->actionLevel_down);
	if(items & MENUITEM_EDIT)
		menu.addAction(m_ui->actionHelp);
	if(items & MENUITEM_REMOVENODE)
		menu.addAction(m_ui->actionRemove_state);
}
/*!\func
 * return current node
 * \params no
 * \return node object
 */
INode*GraphBody::getCurrentNode() const
{
	return node;
}
/*!\func
 * return current selected node
 * \params no
 * \return node object
 */
INode*GraphBody::getSelectedNode() const
{
	if(node->nodes().contains(currentIndex))
		return node->nodes()[currentIndex];
	return NULL;
}
/*!\func
 * change mainWindow
 * \params
 * - ch - flag changes
 * \return node object
 */
void GraphBody::change(const bool ch)
{
	if(parent)parent->change(ch);
}
/*!\func
 * get maximum id
 * \params no
 * \return maximum id
 */
qint16 GraphBody::getMax() const
{
	return max_id;
}
/*!\func
 * set state
 * \params no
 * \return maximum id
 */
void GraphBody::setState(State*state)
{
	this->state = QSharedPointer<State>(state);
}
