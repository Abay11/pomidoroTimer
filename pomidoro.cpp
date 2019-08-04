#include "pomidoro.h"
#include "concretestates.h"
#include "trayui.h"

#include <QTimer>



Pomidoro::Pomidoro(QObject* parent, TrayUI* /*ui*/)
	: QObject(parent), StatesHolder(this)
{
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
	delete timer;
}

int Pomidoro::getWorkDuration() const
{
	return work_;
}

int Pomidoro::getRestDuration() const
{
	return sh_rest_;
}

int Pomidoro::getLongRestDuration() const
{
	return l_rest_;
}

int Pomidoro::getReps() const
{
	return reps_;
}

void Pomidoro::setDurations(int work, int rest, int long_rest)
{
	work_ = work;

	sh_rest_ = rest;

	l_rest_ = long_rest;
}

void Pomidoro::setWorkDuration(int min)
{
	work_ = min;
}

void Pomidoro::setShortRestDuration(int min)
{
	sh_rest_ = min;
}

void Pomidoro::setLongRestDuration(int min)
{
	l_rest_ = min;
}

void Pomidoro::setReps(int value)
{
	reps_ = value;
}

void Pomidoro::slotStart()
{
	isRunning_ = true;

	state_->doLog("start()");

	state_->start();
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
	timer->stop();

	state_->stop();

	isRunning_ = false;
}

void Pomidoro::slotReset()
{
	state_->reset();
}

void Pomidoro::slotStartTimer(int min)
{
	initTimerIfNot();

	timer->setSingleShot(true);
	timer->start(min * 1000 * 60);
}

void Pomidoro::slotTimeOut()
{
	state_->doLog("timerElapsed()");

	state_->timerElapsed();

	if(total_ >= reps_)
	{
		isRunning_ = false;

		emit finished();
	}
}

void Pomidoro::initTimerIfNot()
{
	if(!timer)
	{
		timer = new QTimer;
		connect(timer, SIGNAL(timeout()), SLOT(slotTimeOut()));
	}
}

bool Pomidoro::isRunning()
{
	return isRunning_.load();
}

void Pomidoro::setIsContinuousWork(bool value)
{
	isContinuousWork = value;
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

