#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "../utility.h"

#include "../pomidoro.h"

#include "../state.h"

class test : public QObject
{
	Q_OBJECT

public:
	test();
	~test();

private slots:
	void test_count_possible_repetitions0();
	void test_count_possible_repetitions1();
	void test_count_possible_repetitions2();
	void test_count_possible_repetitions3();
	void test_count_possible_repetitions4();
	void test_count_possible_repetitions5();

	void test_next_completion0();
	void test_next_completion1();
	void test_next_completion2();
	void test_next_completion3();

	void test_main_logic0();
	void test_main_logic1();
	void test_main_logic2();
	void test_main_logic3();
};

test::test()
{

}

test::~test()
{

}

void test::test_count_possible_repetitions0()
{
	int res;
	QTime time;

	std::tie(res, time) = Utility::count_possible_repetitions(20, 3, 15, QTime::fromString("23:00", "hh:mm"));

	QCOMPARE(res, 0);
	QCOMPARE(time, QTime::fromString("23:00", "hh:mm"));
}

void test::test_count_possible_repetitions1()
{
	int res = Utility::count_possible_repetitions(20, 3, 15, QTime::fromString("22:16", "hh:mm")).first;
	QTime finishTime;

	std::tie(res, finishTime) = Utility::count_possible_repetitions(20, 3, 15, QTime::fromString("22:16", "hh:mm"));

	QCOMPARE(res, 1);
	QCOMPARE(finishTime, QTime::fromString("00:00", "hh:mm"));
}

void test::test_count_possible_repetitions2()
{
	int res;
	QTime finishTime;

	std::tie(res, finishTime) = Utility::count_possible_repetitions(20, 3, 15, QTime::fromString("22:15", "hh:mm"));

	QCOMPARE(res, 1);
	QCOMPARE(finishTime, QTime::fromString("23:59", "hh:mm"));
}

void test::test_count_possible_repetitions3()
{
	int res;
	QTime finishTime;
	std::tie(res, finishTime) = Utility::count_possible_repetitions(25, 5, 30, QTime::fromString("21:35", "hh:mm"));

	QCOMPARE(res, 1);
	QCOMPARE(finishTime, QTime::fromString("00:00", "hh:mm"));
}

void test::test_count_possible_repetitions4()
{
	int res;
	QTime finishTime;
	std::tie(res, finishTime) = Utility::count_possible_repetitions(25, 5, 30, QTime::fromString("21:36", "hh:mm"));

	QCOMPARE(res, 0);
	QCOMPARE(finishTime, QTime::fromString("21:36", "hh:mm"));
}

void test::test_count_possible_repetitions5()
{
	int res;
	QTime finishTime;
	std::tie(res, finishTime) = Utility::count_possible_repetitions(10, 5, 15, QTime::fromString("21:41", "hh:mm"));

	QCOMPARE(res, 1);
	QCOMPARE(finishTime, QTime::fromString("22:51", "hh:mm"));
}

void test::test_next_completion0()
{
	auto res = Utility::next_completion(20, 3, QTime::fromString("13:00", "hh:mm"));

	QCOMPARE(res, QTime::fromString("14:29", "hh:mm"));
}

void test::test_next_completion1()
{
	auto res = Utility::next_completion(20, 3, QTime::fromString("23:30", "hh:mm"));

	QCOMPARE(res, QTime::fromString("00:59", "hh:mm"));
}

void test::test_next_completion2()
{
	auto res = Utility::next_completion(10, 5, QTime::fromString("23:47", "hh:mm"));

	QCOMPARE(res, QTime::fromString("00:42", "hh:mm"));
}

void test::test_next_completion3()
{
	auto res = Utility::next_completion(25, 5, QTime::fromString("00:00", "hh:mm"));

	QCOMPARE(res, QTime::fromString("01:55", "hh:mm"));
}

void test::test_main_logic0()
{
	Pomidoro* pomidoro = new Pomidoro(nullptr);

	QCOMPARE(pomidoro->getActiveState()->type(), State::STATES::ACTIVE);
	QCOMPARE(pomidoro->getInactiveState()->type(), State::STATES::INACTIVE);
	QCOMPARE(pomidoro->getPausedState()->type(), State::STATES::PAUSED);
	QCOMPARE(pomidoro->getShortRestState()->type(), State::STATES::SHORT_REST);
	QCOMPARE(pomidoro->getLongRestState()->type(), State::STATES::LONG_REST);

	delete pomidoro;

	State::clearLog();
}

void test::test_main_logic1()
{
	Pomidoro* pomidoro = new Pomidoro(nullptr);
	QCOMPARE(pomidoro->getState()->type(), State::STATES::INACTIVE);

	delete pomidoro;
	State::clearLog();
}

void test::test_main_logic2()
{
	Pomidoro* pomidoro = new Pomidoro(this);

	pomidoro->slotStart();

	QCOMPARE(pomidoro->getState()->type(), State::STATES::ACTIVE);

	pomidoro->slotPause();

	QCOMPARE(pomidoro->getState()->type(), State::STATES::PAUSED);

	pomidoro->slotStart();

	QCOMPARE(pomidoro->getState()->type(), State::STATES::ACTIVE);

	pomidoro->slotStop();

	QCOMPARE(pomidoro->getState()->type(), State::STATES::INACTIVE);

	delete pomidoro;
	State::clearLog();
}

void test::test_main_logic3()
{
	Pomidoro* pomidoro = new Pomidoro(nullptr);

	delete pomidoro;
}

QTEST_MAIN(test)

#include "tst_test.moc"