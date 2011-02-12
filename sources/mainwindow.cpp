#include "mainwindow.h"
#include "errors.h"
#include "inode.h"
#include <QCloseEvent>
#include <QTime>
#include <QInputDialog>
#include "graphbody.h"
#include "nodesfactory.h"
#include "activitybody.h"
#include "usecasebody.h"
#include "statebody.h"
#include "classbody.h"
#include "topologybody.h"
#include "sequencebody.h"
#include "collaborationbody.h"


#include <QMessageBox>
#include <QFileDialog>
#include "ui_mainwindow.h"

/*!\func
 * constructor
 * \params
 * - parent - parent
 * \return no
 */
EnterInputs::EnterInputs(QWidget *parent)
	: QMainWindow(parent),
	ui(new Ui::EnterInputs)
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	ui->setupUi(this);
	current = 0;
	ui->statusBar->addWidget(&pathLevels);
	loadParams();
	window_title = windowTitle ();
	change(false);
	newProject();
	ui->datagrams->setCurrentIndex(0);
	connect(ui->datagrams, SIGNAL(tabCloseRequested ( int)), this, SLOT(on_tabCloseRequested ( int)));
}
/*!\func
 * destructor
 * \params no
 * \return no
 */
EnterInputs::~EnterInputs()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	current = 0;
	while(ui->datagrams->count() > 0)
	{
		ui->datagrams->removeTab(0);
		current = 0;
	}
	delete ui;
}
/*!\func
 * save params in file
 * \params no
 * \return no
 */
void EnterInputs::saveParams() const
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	QSettings settings(qApp->applicationDirPath() + "/../etc/" + "config_struct.ini", QSettings::IniFormat);
	settings.beginGroup("project");
	settings.setValue("current_project", project_name);
	settings.endGroup();
	settings.beginGroup("window");
	settings.setValue("x", geometry().x());
	settings.setValue("y", geometry().y());
	settings.setValue("width", geometry().width());
	settings.setValue("height", geometry().height());
	settings.endGroup();
}
/*!\func
 * load params from file
 * \params no
 * \return no
 */
void EnterInputs::loadParams()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	QSettings settings(qApp->applicationDirPath() + "/../etc/" + "config_struct.ini", QSettings::IniFormat);
	settings.beginGroup("window");
	setGeometry(settings.value("x").toInt(),settings.value("y").toInt(),
		settings.value("width").toInt(),settings.value("height").toInt());
	settings.endGroup();
	settings.beginGroup("project");
	project_name = settings.value("current_project").toString();
	settings.endGroup();
}
/*!\func
 * user said: generate code!
 * \params no
 * \return no
 */
void EnterInputs::on_actionGeneration_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	/*static Generator generator(useCase->getParentNode());
	generator.setModal(true);
	generator.show();
	generator.checkValidate();
	*/
}
/*!\func
 * user said: exit from program
 * \params no
 * \return no
 */
void EnterInputs::on_actionExit_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	close();
}
/*!\func
 * user said: level up
 * \params no
 * \return no
 */
void EnterInputs::on_actionLevel_up_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(current)
		ui->actionLevel_up->setEnabled(current->levelUp());
}
/*!\func
 * user said: save current project
 * \params no
 * \return no
 */
void EnterInputs::on_actionSave_project_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	project->save();
	change(false);
	setWindowTitle(window_title + " - "  + project->getProjectName());
}
/*!\func
 * form closed
 * \params no
 * \return no
 */
void EnterInputs::closeEvent ( QCloseEvent * event )
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	Q_UNUSED(event)
	if(hasChanges)
		switch(QMessageBox::question(0, tr("Saving project..."),
					     tr("Are you want save project before close it?"),
					     QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel))
		{
		case QMessageBox::Yes:
		on_actionSave_project_triggered();
		break;
		case QMessageBox::Cancel:
		event->ignore();
		return;
		default:
		;;
	}
	event->accept();
	saveParams();
}
/*!\func
 * user want open existed project
 * \params no
 * \return no
 */
void EnterInputs::on_actionOpen_project_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(hasChanges)
		if(QMessageBox::question(0, tr("Saving project..."), tr("Are you want save project before close it?"), QMessageBox::Yes, QMessageBox::No, 0) == QMessageBox::Yes)
			on_actionSave_project_triggered();
	QString project_path = QFileDialog::getOpenFileName(0, tr("Open project..."), QDir::homePath(), tr("Projects (project.xml);;"));
	if(project_path.isEmpty())return;
	project_path.replace(projectMainFile, "");
	QDir dir;
	dir.mkpath(project_path);
	project_name = project_path;
	newProject();
}
/*!\func
 * user want create new project
 * \params no
 * \return no
 */
