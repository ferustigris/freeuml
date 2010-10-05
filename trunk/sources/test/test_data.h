#ifndef TEST_DATA_H
#define TEST_DATA_H

#include <QObject>
#include <QTest>

class Test_Data : public QObject
{
Q_OBJECT
public:
	explicit Test_Data(QObject *parent = 0);
signals:

private slots:
	void states_data();
	void states();
};

#endif // TEST_DATA_H
