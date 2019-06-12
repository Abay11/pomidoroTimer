#ifndef TOMATO_H
#define TOMATO_H

class TrayUI;

#include "settingsdialog.h"
#include "requestdialog.h"
#include "concretestates.h"


class Pomidoro: public QObject
{
	Q_OBJECT
public:
	Pomidoro(TrayUI* ui_instance);

	~Pomidoro();

	int getWorkDuration() const;

	void setWorkDuration(int value);

private:
	TrayUI* ui_;
	QTimer* timer;
	QTime* time;
	//	QSound* player;

	int	workDuration = 20;
	int shortRestDuration = 5;
	int longRestDuration  = 15;
	int reps = 1;
	int round = 0;
	int total = 0;

	bool turnLongRest = false;
	bool showAgainDialog = true;

	enum TYPE {WORK = 0, SHORTREST, LONGREST} type = WORK;

	State* inactiveState;
	State* activeState;
	State* pausedState;
	State* shortRestState;
	State* longRestState;
	State* state;

	void updateInfo();
	void saveSettings();
	void restoreSettings();
};

#endif // TOMATO_H