void EnterInputs::on_actionCreate_project_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(hasChanges)
		if(QMessageBox::question(0, tr("Saving project..."), tr("Are you want save project before close it?"), QMessageBox::Yes, QMessageBox::No, 0) == QMessageBox::Yes)
			project->save();
	project_name = "";
	newProject();
}
/*!\func
 * create new project
 * \params no
 * \return no
 */
bool EnterInputs::newProject ()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	/*createNewActivity();
	createNewUseCase();
	createNewFSM();
	createNewTopology();
	createNewCollaboration();
	createNewSequence();
	createNewClass();*/
	project = QSharedPointer<Project>(new Project(this, diagrams, project_name));//new Project(activity.data(), useCase.data(), fsm.data(), topology.data(), collaboration.data(), sequence.data(), classes.data(), project_name));
	project->load();
	setWindowTitle(window_title + " - " + project->getProjectName());
	addDiagrams();
	return true;
}
/*!\func
 * enable or disable button "levelup"
 * \params
 * - enable - enable or disable
 * \return no
 */
void EnterInputs::setEnableUpLevel(const bool enable)
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	ui->actionLevel_up->setEnabled(enable);
}
/*!\func
 * set level path in status bar
 * \params
 * - path - path
 * \return no
 */
void EnterInputs::setLevelPath(const QString& path)
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	pathLevels.setText(path);
}
/*!\func
 * set changes flag, is current project saved?
 * \params
 * - changes - are changes present?
 * \return no
 */
void EnterInputs::change(const bool changes)
{
	hasChanges = changes;
	ui->actionSave_project->setEnabled(changes);
}
/*!\func
 * select diagram
 * \params
 * - index - diagram number
 * \return no
 */
void EnterInputs::on_datagrams_currentChanged(int index)
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	current = 0;
	ui->actionAdd_activity->setVisible(false);
	ui->actionAdd_condition->setVisible(false);
	ui->actionAddState->setVisible(false);
	ui->actionAdd_sync->setVisible(false);
	ui->actionAdd_use_case->setVisible(false);
	ui->actionAdd_author->setVisible(false);
	ui->actionAdd_node->setVisible(false);
	ui->actionAdd_module->setVisible(false);
	ui->actionAdd_coloboration->setVisible(false);
	ui->actionAdd_sequence->setVisible(false);
	ui->actionAdd_class->setVisible(false);
	if((index < diagrams.count()) && (index >= 0))
		current = diagrams[index].data();
	if(current)
	{
		if(current->type() == "ActivityBody")
		{
			ui->actionAdd_activity->setVisible(true);
			ui->actionAdd_condition->setVisible(true);
			ui->actionAdd_sync->setVisible(true);
		}
		else if(current->type() == "UseCaseBody")
		{
			ui->actionAdd_use_case->setVisible(true);
			ui->actionAdd_author->setVisible(true);
		}
		else if(current->type() == "StateBody")
		{
			ui->actionAddState->setVisible(true);
		}
		else if(current->type() == "TopologyBody")
		{
			ui->actionAdd_node->setVisible(true);
			ui->actionAdd_module->setVisible(true);
		}
		else if(current->type() == "CollaborationBody")
		{
			ui->actionAdd_coloboration->setVisible(true);
		}
		else if(current->type() == "SequenceBody")
		{
			ui->actionAdd_sequence->setVisible(true);
		}
		else if(current->type() == "ClassBody")
		{
			ui->actionAdd_class->setVisible(true);
		}
		current->reflesh();
	}
}
/*!\func
 * new activity
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_activity_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(current)
		current->addTop(TOP_ACTIVITY);
}
/*!\func
 * add new condition to activity diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_condition_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(current)
		current->addTop(TOP_IF);
}
/*!\func
 * add new sync to activity diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_sync_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(current)
		current->addTop(TOP_SYNC);
}
/*!\func
 * add new author to use case diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_author_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(current)
		current->addTop(TOP_AUTHOR);
}
/*!\func
 * add new use case to use case diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_use_case_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(current)
		current->addTop(TOP_USECASE);
}
/*!\func
 * add new state to fsm diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAddState_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(current)
		current->addTop(TOP_SIMPLE);
}
/*!\func
 * add new node to topology diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_node_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(current)
		current->addTop(TOP_HOST);
}
/*!\func
 * add new module to topology diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_module_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(current)
		current->addTop(TOP_ACTIVITY);
}
/*! \func
 * add new component to collaboration diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_coloboration_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(current)
		current->addTop(TOP_ACTIVITY);
}
/*! \func
 * add new sequence to sequence diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_sequence_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(current)
		current->addTop(TOP_SEQUENCE);
}
/*! \func
 * add new class to diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_class_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(current)
		current->addTop(TOP_CLASS);
}
/*!\func
 * show tool bar
 * \params no
 * \return no
 */
