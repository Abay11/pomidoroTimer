#ifndef TRAYUI_H
#define TRAYUI_H

#include <QObject>

class Pomidoro;

class QSystemTrayIcon;
class QMenu;
class QAction;

class TrayUI : public QObject
{

	Q_OBJECT

public:
	TrayUI();

private slots:
	void slotStart();
	void slotPause();
	void slotReset();
	void slotStop();
	void slotTimerElapsed();
	void slotOpenSettings();

private:
	Pomidoro* pomidoro;


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
