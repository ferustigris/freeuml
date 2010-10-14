#include "mainwindow.h"
#include "errors.h"
#include "inode.h"
#include <QCloseEvent>
#include <QTime>
#include <QMessageBox>
#include <QFileDialog>
#include "ui_mainwindow.h"
#include "activitybody.h"
#include "usecasebody.h"
#include "statebody.h"
#include "classbody.h"
#include "topologybody.h"
#include "sequencebody.h"
#include "collaborationbody.h"

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
	ui->statusBar->addWidget(&pathLevels);
	loadParams();
	window_title = windowTitle ();
	change(false);
	newProject();
	ui->datagrams->setCurrentIndex(0);
}
/*!\func
 * destructor
 * \params no
 * \return no
 */
EnterInputs::~EnterInputs()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
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
 * create new body for draw
 * \params no
 * \return no
 */
void EnterInputs::createNewUseCase()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	useCase = QSharedPointer<GraphBody>(new UseCaseBody(this));
	ui->useCaseLayout->addWidget(useCase.data());
}
/*!\func
 * create new body for activity diagram
 * \params no
 * \return no
 */
void EnterInputs::createNewActivity()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	activity = QSharedPointer<GraphBody>(new ActivityBody(this));
	ui->activityLayout->addWidget(activity.data());
}
/*!\func
 * create new body for state (fsm) diagram
 * \params no
 * \return no
 */
void EnterInputs::createNewFSM()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	fsm = QSharedPointer<GraphBody>(new StateBody(this));
	ui->fsmLayout->addWidget(fsm.data());
}
/*!\func
 * create new body for topology diagram
 * \params no
 * \return no
 */
void EnterInputs::createNewTopology()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	topology = QSharedPointer<GraphBody>(new TopologyBody(this));
	ui->topologyLayout->addWidget(topology.data());
}
/*!\func
 * create new body for topology diagram
 * \params no
 * \return no
 */
void EnterInputs::createNewCollaboration()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	collaboration = QSharedPointer<GraphBody>(new CollaborationBody(this));
	ui->coloborationLayout->addWidget(collaboration.data());
}
/*!\func
 * create new body for Sequence diagram
 * \params no
 * \return no
 */
void EnterInputs::createNewSequence()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	sequence = QSharedPointer<GraphBody>(new SequenceBody(this));
	ui->sequenceLayout->addWidget(sequence.data());
}
/*!\func
 * create new body for class diagram
 * \params no
 * \return no
 */
void EnterInputs::createNewClass()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	classes = QSharedPointer<GraphBody>(new ClassBody(this));
	ui->classLayout->addWidget(classes.data());
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
	createNewActivity();
	createNewUseCase();
	createNewFSM();
	createNewTopology();
	createNewCollaboration();
	createNewSequence();
	createNewClass();
	project = QSharedPointer<Project>(new Project(activity.data(), useCase.data(), fsm.data(), topology.data(), collaboration.data(), sequence.data(), classes.data(), project_name));
	project->load();
	setWindowTitle(window_title + " - " + project->getProjectName());
	on_datagrams_currentChanged(0);
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
 * show tool bar
 * \params no
 * \return no
 */
void EnterInputs::on_actionShow_toolbar_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	ui->mainToolBar->show();
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
	switch(index)
	{
	case 0://activity
		ui->actionAdd_activity->setVisible(true);
		ui->actionAdd_condition->setVisible(true);
		ui->actionAdd_sync->setVisible(true);
		current = activity.data();
		break;
	case 1://use case
		ui->actionAdd_use_case->setVisible(true);
		ui->actionAdd_author->setVisible(true);
		current = useCase.data();
		break;
	case 2://fsm
		current = fsm.data();
		ui->actionAddState->setVisible(true);
		break;
	case 3://topology
		current = topology.data();
		ui->actionAdd_node->setVisible(true);
		ui->actionAdd_module->setVisible(true);
		break;
	case 4://collaboration
		current = collaboration.data();
		ui->actionAdd_coloboration->setVisible(true);
		break;
	case 5://sequence
		current = sequence.data();
		ui->actionAdd_sequence->setVisible(true);
		break;
	case 6://class
		current = classes.data();
		ui->actionAdd_class->setVisible(true);
		break;
	}
	current->reflesh();
}
/*!\func
 * new activity
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_activity_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	activity->addTop(TOP_ACTIVITY);
}
/*!\func
 * add new condition to activity diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_condition_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	activity->addTop(TOP_IF);
}
/*!\func
 * add new sync to activity diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_sync_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	activity->addTop(TOP_SYNC);
}
/*!\func
 * add new author to use case diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_author_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	useCase->addTop(TOP_AUTHOR);
}
/*!\func
 * add new use case to use case diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_use_case_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	useCase->addTop(TOP_USECASE);
}
/*!\func
 * add new state to fsm diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAddState_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	fsm->addTop(TOP_SIMPLE);
}
/*!\func
 * add new node to topology diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_node_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	topology->addTop(TOP_HOST);
}
/*!\func
 * add new module to topology diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_module_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	topology->addTop(TOP_ACTIVITY);
}
/*! \func
 * add new component to collaboration diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_coloboration_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	collaboration->addTop(TOP_ACTIVITY);
}
/*! \func
 * add new sequence to sequence diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_sequence_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	sequence->addTop(TOP_SEQUENCE);
}
/*! \func
 * add new class to diagram
 * \params no
 * \return no
 */
void EnterInputs::on_actionAdd_class_triggered()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	classes->addTop(TOP_CLASS);
}
