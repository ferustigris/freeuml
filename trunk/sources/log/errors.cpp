#include "errors.h"
#include <QDir>
#include <QCoreApplication>

/*! \func
 * constructor
 * \params no
 * \return no
 */
Log::Log(const quint8 maxlevel, const QString&log_name)
{
	QDir dir;
	this->maxlevel = maxlevel;
	QString path(qApp->applicationDirPath() + "/../var/log/");
	dir.mkpath(path);
	file.setFileName(path + log_name);
	file.open(QIODevice::ReadWrite | QIODevice::Text);
	out.setDevice(&file);
}
/*!\func LOG
 * ���������� ��������� � ������
 * \param
 * - level - ��������� ���������
 * - msg - ���������
 * - _maxlevel - ������� ��������������
 * - log_file - ���� �������
 * \return ���
 */
void Log::log(quint8 level, QString msg)
{
	static Log logger(3, "main.log");
	if(level > logger.maxlevel)return;
	logger.out.seek(logger.file.size());
	logger.out<<msg<<"\n";
}
/*!\func LOG
 * ������ �����
 * \param
 * - _name - ��� ������, ��������
 * \return ���
 */
ECommonError::ECommonError(const QString & _name) {
    name = _name;
	LOG(LOG_ERROR, name);
}
/*!\func LOG
 * ������ ���������� �� �������, �� ��������� ��� ����������
 * \param
 * - _name - ��� ������, ��������
 * \return ���
 */
ELibraryNotFound::ELibraryNotFound(const QString &name):ECommonError(name){
    LOG(LOG_APPER, name);
}
