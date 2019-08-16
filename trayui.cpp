#include "trayui.h"

#include "utility.h"
#include "pomidoro.h"
#include "datasaver.h"

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
		timer_data(new QAction(menu)),
		rounds(new QAction(menu)),
		start(new QAction("Start", menu)),
		reset(new QAction("Reset timer", menu)),
		stop(new QAction("Stop", menu)),
		version(new QAction(Utility::VERSION, menu))
{
	pomidoro_ = controller_->pomidoro();
	configs_ = pomidoro_->configs_;

	loadConfigs();

	menu->addAction(timer_data);
	menu->addAction(rounds);
	menu->addAction(start);
	menu->addAction(reset);
	menu->addAction(stop);
	menu->addAction("Settings", this, SLOT(slotOpenSettings()));
	menu->addAction(version);
	menu->addAction("Exit", qApp, SLOT(quit()));

	connect(start, SIGNAL(triggered()), controller_, SLOT(startPomidoro()));
	//k	connect(reset, SIGNAL(triggered()), controller_, SLOT(controller_->resetPomidoro()));
	connect(stop, SIGNAL(triggered()), controller_, SLOT(stopPomidoro()));

	connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(slotTrayActivated()));

	connect(timer_updater_, SIGNAL(timeout()), SLOT(slot_timer_updater()));

	connect(pomidoro_, SIGNAL(active()), SLOT(slot_set_active_icon()));
	connect(pomidoro_, SIGNAL(inactive()), SLOT(slot_set_inactive_icon()));
	connect(pomidoro_, SIGNAL(rest()), SLOT(slot_set_rest_icon()));

	slot_set_inactive_icon();
	tray->setContextMenu(menu);
	tray->show();
}

void TrayUI::slotOpenSettings()
{
	static SettingsDialog* pdialog = new SettingsDialog(pomidoro_->configs());

	if(pdialog->exec())
		accept_changes();
}

void TrayUI::slotTrayActivated()
{
	//set 100 ms for updating to get more
	//comfortable user expirience
	timer_updater_->start(100);
}

void TrayUI::slot_timer_updater()
{
	if(!tray->contextMenu()->isVisible())
	{
		timer_updater_->stop();
		return;
	}

	//do update info periodically during context menu is visible
	timer_data->setText(Utility::formatTimerRemainingToString(pomidoro_->getTimerRemainingTime()));

	//TODO: get more efficient way (no need to update this component every time)
	rounds->setText(QString("%1/%2. Total: %3")
		.arg(configs_->rounds_)
		.arg(configs_->reps_)
		.arg(configs_->total_));
}

void TrayUI::slot_set_active_icon()
{
	tray->setIcon(QIcon(":/Icons/red.png"));
}

void TrayUI::slot_set_rest_icon()
{
	tray->setIcon(QIcon(":/Icons/green.png"));
}

void TrayUI::slot_set_inactive_icon()
{
	tray->setIcon(QIcon(":/Icons/gray.png"));
}

void TrayUI::accept_changes()
{
	qDebug() << "Saving updated data";

	controller_->stopPomidoro();

	pomidoro_->saver_->saveData();

	loadConfigs();
}

void TrayUI::loadConfigs()
{
	timer_data->setText(QString("%1:00").arg(configs_->work_));

	rounds->setText(QString("%1/%2. Total: %3")
		.arg(configs_->rounds_)
		.arg(configs_->reps_)
		.arg(configs_->total_));
}
