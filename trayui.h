#ifndef TRAYUI_H
#define TRAYUI_H

#include <QObject>
#include <QSystemTrayIcon>

class Pomidoro;
class ConfigParams;
class ThreadController;

class QSystemTrayIcon;
class QMenu;
class QAction;
class QTimer;

class TrayUI : public QObject
{

	Q_OBJECT

public:
	TrayUI(QObject* parent = nullptr);

private slots:
	void slotOpenSettings();

	void slotTrayActivated();

	void slot_timer_updater();

	void slot_set_active_icon();

	void slot_set_pause_icon();

	void slot_set_rest_icon();

	void slot_set_inactive_icon();

private:
	void accept_changes();

	void loadConfigs();

private:
	Pomidoro* pomidoro_;
	ConfigParams* configs_;
	ThreadController* controller_;

	QTimer* timer_updater_;

	QSystemTrayIcon* tray_;
	QMenu* menu_;
	QAction* timer_data_;
	QAction* rounds_;
	QAction* start_;
	QAction* pause_;
	QAction* reset_;
	QAction* skip_;
	QAction* stop_;
	QAction* version_;
};

#endif // TRAYUI_H
