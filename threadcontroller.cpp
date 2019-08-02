#include "threadcontroller.h"
#include "pomidoro.h"

#include <QThread>

ThreadController::ThreadController(Pomidoro* instance, QObject* parent) : QObject(parent),
	thread_(new QThread)
{
	qRegisterMetaType(this);

	pomidoro_ = instance ? instance : new Pomidoro;

	qRegisterMetaType(pomidoro_);

	connect(pomidoro_, SIGNAL(eventloopInited()), SLOT(slotSetConnections()));

	connect(this, SIGNAL(cmdStart()), pomidoro_, SLOT(slotStart()));

	connect(this, SIGNAL(cmdStop()), pomidoro_, SLOT(slotStop()));

	connect(this, SIGNAL(cmdPause()), pomidoro_, SLOT(slotPause()));
}

ThreadController::ThreadController(const ThreadController& /*other*/)
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

void ThreadController::startPomidoro()
{
	emit cmdStart();
}

void ThreadController::stopPomidoro()
{
	emit cmdStop();
}

void ThreadController::pausePomidoro()
{
	quitLoop();

	emit cmdPause();
}

void ThreadController::quitLoop()
{
	emit cmdQuitLoop();
}

void ThreadController::run()
{
	pomidoro_->moveToThread(thread_);

	thread_->start();
}

void ThreadController::stop()
{
	if(pomidoro_->isRunning_)
		pomidoro_->slotStop();

	//		emit quitLoop();

	thread_->quit();

	thread_->wait();
}

void ThreadController::slotSetConnections()
{
	connect(this, SIGNAL(cmdQuitLoop()), pomidoro_->loop, SLOT(quit()), Qt::ConnectionType::DirectConnection);
}
