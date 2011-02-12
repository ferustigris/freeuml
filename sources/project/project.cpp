#include "project.h"
#include <QTextStream>
#include <QApplication>
#include <QDir>
#include <QTime>
#include <QMessageBox>
#include <QFileDialog>
#include "graphbody.h"
#include "nodesfactory.h"
#include "activitybody.h"
#include "usecasebody.h"
#include "statebody.h"
#include "classbody.h"
#include "topologybody.h"
#include "sequencebody.h"
#include "collaborationbody.h"

/*!\func
 * constructor
 * \param no
 * \return no
 */
Project::Project(EnterInputs *mw, QList<QSharedPointer<GraphBody> > &diagrams, const QString&_path) : file(_path)
{//
	fileName = _path + projectMainFile;
	this->mw = mw;
	this->diagrams = &diagrams;
	path = _path;
	tmpProject = false;
	if(path.isEmpty()||!QFile::exists(fileName))
	{
		QDir dir;
		do
		{
			path = dir.tempPath() + "/tmp_" + QTime::currentTime().toString("mm.ss.zzz");
		} while(dir.exists(path));
		dir.mkpath(path);
		mustBeRemoved<<path;
		tmpProject = true;
		fileName = path + projectMainFile;
	}
	simpleContent = "<?xml version='1.0' encoding='utf-8'?>\n";
	simpleContent += "<project>\n";
	simpleContent += "</project>\n";
	content = "<?xml version='1.0' encoding='utf-8'?>\n";
	content += "<project>\n";
	content += "\t<ActivityBody name=\"Activity\" />\n";
	content += "\t<UseCaseBody name=\"UseCase\" />\n";
	content += "\t<StateBody name=\"State\" />\n";
	content += "\t<TopologyBody name=\"Topology\" />\n";
	content += "\t<CollaborationBody name=\"Collaboration\" />\n";
	content += "\t<SequenceBody name=\"Sequence\" />\n";
	content += "\t<ClassBody name=\"Classes\" />\n";
	content += "</project>\n";
	create_new();
	if(file.open(QIODevice::ReadWrite))
		if (doc.setContent(&file))
		{
		}
}
/*!\func
 * remove path
 * \params
 * - path - directory
 * \return
 */
void rmdir(const QString path)
{
	QDir dir(path);
	foreach(QFileInfo entry, dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot))
	{
		if(entry.isDir())
			rmdir(entry.absoluteFilePath());
		else
			dir.remove(entry.absoluteFilePath());
	}
	dir.rmdir(path);
}
/*!\func
 * destructor
 * \param no
 * \return no
 */
Project::~Project()
{
	foreach(QString tmp, mustBeRemoved)
		rmdir(tmp);
}
/*!\func
 * load project
 * \param no
 * \return no
 */
int Project::load()
{
	QDomElement docElem = doc.documentElement();
	QDomNode n = docElem.firstChild();
	diagrams->clear();
	while(!n.isNull())
	{
		QDomElement e = n.toElement();
		GraphBody *gb = 0;
		if((e.tagName() =="ActivityBody"))
		{
			gb = new ActivityBody(mw);
		}
		if((e.tagName() =="UseCaseBody"))
		{
			gb = new UseCaseBody(mw);
		}
		if((e.tagName() =="StateBody"))
		{
			gb = new StateBody(mw);
		}
		if((e.tagName() =="TopologyBody"))
		{
			gb = new TopologyBody(mw);
		}
		if((e.tagName() =="CollaborationBody"))
		{
			gb = new CollaborationBody(mw);
		}
		if((e.tagName() =="SequenceBody"))
		{
			gb = new SequenceBody(mw);
		}
		if((e.tagName() =="ClassBody"))
		{
			gb = new ClassBody(mw);
		}
		if(gb)
		{
			gb->setTitle(e.attribute("name"));
			diagrams->append(QSharedPointer<GraphBody>(gb));
			load_node(n, gb->getParentNode(), gb);
			load_edges(n, gb);
		}
		n = n.nextSibling();
	}
	return 0;
}
/*!\func
 * save project
 * \param no
 * \return no
 */
void Project::save()
{
	if(isTmpProject())
	{
		QString tmp = QFileDialog::getSaveFileName(0, QApplication::translate("EnterInputs", "Save project..."), QDir::homePath());
		if(tmp.isEmpty())return;
		path = tmp;
		fileName = path + projectMainFile;
		QDir dir;
		dir.mkpath(path);
	}
	backup();
	if (!doc.isNull())
		doc.clear();
	file.close();
	file.remove();
	create_new();
	file.open(QIODevice::ReadWrite);
	doc.setContent(simpleContent);
	QDomElement docElem = doc.documentElement();
	foreach(QSharedPointer<GraphBody>p, *diagrams)
	{
		QDomElement e = doc.createElement(p->type());
		e.setAttribute("name", p->getTitle());
		docElem.appendChild(e);
		save_node(e, p->getParentNode());
	}
	QTextStream tf(&file);
	doc.save(tf, 4);
	doc.setContent(&file);
	tmpProject = false;
}
/*!\func
 * save one level (recurent)
 * \param no
 * \return no
 */
