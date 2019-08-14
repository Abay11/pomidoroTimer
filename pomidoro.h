#ifndef TOMATO_H
#define TOMATO_H


#include "settingsdialog.h"
#include "requestdialog.h"
#include "concretestates.h"
#include "threadcontroller.h"
#include "statesholder.h"

#include <QObject>

class TrayUI;
class State;
class DataSaver;

class QTimer;

class ConfigParams
{
public:
	//indicates if need to switch on longRestState after finishing pomidoro
	bool isContinuousWork = false;
	bool showDialogAgain = true;

	int	work_ = 20;
	int sh_rest_ = 5;
	int l_rest_ = 15;
	int reps_ = 1;
	int rounds_ = 0;
	//indicates already have been finished total pomidoro count
	int total_ = 0;
};

class Pomidoro : public QObject, public StatesHolder
{
	Q_OBJECT

	friend class test;

	friend TrayUI;
	friend DataSaver;
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

	void setReps(int value);

	bool isRunning();

	void setIsContinuousWork(bool value);

	int getTimerRemainingTime();

	int getTotal() const;

	int getRounds() const;

	ConfigParams* configs();

public slots:
	void slotStart();

	void slotPause();

	void slotStop();

	void slotReset();

	void slotStartTimer(int min);

private slots:
	void slotTimeOut();

signals:
	//Pomidoro should emit this signals
	//cause Controller will be wait for these
	//and those not will finished to fast
	void active();

	void inactive();

	//TODO: set more appropriatable name
	void rest();

	//class members
private:
	void initTimerIfNot();

protected:
	ConfigParams* configs_;

	DataSaver* saver_;

private:
	QTimer* timer_ = nullptr;

	std::atomic<bool> isRunning_;
};

Q_DECLARE_METATYPE(Pomidoro);

#endif // TOMATO_H
