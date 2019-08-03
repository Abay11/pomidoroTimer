#ifndef TOMATO_H
#define TOMATO_H


#include "settingsdialog.h"
#include "requestdialog.h"
#include "concretestates.h"
#include "threadcontroller.h"

#include <QObject>

class TrayUI;
class State;

class QTimer;

class Pomidoro : protected QObject
{
	Q_OBJECT

	friend ThreadController;
	friend Inactive;
	friend Active;
	friend Paused;
	friend ShortRest;
	friend LongRest;

public:
	Pomidoro(QObject* parent = nullptr, TrayUI* ui_instance = nullptr);

	Pomidoro(const Pomidoro& other);

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

	bool isRunning();

	void setIsContinuousWork(bool value);

public slots:

	void slotStart();

	void slotPause();

	void slotStop();

	void slotReset();

	void slotStartTimer(int min);

private slots:

	void slotTimeOut();

signals:
	void eventloopInited();

	void finished();

	//class members
private:
	void initIfNotTimer_Eventloop();

protected:
	//indicates if need to switch on longRestState after finishing pomidoro
	bool isContinuousWork = false;

	int	work_ = 20;
	int sh_rest_ = 5;
	int l_rest_ = 15;
	int reps_ = 1;
	int rounds_ = 0;
	//indicates already have been finished total pomidoro count
	int total_ = 0;

private:
	QTimer* timer = nullptr;
	QTimer* eventProcessorTimer = nullptr;
	QEventLoop* loop = nullptr;

	bool showAgainDialog = true;

	std::atomic<bool> isRunning_;

	State* inactiveState;
	State* activeState;
	State* pausedState;
	State* shortRestState;
	State* longRestState;
	State* state_;
};

Q_DECLARE_METATYPE(Pomidoro);

#endif // TOMATO_H
