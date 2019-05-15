#include <QtTest>

// add necessary includes here
#include "../utility.h"

class Test : public QObject
{
	Q_OBJECT

public:
	Test();
	~Test();

private slots:
	void test_count_possible_repetitions0();
	void test_count_possible_repetitions1();
	void test_count_possible_repetitions2();
	void test_count_possible_repetitions3();
	void test_count_possible_repetitions4();

};

Test::Test()
{
}

Test::~Test()
{

}

void Test::test_count_possible_repetitions0()
{
	int res = Utility::count_possible_repetitions(20, 3, 15, QTime::fromString("23:00", "hh:mm"));

	QCOMPARE(res, 0);
}

void Test::test_count_possible_repetitions1()
{
	int res = Utility::count_possible_repetitions(20, 3, 15, QTime::fromString("22:16", "hh:mm"));

	QCOMPARE(res, 1);
}

void Test::test_count_possible_repetitions2()
{
	int res = Utility::count_possible_repetitions(20, 3, 15, QTime::fromString("22:15", "hh:mm"));

	QCOMPARE(res, 1);
}

void Test::test_count_possible_repetitions3()
{
	int res = Utility::count_possible_repetitions(25, 5, 30, QTime::fromString("21:35", "hh:mm"));

	QCOMPARE(res, 1);
}

void Test::test_count_possible_repetitions4()
{
	int res = Utility::count_possible_repetitions(25, 5, 30, QTime::fromString("21:36", "hh:mm"));

	QCOMPARE(res, 0);
}

QTEST_APPLESS_MAIN(Test)

#include "tst_test.moc"
