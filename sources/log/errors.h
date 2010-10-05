#ifndef ERRORS_H
#define ERRORS_H
#include <QFile>
#include <QTextStream>
const quint8 LOG_DEBUG = 7;
const quint8 LOG_ERROR = 2;
const quint8 LOG_APPER = 3;

#define LOG(x,y); Log::log(x,y);
//! class for log errors
class Log {
	Log(const quint8 maxlevel, const QString&log_name);
	QFile file;
	QTextStream out;
	quint8 maxlevel;
public:
	static void log(quint8 level, QString msg);
};
/*! класс предок исключений*/
class ECommonError {
public:
    ECommonError(const QString & _name);
    const QString& getName() {
        return name;
    }
public:
    QString name;
};
/*! класс исключения не найдена библиотека */
class ELibraryNotFound : public ECommonError {
public:
    ELibraryNotFound(const QString &name);
};

#endif // ERRORS_H
