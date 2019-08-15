#include "pomidoro.h"
#include "concretestates.h"
#include "trayui.h"
#include "datasaver.h"

#include <QTimer>

Pomidoro::Pomidoro(QObject* parent, TrayUI* /*ui*/)
	: QObject(parent),
		StatesHolder(this),
		configs_(new ConfigParams),
		saver_(new DataSaver(configs_))
{
	State::setParams(configs_);

	isRunning_ = false;

	qApp->setQuitOnLastWindowClosed(false);
}

Pomidoro::Pomidoro(const Pomidoro& other)
	: QObject(other.parent()), StatesHolder(this)
{
	//TODO: add realisation
}

Pomidoro::~Pomidoro()
{
	delete timer_;
}

int Pomidoro::getWorkDuration() const
{
	return configs_->work_;
}

int Pomidoro::getRestDuration() const
{
	return configs_->sh_rest_;
}

int Pomidoro::getLongRestDuration() const
{
	return configs_->l_rest_;
}

int Pomidoro::getReps() const
{
	return configs_->reps_;
}

void Pomidoro::setDurations(int work, int rest, int long_rest)
{
	configs_->work_ = work;

	configs_->sh_rest_ = rest;

	configs_->l_rest_ = long_rest;
}

void Pomidoro::setWorkDuration(int min)
{
	configs_->work_ = min;
}

void Pomidoro::setShortRestDuration(int min)
{
	configs_->sh_rest_ = min;
}

void Pomidoro::setLongRestDuration(int min)
{
	configs_->l_rest_ = min;
}

void Pomidoro::setReps(int value)
{
	configs_->reps_ = value;
}

void Pomidoro::slotStart()
{
	isRunning_ = true;

	state_->doLog("start()");

	state_->start();

	emit active();
}

void Pomidoro::slotPause()
{
	state_->doLog("pause()");

	//need to save previous state,
	//because the PAUSED state should to know
	//on which state need to switch on
	//after slotStart() was invoked
	auto p = dynamic_cast<Paused*>(pausedState);
	p->previous = state_->type();

	state_->pause();
}

void Pomidoro::slotStop()
{
	timer_->stop();

	state_->stop();

	isRunning_ = false;

	emit inactive();
}

void Pomidoro::slotReset()
{
	state_->reset();
}

void Pomidoro::slotStartTimer(int min)
{
	initTimerIfNot();

	timer_->setSingleShot(true);
	timer_->start(min * 1000 * 60);
}

void Pomidoro::slotTimeOut()
{
	state_->doLog("timerElapsed()");

	//need to emit a signal for UI to set rest icon,
	//if we switch on SHORT or LONG REST state
	//for it, check if current state is ACTIVE
	bool isWorkState = state_->type() == State::STATES::ACTIVE;

	if(isWorkState) emit rest();

	state_->timerElapsed();

	if(configs_->total_ >= configs_->reps_)
	{
		isRunning_ = false;

		emit inactive();
	}
}

void Pomidoro::initTimerIfNot()
{
	if(!timer_)
	{
		timer_ = new QTimer;
		connect(timer_, SIGNAL(timeout()), SLOT(slotTimeOut()));
	}
}

int Pomidoro::getRounds() const
{
	return configs_->rounds_;
}

ConfigParams* Pomidoro::configs()
{
	return configs_;
}

int Pomidoro::getTotal() const
{
	return configs_->total_;
}

bool Pomidoro::isRunning()
{
	return isRunning_.load();
}

void Pomidoro::setIsContinuousWork(bool value)
{
	configs_->isContinuousWork = value;
}

int Pomidoro::getTimerRemainingTime()
{
	if(timer_ && timer_->isActive())
		return timer_->remainingTime();

	//cause QTimer::remainingTime() returns milliseconds
	//need to convert to milliseconds (we store minutes)
	return configs_->work_ * 60 * 1000;
}

/*
void Pomidoro::slotStart()
{
	state->start();

//	if(start->text() == "Start")
//	{
//		time->setHMS(0, workDuration, 0);
//		start->setText("Pause");
//		timer->start(1000);
//		qDebug() << "START";
//	}
//	else if(start->text() == "Pause")
//	{
//		start->setText("Continue");
//		timer->stop();
//		qDebug() << "PAUSE";
//	}
//	else if(start->text() == "Continue")
//	{
//		start->setText("Pause");
//		timer->start(1000);
//		qDebug() << "CONTINUE";
//	}

//	tray->setIcon(QIcon(":/Icons/red.png"));

}


void Pomidoro::slotPause()
{
	state->pause();
}

void Pomidoro::slotReset()
{

//	switch(type)
//	{
//		case WORK:
//			time->setHMS(0, workDuration, 0);
//			break;

//		case SHORTREST:
//			time->setHMS(0, shortRestDuration, 0);
//			break;

//		case LONGREST:
//			time->setHMS(0, longRestDuration, 0);
//			break;
//	}

//	updateInfo();
}

void Pomidoro::slotStop()
{
	state->stop();

//	qDebug() << "STOP";
//	timer->stop();
//	type = WORK;
//	time->setHMS(0, workDuration, 0);
//	round = 0;
//	updateInfo();
//	start->setText("Start");
//	tray->setIcon(QIcon(":/Icons/gray.png"));
	}

	void Pomidoro::slotUpdate()
	{
//	if(time->minute() > 0 || time->second() > 0)
//	{
//		*time = time->addSecs(-1);
//	}
//	else
//	{
//		player->play();

//		switch(type)
//		{

//			case WORK:
//				if(++round % reps != 0)
//				{
//					type = SHORTREST;
//					time->setHMS(0, shortRestDuration, 0);
//					tray->showMessage("Pomidoro timer", "Have a short break!", QSystemTrayIcon::Information, 3000);
//					qDebug() << "short rest launched after work";
//				}
//				else
//				{
//					++total;

//					type = LONGREST;
//					tray->showMessage("Pomidoro timer", "Have a long break!", QSystemTrayIcon::Information, 3000);

//					if(showAgainDialog)
//					{
//						RequestDialog* prdialog = new RequestDialog(&showAgainDialog);
//						turnLongRest = prdialog->exec();
//						delete prdialog;
//					}

//					if(turnLongRest)
//					{
//						qDebug() << "long rest launched after work";
//						time->setHMS(0, longRestDuration, 0);
//					}
//					else
//					{
//						qDebug() << "pomidoro stopped";
//						//if user don't want to have a long rest
//						//set type the WORK
//						type = WORK;
//						slotStop();
//					}
//				}

//				tray->setIcon(QIcon(":/Icons/green.png"));
//				break;

//			default:
//				type = WORK;
//				time->setHMS(0, workDuration, 0);
//				tray->showMessage("Pomidoro timer", "Continue your work!", QSystemTrayIcon::Information, 3000);
//				tray->setIcon(QIcon(":/Icons/red.png"));
//				qDebug() << "new round launched after short rest";
//		}
//	}

//	updateInfo();
//	qDebug() << time->toString("mm:ss");

}

void Pomidoro::slotTimerElapsed()
{
	state->timerElapsed();
}

void Pomidoro::slotOpenSettings()
{
	qDebug() << workDuration;
	SettingsDialog* pdialog = new SettingsDialog(&workDuration,
		&shortRestDuration,
		&longRestDuration,
		&reps,
		&turnLongRest,
		&showAgainDialog);

	if(pdialog->exec())
		slotStop();

	qDebug() << workDuration;
}
*/

