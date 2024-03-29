#ifndef PROJECT_H
#define PROJECT_H
#include "edge.h"
#include "inode.h"
#include <QDomNode>
#include <QString>
#include <QFile>

class GraphBody;
class EnterInputs;
const QString projectMainFile("/project.xml");

//! class for projects files
class Project
{
public:
	//Project(GraphBody *activity, GraphBody *useCase, GraphBody *state, GraphBody *topology, GraphBody *colloboration, GraphBody *sequence, GraphBody *classes, const QString&_path);
    Project(EnterInputs *mw, QList<GraphBody *> &diagrams, const QString&_path);
	~Project();
	int load();
	void save();
	QString getProjectName();
	bool isTmpProject() const;
private:
	QDomDocument doc;
	QString fileName;
	QString path;
	QFile file;
	QString content, simpleContent;
	/*GraphBody *activity;
	GraphBody *useCase;
	GraphBody *state;
	GraphBody *topology;
	GraphBody *collaboration;
	GraphBody *sequence;
	GraphBody *classes;*/
	EnterInputs *mw;
    QList<GraphBody *> *diagrams;
	bool tmpProject;
	QStringList mustBeRemoved;
protected:
	void save_edge(QDomElement& parent, INode* node);
	void create_new();
	void backup();
	void save_node(QDomElement& parent, INode* node);
	int load_node(QDomNode& parent, INode* node, GraphBody*activity);
	int load_edges(QDomNode& parent, GraphBody*activity);
	int load_one_edge( QDomNode& parent, GraphBody*activity);
private:
	INode* findNode(const qint32 id, INode* parent);
};

#endif // PROJECT_H
