#ifndef TRAYUI_H
#define TRAYUI_H

#include <QObject>
#include <QSystemTrayIcon>

class Pomidoro;
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

	void slot_set_rounds_info();

	void slot_set_active_icon();

	void slot_set_rest_icon();

	void slot_set_inactive_icon();

private:
	void accept_changes();

private:
	Pomidoro* pomidoro_;
	ThreadController* controller_;

	QTimer* timer_updater_;

	QSystemTrayIcon* tray;
	QMenu* menu;
	QAction* display;
	QAction* rounds;
	QAction* start;
	QAction* reset;
	QAction* stop;
	QAction* version;
};

#endif // TRAYUI_H
