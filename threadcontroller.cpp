#include "threadcontroller.h"

#include <QThread>

#include "pomidoro.h"

ThreadController::ThreadController(QObject* parent) : QObject(parent),
	thread_(new QThread)
{
}

ThreadController::~ThreadController()
{
	delete pomidoro_;

	delete thread_;
}

void ThreadController::run()
{
	pomidoro_ = new Pomidoro;

	pomidoro_->moveToThread(thread_);

	thread_->start();
}

void ThreadController::stop()
{
	thread_->quit();

	thread_->wait();
}

Pomidoro* ThreadController::pomidoro() const
{
	return pomidoro_;
}
