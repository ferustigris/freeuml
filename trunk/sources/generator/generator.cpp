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
 * \param ���
 * \return ���
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
 * \param ���
 * \return ���
 */
Generator::~Generator()
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    delete m_ui;
}
/*!\func
 *
 * \param ���
 * \return ���
 */
void Generator::closeEvent ( QCloseEvent * )
{
	m_ui->pbNext->setText(tr("Next"));
	m_ui->pbCancel->setText(tr("Cancel"));
}
/*!\func
 *
 * \param ���
 * \return ���
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
 * �������� �� ������ ������
 * \param ���
 * \return ���
 */
void Generator::on_pbCancel_clicked()
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    close();
}
/*!\func
 * �������� ��������� � ���
 * \param
 * - msg - ���������
 * \return ���
 */
void Generator::addLog(const QString& msg)
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    m_ui->lwLog->addItem(msg);
}
/*!\func
 * �������� ������� ��������� � ���
 * \param
 * - msg - ���������
 * \return ���
 */
void Generator::addOk(const QString& msg)
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    QListWidgetItem *item = new QListWidgetItem(QIcon(":/icons/ok"), msg, m_ui->lwLog);
    m_ui->lwLog->addItem(item);
}
/*!\func
 * �������� ������ ��������� � ���
 * \param
 * - msg - ���������
 * \return ���
 */
void Generator::addWarning(const QString& msg)
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    QListWidgetItem *item = new QListWidgetItem(QIcon(":/icons/bad"), msg, m_ui->lwLog);
    m_ui->lwLog->addItem(item);
}
/*!\func
 * �������� ��������� � ���
 * \param
 * - msg - ���������
 * \return ���
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
 * ��������� ���� ��� ����� ����, ����������� �������
 * \param
 * - node - ������� �������
 * \return no
 */
void Generator::genNodeCode(const QString&startDir, INode* n, const QString&parentDir, QTextStream &xise)
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
}
/*!\func
 * ���������������, ���������
 * \param ���
 * \return ���
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
 * �������� ����������
 * \param ���
 * \return ���
 */
void Generator::checkValidate()
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    if(!node)
    {
	LOG(LOG_ERROR, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + "> - �� ����������� ������ ���������!");
	return;
    }
    bool ok = true;
    addLog(tr("Check validate..."));
    if(ok)
	addOk(tr("All right!"));
    m_ui->pbNext->setEnabled(true);
}
