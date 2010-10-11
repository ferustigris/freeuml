#ifndef INODE_H
#define INODE_H
#include <QList>
#include <edge.h>
#include <QGraphicsItem>
enum TopTypes
{
	TOP_SIMPLE = 0,
	TOP_ROOT,
	TOP_ACTIVITY,
	TOP_IF,
	TOP_SYNC,
	TOP_USECASE,
	TOP_AUTHOR,
	TOP_HOST,
	TOP_SEQUENCE,
	TOP_CLASS,
};
class INode : public QGraphicsItem
{
public:
    virtual TopTypes getType() const = 0 ;
    virtual QString getName() const = 0 ;
    virtual void setName(const QString&) = 0;
	virtual QString getHelp() const = 0;
	virtual QStringList getHelpImages() const = 0;
	virtual void setHelp(const QString&, const QStringList&) = 0;
	virtual QString getHelpFile() const = 0;
	virtual void setHelpFile(const QString&) = 0;
	virtual QString getShortDesc() const = 0;
    virtual void setShortDesc(const QString&) = 0;
    virtual qint16 getId() = 0;
    virtual INode*getParent() = 0;
    virtual QList<INode*> getNodes() const = 0;
    virtual void addNode(INode*node) = 0;
    virtual void removeNode(const qint32 id) = 0;
    virtual void addEdge(Edge *edge) = 0;
    virtual void delEdge(Edge *edge) = 0;
    virtual QList<Edge *> edgesIn() const = 0;
    virtual QList<Edge *> edgesOut() const = 0;
    virtual QMap<qint16, INode* > nodes() const = 0;
    virtual void Show() = 0;
    virtual void Hide() = 0;
    virtual void remove() = 0;
	virtual void Edit() = 0;
};

#endif // INODE_H
