#include "threadcontroller.h"
#include "pomidoro.h"

#include <QThread>

ThreadController::ThreadController(Pomidoro* instance, QObject* parent) : QObject(parent),
	thread_(new QThread)
{
	pomidoro_ = instance ? instance : new Pomidoro;

	qRegisterMetaType(pomidoro_);

	connect(this, SIGNAL(cmdStart()), pomidoro_, SLOT(slotStart()));

	connect(this, SIGNAL(cmdStop()), pomidoro_, SLOT(slotStop()));

	connect(this, SIGNAL(cmdPause()), pomidoro_, SLOT(slotPause()));

	connect(this, SIGNAL(cmdReset()), pomidoro_, SLOT(slotReset()));

	connect(this, SIGNAL(cmdSkip()), pomidoro_, SLOT(slotSkip()));

	connect(this, SIGNAL(cmdSaveConfigs()), pomidoro_, SLOT(slotSaveConfigs()));
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

void ThreadController::callSaveConfigs()
{
	emit cmdSaveConfigs();
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

void ThreadController::resetPomidoro()
{
	emit cmdReset();
}

void ThreadController::skipPomidoro()
{
	emit cmdSkip();
}