void EnterInputs::on_actionShow_toolbar_triggered(bool checked)
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(checked)ui->mainToolBar->show();
	else
		ui->mainToolBar->hide();
}
/*! \func
 * add diagrams to layouts
 * \params no
 * \return no
 */
void EnterInputs::addDiagrams()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	current = 0;
	while(ui->datagrams->count() > 0)
	{
		ui->datagrams->removeTab(0);
		current = 0;
	}
	foreach(QSharedPointer<GraphBody>p, diagrams)
	{
		ui->datagrams->addTab(p.data(), QIcon(":/icon/" + p->type()), p->getTitle());
	}
	ui->datagrams->setTabsClosable(true);
}
/*! \func
 * create new diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionCreate_activity_diagram_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	GraphBody *gb = new ActivityBody(this);
	gb->setTitle(gb->type() + "_" + QString::number(diagrams.count()));
	diagrams.append(QSharedPointer<GraphBody>(gb));
	addDiagrams();
	change(true);
}
/*! \func
 * create new diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionCreate_fsm_diagram_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	GraphBody *gb = new StateBody(this);
	gb->setTitle(gb->type() + "_" + QString::number(diagrams.count()));
	diagrams.append(QSharedPointer<GraphBody>(gb));
	addDiagrams();
	change(true);
}
/*! \func
 * create new diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionCreate_coloboration_diagram_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	GraphBody *gb = new CollaborationBody(this);
	gb->setTitle(gb->type() + "_" + QString::number(diagrams.count()));
	diagrams.append(QSharedPointer<GraphBody>(gb));
	addDiagrams();
	change(true);
}
/*! \func
 * create new diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionCreate_sequence_diagram_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	GraphBody *gb = new SequenceBody(this);
	gb->setTitle(gb->type() + "_" + QString::number(diagrams.count()));
	diagrams.append(QSharedPointer<GraphBody>(gb));
	addDiagrams();
	change(true);
}
/*! \func
 * create new diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionCreate_class_diagram_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	GraphBody *gb = new ClassBody(this);
	gb->setTitle(gb->type() + "_" + QString::number(diagrams.count()));
	diagrams.append(QSharedPointer<GraphBody>(gb));
	addDiagrams();
	change(true);
}
/*! \func
 * create new diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionCreate_topology_diagram_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	GraphBody *gb = new TopologyBody(this);
	gb->setTitle(gb->type() + "_" + QString::number(diagrams.count()));
	diagrams.append(QSharedPointer<GraphBody>(gb));
	addDiagrams();
	change(true);
}
/*! \func
 * create new diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionCreate_use_case_diagram_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	GraphBody *gb = new UseCaseBody(this);
	gb->setTitle(gb->type() + "_" + QString::number(diagrams.count()));
	diagrams.append(QSharedPointer<GraphBody>(gb));
	addDiagrams();
	change(true);
}
/*! \func
 * remove diagram
 * \params no
 * \return no
 */
void EnterInputs::on_tabCloseRequested ( int index )
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	change(true);
	for(int cur = 0; cur < diagrams.count(); cur++)
	{
		if(cur != index)
		{
			ui->datagrams->setCurrentIndex(cur);
			if(diagrams.count() > index && index >= 0)
			{
				ui->datagrams->removeTab(index);
				diagrams.removeAt(index);
				addDiagrams();
				break;
			}
		}
	}
}
/*! \func
 * remove diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionEdit_name_of_diagram_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(current)
	{
		bool ok;
		QString text = QInputDialog::getText(this, tr("Name of active diagram"),
												tr("New name:"), QLineEdit::Normal,
												current->getTitle(), &ok);
		if(ok)
		{
			current->setTitle(text);
			ui->datagrams->setTabText(ui->datagrams->currentIndex(), text);
		}
	}

}
