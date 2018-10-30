#include "tomato.h"

void Tomato::updateDisplay()
{
 padisplay->setText(ptime->toString("mm:ss"));
}

Tomato::Tomato(QObject *p)
 :QObject(p)
 ,ptray(new QSystemTrayIcon(QIcon(":/Icons/gray.png"), this))
 ,pmenu(new QMenu)
 ,padisplay(new QAction(pmenu))
 ,pastart(new QAction("Start", pmenu))
 ,pastop(new QAction("Stop", pmenu))
 ,ptimer(new QTimer(this))
 ,ptime(new QTime)
{
 updateDisplay();
 padisplay->setText(QString("%1:00").arg(workDuration));
 pmenu->addAction(padisplay);
 pmenu->addAction(pastart);
 pmenu->addAction(pastop);
 pmenu->addAction("Exit", qApp, SLOT(quit()));

 ptray->setContextMenu(pmenu);
 ptray->show();

 connect(pastart, SIGNAL(triggered()), SLOT(slotStart()));
 connect(pastop, SIGNAL(triggered()), SLOT(slotStop()));
 connect(ptimer, SIGNAL(timeout()), SLOT(slotUpdate()));
}

void Tomato::slotStart()
{

 if(pastart->text()=="Start")
	{
	 ptime->setHMS(0, 0, 10);
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
}

void Tomato::slotStop()
{
 qDebug()<<"STOP";
 ptimer->stop();
 ptime->setHMS(0, 10, 0);
 updateDisplay();
 pastart->setText("Start");
}

void Tomato::slotUpdate()
{
 if(ptime->minute()>0 || ptime->second()>0)
	{
	 *ptime=ptime->addSecs(-1);
	}
 else
	{
	 switch (type) {

		case WORK:
			 if(++round%reps!=0)
				{
				 type=SHORTREST;
				 ptime->setHMS(0, 0, 5-1);
				 qDebug()<<"short rest launched after work";
				}
			 else
				{
				 type=LONGREST;
				 bool execreturn=false;
				 if(execreturn)
				 ptime->setHMS(0,0,15-1);
					else
				 slotStop();
				 qDebug()<<"long rest launched after work";
				}
		 break;

		case SHORTREST:
		 type=WORK;
		 ptime->setHMS(0,0,10-1);
		 qDebug()<<"new round launched after short rest";
		 break;

		case LONGREST:
		 type=WORK;
		 ptime->setHMS(0,0,10-1);
		 qDebug()<<"new pomidoro launched after long rest";
		 break;
		}
	}

 updateDisplay();
 qDebug()<<ptime->toString("mm:ss");
}
