#include <QtGui/QApplication>
#include <QTranslator>
#include "mainwindow.h"
#include "errors.h"

/*!\func
 * точка входа в программу
 * \param
 * - кол-во арг-ов ком. строки
 * - аргументы ком. строки
 * \return no
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    QTranslator translator;
    translator.load(":/tr/" + QLocale::system().name());
    a.installTranslator(&translator);
    EnterInputs w;
    w.show();
    return a.exec();
}