void Project::save_node(QDomElement& parent, INode* node)
{
	foreach(INode*item, node->nodes())
	{
		QDomElement e = doc.createElement("top");
		e.setAttribute("id", item->getId());
		e.setAttribute("name", item->getName());
		e.setAttribute("x", item->pos().x());
		e.setAttribute("y", item->pos().y());
		e.setAttribute("type", item->getType());
		e.setAttribute("short_description", item->getShortDesc());
		parent.appendChild(e);
		save_node(e, item);
		save_edge(parent, item);
	}
}
/*!\func
 * save one relation (recurent)
 * \param no
 * \return no
 */
void Project::save_edge(QDomElement& parent, INode* node)
{
	foreach(Edge*item, node->edgesIn())
	{
		QDomElement e = doc.createElement("edge");
		e.setAttribute("from", item->sourceNode()->getId());
		e.setAttribute("to", item->destNode()->getId());
		e.setAttribute("data", item->getData());
		e.setAttribute("type", item->getType());
		parent.appendChild(e);
	}
}
/*!\func
 * create new file
 * \param no
 * \return no
 */
void Project::create_new()
{
	file.setFileName(fileName);
	if(!file.exists())
	{
		file.open(QFile::WriteOnly);
		QTextStream out(&file);
		out<<content;
		file.close();
	}
}
/*!\func
 * create backup
 * \param no
 * \return no
 */
void Project::backup()
{
	file.remove(fileName + ".backup");
	file.copy(fileName + ".backup");
}
/*!\func
 * find node with id
 * \params
 * - id - id of serched node
 * \return no
 */
INode* Project::findNode(const qint32 id, INode* parent)
{
	if(!parent)return 0;
	if(parent->getId() == id)return parent;
	foreach(INode*n, parent->nodes())
	{
		if(INode* r = findNode(id, n))return r;
	}
	return 0;
}
/*!\func
 * are current project in temp directory (no saved)?
 * \param no
 * \return no
 */
bool Project::isTmpProject() const
{
	return tmpProject;
}
//! get proj name
QString Project::getProjectName()
{
	return path;
}
/*!\func
 * load one level (recurent)
 * \param no
 * \return no
 */
int Project::load_edges(QDomNode& parent, GraphBody*activity)
{
	QDomNode node = parent.firstChild();
	while(!node.isNull())
	{
		QDomElement e = node.toElement();
		if(e.tagName() =="top")
			load_edges(node, activity);
		node = node.nextSibling();
	}
	load_one_edge(parent, activity);
	return 0;
}
/*!\func
 * load one level (recurent)
 * \param no
 * \return no
 */
int Project::load_one_edge(QDomNode& parent, GraphBody*activity)
{
	QDomNode node = parent.firstChild();
	while(!node.isNull())
	{
		QDomElement e = node.toElement();
		if((e.tagName() =="edge")&&(e.hasAttribute("to"))&&(e.hasAttribute("from")))
		{
			int to = e.attribute("to").toInt();
			int from = e.attribute("from").toInt();
			INode *nto = findNode(to, activity->getParentNode()), *nfrom = findNode(from, activity->getParentNode());
			if((nto)&&(nfrom))
			{
				activity->getFactory()->newEdge((Types)e.attribute("type").toInt(), nfrom, nto, e.attribute("data"))->hide();
			}
		}
		node = node.nextSibling();
	}
	return 0;
}
/*!\func
 * load one level (recurent) activity
 * \param no
 * \return no
 */
int Project::load_node(QDomNode& parent, INode* pnode, GraphBody*activity)
{
	QDomNode node = parent.firstChild();
	static int max_id = 0;
	while(!node.isNull())
	{
		QDomElement e = node.toElement();
		if((e.tagName() =="top")&&(e.hasAttribute("id"))&&(e.hasAttribute("name")))
		{
			int id = e.attribute("id").toInt();
			if(id > max_id)max_id = id;
			INode *n = activity->getFactory()->newNode((TopTypes)e.attribute("type").toInt(), id, pnode, e.attribute("name"),e.attribute("short_description"),
												    QPointF(e.attribute("x").toDouble(), e.attribute("y").toDouble()));
			load_node(node, n, activity);
		}
		node = node.nextSibling();
	}
	pnode->hide();
	return max_id;
}
