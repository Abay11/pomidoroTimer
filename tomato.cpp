#include "tomato.h"

void Tomato::updateInfo()
{
 padisplay->setText(ptime->toString("mm:ss"));
 parounds->setText(QString("%1/%2. Total: %3").arg(round%reps).arg(reps).arg(total));
}

void Tomato::saveSettings()
{
 QFile file("data.bin");
 if(file.open(QIODevice::WriteOnly))
	{
		 QDataStream in(&file);
		 in<<workDuration
			<<shortRestDuration
		 <<longRestDuration
		 <<reps
		 <<turnLongRest
		 <<showAgainDialog;
	}

}

void Tomato::restoreSettings()
{
 QFile file("data.bin");
 if(file.open(QIODevice::ReadOnly))
	{
		 QDataStream out(&file);
		 out>>workDuration>>shortRestDuration>>longRestDuration
			 >>reps>>turnLongRest>>showAgainDialog;
	}
}

Tomato::Tomato(QObject *p)
 :QObject(p)
 ,ptray(new QSystemTrayIcon(QIcon(":/Icons/gray.png"), this))
 ,pmenu(new QMenu)
 ,padisplay(new QAction(pmenu))
 ,parounds(new QAction(pmenu))
 ,pastart(new QAction("Start", pmenu))
 ,pareset(new QAction("Reset timer", pmenu))
 ,pastop(new QAction("Stop", pmenu))
 ,ptimer(new QTimer(this))
 ,ptime(new QTime)
 ,psound(new QSound(":/Sounds/birds.wav"))
{
 restoreSettings();
 updateInfo();

 padisplay->setText(QString("%1:00").arg(workDuration));
 pmenu->addAction(padisplay);
 pmenu->addAction(parounds);
 pmenu->addAction(pastart);
 pmenu->addAction(pareset);
 pmenu->addAction(pastop);
 pmenu->addAction("Settings", this, SLOT(slotOpenSettings()));
 pmenu->addAction("Exit", qApp, SLOT(quit()));

 ptray->setContextMenu(pmenu);
 ptray->show();

 connect(pastart, SIGNAL(triggered()), SLOT(slotStart()));
 connect(pareset, SIGNAL(triggered()), SLOT(slotReset()));
 connect(pastop, SIGNAL(triggered()), SLOT(slotStop()));
 connect(ptimer, SIGNAL(timeout()), SLOT(slotUpdate()));

 qApp->setQuitOnLastWindowClosed(false);
}

Tomato::~Tomato()
{
 saveSettings();
}

void Tomato::slotStart()
{
 if(pastart->text()=="Start")
	{
	 ptime->setHMS(0, workDuration, 0);
	 pastart->setText("Pause");
	 ptimer->start(1000);
	 qDebug()<<"START";
	}
 else if(pastart->text()=="Pause")
	{
	 pastart->setText("Continue");
	 ptimer->stop();
	 qDebug()<<"PAUSE";
	}
 else if(pastart->text()=="Continue")
	{
	 pastart->setText("Pause");
	 ptimer->start(1000);
	 qDebug()<<"CONTINUE";
	}
 ptray->setIcon(QIcon(":/Icons/red.png"));
}

void Tomato::slotReset()
{
 switch(type)
	{
	case WORK:
	 ptime->setHMS(0, workDuration, 0);
	 break;
	case SHORTREST:
	 ptime->setHMS(0, shortRestDuration, 0);
	 break;
	case LONGREST:
	 ptime->setHMS(0, longRestDuration, 0);
	 break;
	}

 updateInfo();
}

void Tomato::slotStop()
{
 qDebug()<<"STOP";
 ptimer->stop();
 ptime->setHMS(0, workDuration, 0);
 updateInfo();
 pastart->setText("Start");
 ptray->setIcon(QIcon(":/Icons/gray.png"));
}

void Tomato::slotUpdate()
{
 if(ptime->minute()>0 || ptime->second()>0)
	{
	 *ptime=ptime->addSecs(-1);
	}
 else
	{
	 psound->play();

	 switch (type) {

		case WORK:
			 if(++round%reps!=0)
				{
				 type=SHORTREST;
				 ptime->setHMS(0, shortRestDuration, 0);
				 ptray->showMessage("Pomidoro timer", "Have a short break!", QSystemTrayIcon::Information, 3000);
				 qDebug()<<"short rest launched after work";
				}
			 else
				{
				 ++total;

				 type=LONGREST;
				 ptray->showMessage("Pomidoro timer", "Have a long break!", QSystemTrayIcon::Information, 3000);

				 if(showAgainDialog)
					{
					RequestDialog *prdialog=new RequestDialog(&showAgainDialog);
					turnLongRest=prdialog->exec();
					delete prdialog;
					}

				 if(turnLongRest)
					{
					 qDebug()<<"long rest launched after work";
					 ptime->setHMS(0,longRestDuration,0);
					}
					else
					{
					 qDebug()<<"pomidoro stopped";
					 slotStop();
					}
				}
			 ptray->setIcon(QIcon(":/Icons/green.png"));
		 break;

		default:
		 type=WORK;
		 ptime->setHMS(0,workDuration,0);
		 ptray->showMessage("Pomidoro timer", "Continue your work!", QSystemTrayIcon::Information, 3000);
		 ptray->setIcon(QIcon(":/Icons/red.png"));
		 qDebug()<<"new round launched after short rest";

//		case SHORTREST:
//		 type=WORK;
//		 ptime->setHMS(0,workDuration,0);
//		 ptray->showMessage("Pomidoro timer", "Continue your work!", QSystemTrayIcon::Information, 3000);
//		 ptray->setIcon(QIcon(":/Icons/red.png"));
//		 qDebug()<<"new round launched after short rest";
//		 break;

//		case LONGREST:
//		 type=WORK;
//		 ptime->setHMS(0,0,10-1);
//		 ptray->showMessage("Pomidoro timer", "Continue your work!", QSystemTrayIcon::Information, 3000);
//		 ptray->setIcon(QIcon(":/Icons/red.png"));
//		 qDebug()<<"new pomidoro launched after long rest";
//		 break;
		}
	}

 updateInfo();
 qDebug()<<ptime->toString("mm:ss");
}

void Tomato::slotOpenSettings()
{
 qDebug()<<workDuration;
 SettingsDialog *pdialog=new SettingsDialog(&workDuration,
																						&shortRestDuration,
																						&longRestDuration,
																						&reps,
																						&turnLongRest,
																						&showAgainDialog);

 if(pdialog->exec())
		slotStop();

 qDebug()<<workDuration;
}
