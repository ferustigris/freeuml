#include "nodeusecase.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include "errors.h"
#include "graphbody.h"


/*!\func
 * constructor
 * \params no
 * \return no
 */
NodeUseCase::NodeUseCase(GraphBody *graphWidget, INode* _parent, qint16 _id) : NodeActivity(graphWidget, _parent, _id)
{
    graph = graphWidget;
    id = _id;
}
/*!\func
 * type of node
 * \params no
 * \return type of node
 */
TopTypes NodeUseCase::getType() const
{
	return TOP_USECASE;
}
