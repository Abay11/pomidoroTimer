#include "threadcontroller.h"
#include "pomidoro.h"

#include <QThread>

ThreadController::ThreadController(Pomidoro* instance, QObject* parent) : QObject(parent),
	thread_(new QThread)
{
	qRegisterMetaType(this);

	pomidoro_ = instance ? instance : new Pomidoro;

	qRegisterMetaType(pomidoro_);

	connect(this, SIGNAL(cmdStart()), pomidoro_, SLOT(slotStart()));

	connect(this, SIGNAL(cmdStop()), pomidoro_, SLOT(slotStop()));

	connect(this, SIGNAL(cmdPause()), pomidoro_, SLOT(slotPause()));

	connect(this, SIGNAL(cmdSkip()), pomidoro_, SLOT(slotSkip()));
}

ThreadController::ThreadController(const ThreadController& other) : QObject(other.parent())
{
	//TODO: add realisation
}

ThreadController::~ThreadController()
{
	delete pomidoro_;

	delete thread_;
}

Pomidoro* ThreadController::pomidoro() const
{
	return pomidoro_;
}

void ThreadController::run()
{
	pomidoro_->moveToThread(thread_);

	thread_->start();
}

void ThreadController::stop()
{
	QEventLoop* l = new QEventLoop;
	Q_ASSERT(connect(pomidoro_, SIGNAL(inactive()), l, SLOT(quit())));

	if(pomidoro_->isRunning())
		l->exec();

	thread_->quit();

	thread_->wait();

	delete l;
}

void ThreadController::startPomidoro()
{
	//should wait until Pomidoro will started
	//otherwise it immediately will finish
	//despite the QEventLoop in stop() -
	//Pomidoro not get in time changing isRunning flag
	QEventLoop* l = new QEventLoop;

	connect(pomidoro_, SIGNAL(active()), l, SLOT(quit()));

	emit cmdStart();

	l->exec();
}

void ThreadController::stopPomidoro()
{
	emit cmdStop();
}

void ThreadController::pausePomidoro()
{
	emit cmdPause();
}

void ThreadController::skipPomidoro()
{
	emit cmdSkip();
}

