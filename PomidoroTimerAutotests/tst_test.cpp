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
	void test_count_possible_repetitions5();

};

Test::Test()
{
}

Test::~Test()
{

}

void Test::test_count_possible_repetitions0()
{
	int res;
	QTime time;

	std::tie(res, time) = Utility::count_possible_repetitions(20, 3, 15, QTime::fromString("23:00", "hh:mm"));

	QCOMPARE(res, 0);
	QCOMPARE(time, QTime::fromString("23:00", "hh:mm"));
}

void Test::test_count_possible_repetitions1()
{
	int res = Utility::count_possible_repetitions(20, 3, 15, QTime::fromString("22:16", "hh:mm")).first;
	QTime finishTime;

	std::tie(res, finishTime) = Utility::count_possible_repetitions(20, 3, 15, QTime::fromString("22:16", "hh:mm"));

	QCOMPARE(res, 1);
	QCOMPARE(finishTime, QTime::fromString("00:00", "hh:mm"));
}

void Test::test_count_possible_repetitions2()
{
	int res;
	QTime finishTime;

	std::tie(res, finishTime) = Utility::count_possible_repetitions(20, 3, 15, QTime::fromString("22:15", "hh:mm"));

	QCOMPARE(res, 1);
	QCOMPARE(finishTime, QTime::fromString("23:59", "hh:mm"));
}

void Test::test_count_possible_repetitions3()
{
	int res;
	QTime finishTime;
	std::tie(res, finishTime) = Utility::count_possible_repetitions(25, 5, 30, QTime::fromString("21:35", "hh:mm"));

	QCOMPARE(res, 1);
	QCOMPARE(finishTime, QTime::fromString("00:00", "hh:mm"));
}

void Test::test_count_possible_repetitions4()
{
	int res;
	QTime finishTime;
	std::tie(res, finishTime) = Utility::count_possible_repetitions(25, 5, 30, QTime::fromString("21:36", "hh:mm"));

	QCOMPARE(res, 0);
	QCOMPARE(finishTime, QTime::fromString("21:36", "hh:mm"));
}

void Test::test_count_possible_repetitions5()
{
	int res;
	QTime finishTime;
	std::tie(res, finishTime) = Utility::count_possible_repetitions(10, 5, 15, QTime::fromString("21:41", "hh:mm"));

	QCOMPARE(res, 1);
	QCOMPARE(finishTime, QTime::fromString("22:51", "hh:mm"));
}

QTEST_APPLESS_MAIN(Test)

#include "tst_test.moc"