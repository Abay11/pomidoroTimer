#ifndef TOMATO_H
#define TOMATO_H


#include "settingsdialog.h"
#include "requestdialog.h"
#include "concretestates.h"

#include <QObject>

class TrayUI;
class State;

class QTimer;

class Pomidoro: public QObject
{
	Q_OBJECT
public:
	Pomidoro(TrayUI* ui_instance);

	~Pomidoro();

	int getWorkDuration() const;

	int getRestDuration() const;

	int getLongRestDuration() const;

	int getReps() const;

	void setDurations(int work, int rest, int long_rest);

	void setWorkDuration(int min);

	void setShortRestDuration(int min);

	void setLongRestDuration(int min);

	State* getState();

	void setReps(int value);

	State* getInactiveState();

	State* getActiveState();

	State* getPausedState();

	State* getShortRestState();

	State* getLongRestState();

	void setNewState(State* state);

	void startTimer(int min);

public slots:

	void slotStart();

	void slotPause();

	void slotStop();

	void slotReset();

private slots:

	void slotTimeOut();

signals:
	//	void

private:
	QTimer* timer;

	QTime* time;

	int	work_ = 20;
	int rest_ = 5;
	int long_rest_  = 15;
	int reps_ = 1;
	int rounds_ = 0;
	int total_ = 0;

	bool turnLongRest = false;
	bool showAgainDialog = true;

	enum TYPE {WORK = 0, SHORTREST, LONGREST} type = WORK;

	State* inactiveState;
	State* activeState;
	State* pausedState;
	State* shortRestState;
	State* longRestState;
	State* state_;

	void updateInfo();
	void saveSettings();
	void restoreSettings();
};

#endif // TOMATO_H
