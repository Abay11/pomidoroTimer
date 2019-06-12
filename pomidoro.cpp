#include "pomidoro.h"

#include "trayui.h"

int Pomidoro::getWorkDuration() const
{
	return workDuration;
}

void Pomidoro::setWorkDuration(int value)
{
	workDuration = value;
}

void Pomidoro::updateInfo()
{
	//	ui_.
	//	display->setText(time->toString("mm:ss"));
	//	tray->setToolTip(time->toString("mm:ss"));
	//	rounds->setText(QString("%1/%2. Total: %3").arg(round % reps).arg(reps).arg(total));
}

void Pomidoro::saveSettings()
{
	//	QFile file("data.bin");

	//	if(file.open(QIODevice::WriteOnly))
	//	{
	//		QDataStream in(&file);
	//		in << workDuration
	//			<< shortRestDuration
	//			<< longRestDuration
	//			<< reps
	//			<< turnLongRest
	//			<< showAgainDialog;
	//	}
}

void Pomidoro::restoreSettings()
{
	//	QFile file("data.bin");

	//	if(file.open(QIODevice::ReadOnly))
	//	{
	//		QDataStream out(&file);
	//		out >> workDuration >> shortRestDuration >> longRestDuration
	//			>> reps >> turnLongRest >> showAgainDialog;
	//	}
}

Pomidoro::Pomidoro(TrayUI* ui)
	: QObject(ui)
	, ui_(ui)
	, inactiveState(new Inactive(reps, this))
	, activeState(new Active(reps, this))
	, pausedState(new Paused(reps, this))
	, shortRestState(new ShortRest(reps, this))
	, longRestState(new LongRest(reps, this))
	, state(inactiveState)
{
	restoreSettings();
	updateInfo();

	//	connect(start, SIGNAL(triggered()), SLOT(slotStart()));
	//	connect(reset, SIGNAL(triggered()), SLOT(slotReset()));
	//	connect(stop, SIGNAL(triggered()), SLOT(slotStop()));
	//	connect(timer, SIGNAL(timeout()), SLOT(slotUpdate()));

	qApp->setQuitOnLastWindowClosed(false);
}

Pomidoro::~Pomidoro()
{
	saveSettings();

	delete inactiveState;
	delete activeState;
	delete pausedState;
	delete shortRestState;
	delete longRestState;
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

