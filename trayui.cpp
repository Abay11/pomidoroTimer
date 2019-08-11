#include "trayui.h"

#include "utility.h"
#include "pomidoro.h"

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QTimer>

TrayUI::TrayUI(QObject* parent)
	: QObject(parent),
		controller_(new ThreadController),
		timer_updater_(new QTimer),
		tray(new QSystemTrayIcon),
		menu(new QMenu),
		display(new QAction(menu)),
		rounds(new QAction(menu)),
		start(new QAction("Start", menu)),
		reset(new QAction("Reset timer", menu)),
		stop(new QAction("Stop", menu)),
		version(new QAction(Utility::VERSION, menu))
{
	pomidoro_ = controller_->pomidoro();

	display->setText(QString("%1:00").arg(pomidoro_->getWorkDuration()));
	menu->addAction(display);
	menu->addAction(rounds);
	menu->addAction(start);
	menu->addAction(reset);
	menu->addAction(stop);
	menu->addAction("Settings", this, SLOT(slotOpenSettings()));
	menu->addAction(version);
	menu->addAction("Exit", qApp, SLOT(quit()));

	slot_set_rounds_info();

	connect(start, SIGNAL(triggered()), controller_, SLOT(controller_->startPomidoro()));
	connect(reset, SIGNAL(triggered()), controller_, SLOT(controller_->resetPomidoro()));
	connect(stop, SIGNAL(triggered()), controller_, SLOT(controller_->stopPomidoro()));

	connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(slotTrayActivated()));

	connect(timer_updater_, SIGNAL(timeout()), SLOT(slot_timer_updater()));

	tray->setIcon(QIcon(":/Icons/gray.png"));
	tray->setContextMenu(menu);
	tray->show();
}

void TrayUI::slotOpenSettings()
{
}

void TrayUI::slotTrayActivated()
{
	timer_updater_->start(1000);
}

void TrayUI::slot_timer_updater()
{
	if(!tray->contextMenu()->isVisible())
	{
		timer_updater_->stop();
		return;
	}

	//do update info every 1 sec
	//	display->setText(Utility::formatTimerRemainingToString(pomidoro_->getTimerRemainingTime()));
}

void TrayUI::slot_set_rounds_info()
{
	rounds->setText(QString("%1/%2. Total: %3")
		.arg(pomidoro_->getRounds())
		.arg(pomidoro_->getReps())
		.arg(pomidoro_->getTotal()));
}
