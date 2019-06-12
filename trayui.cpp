#include "trayui.h"

#include "utility.h"
#include "pomidoro.h"

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>

TrayUI::TrayUI()
	:
	pomidoro(new Pomidoro(this)),
	tray(new QSystemTrayIcon),
	menu(new QMenu),
	display(new QAction(menu)),
	rounds(new QAction(menu)),
	start(new QAction("Start", menu)),
	reset(new QAction("Reset timer", menu)),
	stop(new QAction("Stop", menu)),
	version(new QAction(Utility::VERSION, menu))
{
	display->setText(QString("%1:00").arg(pomidoro->getWorkDuration()));
	menu->addAction(display);
	menu->addAction(rounds);
	menu->addAction(start);
	menu->addAction(reset);
	menu->addAction(stop);
	menu->addAction("Settings", this, SLOT(slotOpenSettings()));
	menu->addAction(version);
	menu->addAction("Exit", qApp, SLOT(quit()));

	tray->setContextMenu(menu);
	tray->show();

}

void TrayUI::slotStart()
{

}

void TrayUI::slotPause()
{

}

void TrayUI::slotReset()
{

}

void TrayUI::slotStop()
{

}

void TrayUI::slotTimerElapsed()
{

}

void TrayUI::slotOpenSettings()
{

}
