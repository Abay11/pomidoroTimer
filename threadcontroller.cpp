#include "threadcontroller.h"

#include <QThread>

#include "pomidoro.h"

ThreadController::ThreadController(QObject* parent) : QObject(parent),
	thread_(new QThread)
{
}

void ThreadController::initPomidoro()
{
	pomidoro_ = new Pomidoro;

	pomidoro_->moveToThread(thread_);
}
