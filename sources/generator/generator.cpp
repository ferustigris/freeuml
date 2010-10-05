#include "generator.h"
#include "ui_generator.h"
#include "errors.h"
#include <QFile>
#include <QFileDialog>
#include <QProcess>
#include <node.h>
#include "project.h"

/*!\func
 *
 * \param нет
 * \return нет
 */
Generator::Generator(INode *_node, QWidget *parent) :
		QDialog(parent),
		m_ui(new Ui::Generator)
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	node = _node;
	m_ui->setupUi(this);
}
/*!\func
 *
 * \param нет
 * \return нет
 */
Generator::~Generator()
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    delete m_ui;
}
/*!\func
 *
 * \param нет
 * \return нет
 */
void Generator::closeEvent ( QCloseEvent * )
{
	m_ui->pbNext->setText(tr("Next"));
	m_ui->pbCancel->setText(tr("Cancel"));
}
/*!\func
 *
 * \param нет
 * \return нет
 */
void Generator::changeEvent(QEvent *e)
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
	m_ui->retranslateUi(this);
	break;
    default:
	break;
    }
}
/*!\func
 * нажюатие на кнопку отмена
 * \param нет
 * \return нет
 */
void Generator::on_pbCancel_clicked()
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    close();
}
/*!\func
 * добавить сообщение в лог
 * \param
 * - msg - сообщение
 * \return нет
 */
void Generator::addLog(const QString& msg)
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    m_ui->lwLog->addItem(msg);
}
/*!\func
 * добавить хорошее сообщение в лог
 * \param
 * - msg - сообщение
 * \return нет
 */
void Generator::addOk(const QString& msg)
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    QListWidgetItem *item = new QListWidgetItem(QIcon(":/icons/ok"), msg, m_ui->lwLog);
    m_ui->lwLog->addItem(item);
}
/*!\func
 * добавить плохое сообщение в лог
 * \param
 * - msg - сообщение
 * \return нет
 */
void Generator::addWarning(const QString& msg)
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    QListWidgetItem *item = new QListWidgetItem(QIcon(":/icons/bad"), msg, m_ui->lwLog);
    m_ui->lwLog->addItem(item);
}
/*!\func
 * добавить сообщение в лог
 * \param
 * - msg - сообщение
 * \return нет
 */
void Generator::on_pbNext_clicked()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	static bool closeble = false;
	if(closeble)
	{
		closeble = false;
		close();
		return;
	}
	generate();
	m_ui->pbNext->setText(tr("Close"));
	m_ui->pbCancel->setEnabled(false);
	closeble = true;
}
/*!\func
 * генерация кода для одной ноды, итеративная функция
 * \param
 * - node - текущая вершина
 * \return no
 */
void Generator::genNodeCode(const QString&startDir, INode* n, const QString&parentDir, QTextStream &xise)
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
}
/*!\func
 * непосредственно, генерация
 * \param нет
 * \return нет
 */
void Generator::generate()
{
	LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	if(!node)return;
	QString fn = QFileDialog::getSaveFileName(this, tr("Save project..."), QString(), tr("All Files (*)"));
	if(fn.isEmpty())return;
	QDir dir;
	dir.mkpath(fn);
	dir.setCurrent(fn);
//	genNodeCode(dir.currentPath() + "/", node, dir.currentPath(), xise);
	addOk(tr("Complite."));
}
/*!\func
 * проверка валидности
 * \param нет
 * \return нет
 */
void Generator::checkValidate()
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    if(!node)
    {
	LOG(LOG_ERROR, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + "> - не установлена модель состояний!");
	return;
    }
    bool ok = true;
    addLog(tr("Check validate..."));
    if(ok)
	addOk(tr("All right!"));
    m_ui->pbNext->setEnabled(true);
}
