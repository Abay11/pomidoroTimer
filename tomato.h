#ifndef TOMATO_H
#define TOMATO_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <QApplication>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QFile>
#include <QDataStream>
#include <QSound>

#include "settingsdialog.h"
#include "requestdialog.h"

const QString VERSION = "v1.3";

class Tomato: public QObject
{
	Q_OBJECT
private:
	QSystemTrayIcon* tray;
	QMenu* menu;
	QAction* display;
	QAction* rounds;
	QAction* start;
	QAction* reset;
	QAction* stop;
	QAction* version;
	QTimer* timer;
	QTime* time;
	QSound* player;


	int	workDuration = 20;
	int shortRestDuration = 5;
	int longRestDuration  = 15;
	int reps = 1;
	int round = 0;
	int total = 0;

	bool turnLongRest = false;
	bool showAgainDialog = true;

	enum TYPE {WORK = 0, SHORTREST, LONGREST} type = WORK;

	void updateInfo();
	void saveSettings();
	void restoreSettings();

public:
	Tomato(QObject* p = nullptr);
	~Tomato();

private slots:
	void slotStart();
	void slotPause();
	void slotReset();
	void slotStop();
	void slotUpdate();

	void slotOpenSettings();
};

#endif // TOMATO_H
