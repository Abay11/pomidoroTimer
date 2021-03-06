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
		tray_(new QSystemTrayIcon),
		menu_(new QMenu),
		timer_data_(new QAction(menu_)),
		rounds_(new QAction(menu_)),
		start_(new QAction("Start", menu_)),
		pause_(new QAction("Pause", menu_)),
		reset_(new QAction("Reset timer", menu_)),
		skip_(new QAction("Skip timer", menu_)),
		stop_(new QAction("Stop", menu_)),
		about_(new QAction("About", menu_))
{
	pomidoro_ = controller_->pomidoro();
	configs_ = pomidoro_->configs_;

	loadConfigs();

	menu_->addAction(timer_data_);
	menu_->addAction(rounds_);
	menu_->addAction(start_);
	menu_->addAction(pause_);
	menu_->addAction(reset_);
	menu_->addAction(skip_);
	menu_->addAction(stop_);
	menu_->addAction("Settings", this, SLOT(slotOpenSettings()));
	menu_->addAction(about_);
	menu_->addAction("Exit", qApp, SLOT(quit()));

	connect(start_, SIGNAL(triggered()), controller_, SLOT(startPomidoro()));
	connect(pause_, SIGNAL(triggered()), controller_, SLOT(pausePomidoro()));
	connect(reset_, SIGNAL(triggered()), controller_, SLOT(resetPomidoro()));
	connect(skip_, SIGNAL(triggered()), controller_, SLOT(skipPomidoro()));
	connect(stop_, SIGNAL(triggered()), controller_, SLOT(stopPomidoro()));
	connect(about_, SIGNAL(triggered()), this, SLOT(slot_show_about()));

	connect(tray_, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(slotTrayActivated()));

	connect(timer_updater_, SIGNAL(timeout()), SLOT(slot_timer_updater()));

	connect(pomidoro_, SIGNAL(active()), SLOT(slot_set_active_icon()));
	connect(pomidoro_, SIGNAL(pause()), SLOT(slot_set_pause_icon()));
	connect(pomidoro_, SIGNAL(inactive()), SLOT(slot_set_inactive_icon()));
	connect(pomidoro_, SIGNAL(rest()), SLOT(slot_set_rest_icon()));

	slot_set_inactive_icon();
	tray_->setContextMenu(menu_);
	tray_->show();
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
	if(!tray_->contextMenu()->isVisible())
	{
		timer_updater_->stop();
		return;
	}

	//do update info periodically during context menu is visible
	timer_data_->setText(Utility::formatTimerRemainingToString(pomidoro_->getTimerRemainingTime()));

	//TODO: get more efficient way (no need to update this component every time)
	rounds_->setText(QString("%1/%2. Total: %3")
		.arg(configs_->rounds_)
		.arg(configs_->reps_)
		.arg(configs_->total_));
}

void TrayUI::slot_set_active_icon()
{
	tray_->setIcon(QIcon(":/Icons/red.svg"));

	tray_->showMessage("Pomidoro timer", "It's time to work!", QSystemTrayIcon::Information, NOTIFY_DELAY);
}

void TrayUI::slot_set_pause_icon()
{
	tray_->setIcon(QIcon(":/Icons/yellow.svg"));
}

void TrayUI::slot_set_rest_icon()
{
	tray_->setIcon(QIcon(":/Icons/green.svg"));

	tray_->showMessage("Pomidoro timer", "Have a rest!", QSystemTrayIcon::Information, NOTIFY_DELAY);
}

void TrayUI::slot_set_inactive_icon()
{
	tray_->setIcon(QIcon(":/Icons/gray.svg"));
}

#include <QMessageBox>
void TrayUI::slot_show_about()
{
	QMessageBox msg_box;
	msg_box.setWindowTitle("About");

	QString text;
	QTextStream tx(&text);

	tx << "Free Pomidoro Timer application (v." << Utility::VERSION << "), 2018-2019" << endl;
	tx << "Alim Abay (Github: @abay11)" << endl;

	msg_box.setText(text);
	msg_box.exec();
}

void TrayUI::accept_changes()
{
	qDebug() << "Saving updated data";

	controller_->stopPomidoro();

	controller_->callSaveConfigs();

	loadConfigs();
}

void TrayUI::loadConfigs()
{
	timer_data_->setText(QString("%1:00").arg(configs_->work_));

	rounds_->setText(QString("%1/%2. Total: %3")
		.arg(configs_->rounds_)
		.arg(configs_->reps_)
		.arg(configs_->total_));
}
