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
	emit cmdPause();
}

void ThreadController::run()
{
	pomidoro_->moveToThread(thread_);

	thread_->start();
}

void ThreadController::stop()
{
	QEventLoop* l = new QEventLoop;
	Q_ASSERT(connect(pomidoro_, SIGNAL(finished()), l, SLOT(quit())));

	if(pomidoro_->isRunning())
		l->exec();

	QThread::sleep(1);


	thread_->quit();

	thread_->wait();

	//	delete l;s
}
