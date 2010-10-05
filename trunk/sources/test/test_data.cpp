#include <QDebug>
#include "test_data.h"
#include "nodesfactory.h"

Test_Data::Test_Data(QObject *parent) :
    QObject(parent)
{
}
/*!\func
 * data for states test
 * \param no
 * \return no
 */
void Test_Data::states_data()
{
	QTest::addColumn<QString>("name");
	QTest::addColumn<QString>("desc");
	QTest::newRow("state test 1")<<"test1"<<"d1";
	QTest::newRow("state test 2")<<"a123"<<"d2";
	QTest::newRow("state test 3")<<"asd"<<"sdfgfdghdfsgjeiopr";
}
/*!\func
 * states test
 * \param no
 * \return no
 */
void Test_Data::states()
{
	QFETCH(QString, name);
	QFETCH(QString, desc);
	QCOMPARE(1,1);
	//QVERIFY()
}
QTEST_MAIN(Test_Data)
