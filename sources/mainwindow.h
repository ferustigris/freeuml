#ifndef ENTERINPUTS_H
#define ENTERINPUTS_H

#include <QtGui/QMainWindow>
#include <QMenu>
#include <QLabel>
#include <QSettings>
#include <QStringListModel>
#include "generator.h"
#include "graphbody.h"
#include "project.h"

namespace Ui
{
	class EnterInputs;
}
//! main window class
class EnterInputs : public QMainWindow
{
	Q_OBJECT
public:
	EnterInputs(QWidget *parent = 0);
	~EnterInputs();
	void setEnableUpLevel(const bool enable);
	void setLevelPath(const QString& path);
	void change(const bool changes);
private:
	Ui::EnterInputs *ui;
	QString window_title;//! first part of title
	QString project_name;//! current project
	QLabel pathLevels;
    Project *project;
	/*QSharedPointer<GraphBody> useCase;
	QSharedPointer<GraphBody> activity;
	QSharedPointer<GraphBody> fsm;
	QSharedPointer<GraphBody> topology;
	QSharedPointer<GraphBody> collaboration;
	QSharedPointer<GraphBody> sequence;
	QSharedPointer<GraphBody> classes;*/
    QList<GraphBody *> diagrams;
	GraphBody*current;
	bool hasChanges;
protected:
	void addDiagrams();
	virtual void closeEvent ( QCloseEvent * event );
	bool newProject ();
	void saveParams() const;
	void loadParams();
	/*void createNewUseCase();
	void createNewActivity();
	void createNewFSM();
	void createNewTopology();
	void createNewCollaboration();
	void createNewSequence();
	void createNewClass();*/
private slots:
	void on_actionEdit_name_of_diagram_triggered();
	void on_actionCreate_use_case_diagram_triggered();
	void on_actionCreate_topology_diagram_triggered();
	void on_actionCreate_class_diagram_triggered();
	void on_actionCreate_sequence_diagram_triggered();
	void on_actionCreate_coloboration_diagram_triggered();
	void on_actionCreate_fsm_diagram_triggered();
	void on_actionCreate_activity_diagram_triggered();
	void on_actionShow_toolbar_triggered(bool checked);
	void on_actionAdd_class_triggered();
	void on_tabCloseRequested ( int index );
	void on_actionAdd_sequence_triggered();
	void on_actionAdd_coloboration_triggered();
	void on_actionAdd_module_triggered();
	void on_actionAdd_node_triggered();
	void on_actionAdd_use_case_triggered();
	void on_actionAdd_author_triggered();
	void on_actionAdd_sync_triggered();
	void on_actionAdd_condition_triggered();
	void on_datagrams_currentChanged(int index);
	void on_actionAdd_activity_triggered();
	void on_actionCreate_project_triggered();
	void on_actionOpen_project_triggered();
	void on_actionSave_project_triggered();
	void on_actionLevel_up_triggered();
	void on_actionExit_triggered();
	void on_actionGeneration_triggered();
	void on_actionAddState_triggered();
};
#endif // ENTERINPUTS_H
