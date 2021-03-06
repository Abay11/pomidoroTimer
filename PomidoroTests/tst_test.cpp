#include <QtTest>

// add necessary includes here
#include "../utility.h"

#include "../pomidoro.h"

#include "../state.h"

#include "../threadcontroller.h"

#include "../datasaver.h"

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

	void test_thread_controller();

	void test_pomidoro_activity_state0();

	void test_main_logic0();
	void test_main_logic1();
	void test_main_logic2();
	void test_main_logic3();
	void test_main_logic4();

	void test_data_saving_restoring();

	void test_formatTimerRemainingToString();
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

void test::test_thread_controller()
{
	ThreadController* controller = new ThreadController;

	controller->run();

	controller->stop();

	delete controller;
}

void test::test_pomidoro_activity_state0()
{
	ThreadController* controller = new ThreadController;

	Pomidoro* pomidoro = controller->pomidoro();
	pomidoro->setDurations(1, 0, 0);

	controller->run();
	QCOMPARE(pomidoro->isRunning(), false);

	controller->startPomidoro();
	QThread::msleep(50);
	QCOMPARE(pomidoro->isRunning(), true);

	controller->stopPomidoro();
	QThread::msleep(50);
	QCOMPARE(pomidoro->isRunning(), false);

	controller->stop();

	delete pomidoro;
	State::clearLog();
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
	ThreadController* controller = new ThreadController;

	Pomidoro* pomidoro = controller->pomidoro();
	pomidoro->setDurations(1, 0, 0);

	controller->run();

	controller->startPomidoro();

	QThread::msleep(50);
	QCOMPARE(pomidoro->getState()->type(), State::STATES::ACTIVE);

	controller->pausePomidoro();
	QThread::msleep(50);
	QCOMPARE(pomidoro->getState()->type(), State::STATES::PAUSED);

	pomidoro->slotStart();
	QThread::msleep(50);
	QCOMPARE(pomidoro->getState()->type(), State::STATES::ACTIVE);

	controller->stopPomidoro();
	QThread::msleep(50);
	QCOMPARE(pomidoro->getState()->type(), State::STATES::INACTIVE);

	controller->stop();

	delete pomidoro;
	State::clearLog();
}

void test::test_main_logic2()
{
	ThreadController* c = new ThreadController;

	Pomidoro* pomidoro = c->pomidoro();
	QCOMPARE(pomidoro->getState()->type(), State::STATES::INACTIVE);

	pomidoro->setReps(1);
	pomidoro->setDurations(0, 0, 0);

	c->run();

	c->startPomidoro();

	c->stop();

	QCOMPARE(pomidoro->getState()->type(), State::STATES::INACTIVE);

	QString expected("INACTIVE::start()"
		"->ACTIVE::timerElapsed()" //1 pomidoro
		"->SHORT_REST::timerElapsed()"
		"->ACTIVE::timerElapsed()" //2
		"->SHORT_REST::timerElapsed()"
		"->ACTIVE::timerElapsed()" //3
		"->SHORT_REST::timerElapsed()"
		"->ACTIVE::timerElapsed()" //4
	);

	QCOMPARE(State::getLog(), expected);

	delete pomidoro;
	State::clearLog();
}

void test::test_main_logic3()
{
	ThreadController* c = new ThreadController;

	Pomidoro* pomidoro = c->pomidoro();
	QCOMPARE(pomidoro->getState()->type(), State::STATES::INACTIVE);

	pomidoro->setReps(2);
	pomidoro->setDurations(0, 0, 0);
	pomidoro->setIsContinuousWork(true);

	c->run();

	c->startPomidoro();

	QString expected("INACTIVE::start()"
		"->ACTIVE::timerElapsed()" //1 pomidoro
		"->SHORT_REST::timerElapsed()"
		"->ACTIVE::timerElapsed()" //2
		"->SHORT_REST::timerElapsed()"
		"->ACTIVE::timerElapsed()" //3
		"->SHORT_REST::timerElapsed()"
		"->ACTIVE::timerElapsed()" //4
		"->LONG_REST::timerElapsed()"
		"->ACTIVE::timerElapsed()" //1
		"->SHORT_REST::timerElapsed()"
		"->ACTIVE::timerElapsed()" //2
		"->SHORT_REST::timerElapsed()"
		"->ACTIVE::timerElapsed()" //3
		"->SHORT_REST::timerElapsed()"
		"->ACTIVE::timerElapsed()" //4
	);

	c->stop();

	QCOMPARE(pomidoro->getState()->type(), State::STATES::INACTIVE);

	QCOMPARE(State::getLog(), expected);

	delete pomidoro;
	State::clearLog();
}

void test::test_main_logic4()
{
	Pomidoro* p = new Pomidoro;

	p->setReps(1);
	p->setDurations(1, 1, 1);

	p->slotStart();

	p->setNewState(p->getShortRestState());
	p->slotPause();
	QCOMPARE(p->getState()->type(), State::STATES::PAUSED);
	p->slotStart();
	//Pomidoro should return to the state, on which it was paused
	QCOMPARE(p->getState()->type(), State::STATES::SHORT_REST);

	p->setNewState(p->getLongRestState());
	p->slotPause();
	QCOMPARE(p->getState()->type(), State::STATES::PAUSED);
	p->slotStart();
	//Pomidoro should return to the state, on which it was paused
	QCOMPARE(p->getState()->type(), State::STATES::LONG_REST);

	State::clearLog();
}

void test::test_data_saving_restoring()
{
	Pomidoro* p = new Pomidoro;

	p->setDurations(44, 22, 33);
	p->setReps(77);

	p->saver_->saveData();

	//clear parameters to check restoring :)
	p->setDurations(0, 0, 0);
	p->setReps(0);

	p->saver_->restoreData();

	QCOMPARE(p->configs()->work_, 44);
	QCOMPARE(p->configs()->sh_rest_, 22);
	QCOMPARE(p->configs()->l_rest_, 33);
	QCOMPARE(p->configs()->reps_, 77);

	delete p;
}

void test::test_formatTimerRemainingToString()
{
	QString expected = "20:00";
	QString actual = Utility::formatTimerRemainingToString(20 * 60 * 1000);
	QCOMPARE(actual, expected);

	expected = "20:01";
	actual = Utility::formatTimerRemainingToString((20 * 60 + 1) * 1000);
	QCOMPARE(actual, expected);

	expected = "19:59";
	actual = Utility::formatTimerRemainingToString((19 * 60 + 59) * 1000);
	QCOMPARE(actual, expected);

	expected = "00:00";
	actual = Utility::formatTimerRemainingToString(0);
	QCOMPARE(actual, expected);
}

QTEST_MAIN(test)

#include "tst_test.moc"
