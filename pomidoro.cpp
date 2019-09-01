#include "pomidoro.h"
#include "concretestates.h"
#include "trayui.h"
#include "datasaver.h"

#include <QTimer>
#include <QSound>

Pomidoro::Pomidoro(QObject* parent, TrayUI* /*ui*/)
	: QObject(parent),
		StatesHolder(this),
		configs_(new ConfigParams),
		saver_(new DataSaver(configs_)),
		player_(new QSound(":/Sounds/birds.wav"))
{
	saver_->restoreData();

	State::setParams(configs_);

	isRunning_ = false;

	qApp->setQuitOnLastWindowClosed(false);
}

Pomidoro::Pomidoro(const Pomidoro& other)
	: QObject(other.parent()), StatesHolder(this)
{
	//TODO: add realisation
}

Pomidoro::~Pomidoro()
{
	delete timer_;
}

int Pomidoro::getWorkDuration() const
{
	return configs_->work_;
}

int Pomidoro::getRestDuration() const
{
	return configs_->sh_rest_;
}

int Pomidoro::getLongRestDuration() const
{
	return configs_->l_rest_;
}

int Pomidoro::getReps() const
{
	return configs_->reps_;
}

void Pomidoro::setDurations(int work, int rest, int long_rest)
{
	configs_->work_ = work;

	configs_->sh_rest_ = rest;

	configs_->l_rest_ = long_rest;
}

void Pomidoro::setWorkDuration(int min)
{
	configs_->work_ = min;
}

void Pomidoro::setShortRestDuration(int min)
{
	configs_->sh_rest_ = min;
}

void Pomidoro::setLongRestDuration(int min)
{
	configs_->l_rest_ = min;
}

void Pomidoro::setReps(int value)
{
	configs_->reps_ = value;
}

void Pomidoro::slotStart()
{
	isRunning_ = true;

	state_->doLog("start()");

	state_->start();
}

void Pomidoro::slotPause()
{
	state_->doLog("pause()");

	//need to save previous state,
	//because the PAUSED state should to know
	//on which state need to switch on
	//after slotStart() was invoked
	state_->pause();
}

void Pomidoro::slotStop()
{
	if(timer_) //the timer may be not init if not be called Start
		timer_->stop();

	state_->stop();

	isRunning_ = false;

	emit inactive();
}

void Pomidoro::slotReset()
{
	//just restarts timer with an interval depends on current state
	state_->reset();
}

void Pomidoro::slotSkip()
{
	timer_->setInterval(1000);
}

void Pomidoro::slotStartTimer(int min)
{
	initTimerIfNot();

	timer_->start(min * 1000 * 60);
}

void Pomidoro::slotSaveConfigs()
{
	if(!saver_->saveData())
		qWarning() << "Pomidoro::slotSaveConfigs(): Couldn't save data";
}

void Pomidoro::slotTimeOut()
{
	state_->doLog("timerElapsed()");

	//need to emit a signal for UI to set rest icon,
	//if we switch on SHORT or LONG REST state
	//for it, check if current state is ACTIVE
	bool isWorkState = state_->type() == State::STATES::ACTIVE;

	//notify GUI to change icon
	if(isWorkState) emit rest();
	else emit active();

	state_->timerElapsed();

	if(configs_->total_ >= configs_->reps_)
	{
		isRunning_ = false;

		emit inactive(); //notify GUI to change icon
	}

	player_->play();
}

void Pomidoro::initTimerIfNot()
{
	if(!timer_)
	{
		timer_ = new QTimer;
		timer_->setSingleShot(true);
		connect(timer_, SIGNAL(timeout()), SLOT(slotTimeOut()));
	}
}

void Pomidoro::emit_active()
{
	emit active();
}

void Pomidoro::emit_inactive()
{
	emit inactive();
}

void Pomidoro::emit_pause()
{
	emit pause();
}

void Pomidoro::emit_rest()
{
	emit rest();
}

int Pomidoro::getRounds() const
{
	return configs_->rounds_;
}

ConfigParams* Pomidoro::configs()
{
	return configs_;
}

int Pomidoro::getTotal() const
{
	return configs_->total_;
}

bool Pomidoro::isRunning()
{
	return isRunning_.load();
}

void Pomidoro::setIsContinuousWork(bool value)
{
	configs_->isContinuousWork_ = value;
}

int Pomidoro::getTimerRemainingTime()
{
	//if timer is active returns actual data
	if(timer_ && timer_->isActive())
		return timer_->remainingTime();

	//timer is paused, return saved data
	if(state_->type() == State::STATES::PAUSED)
		return static_cast<Paused*>(state_)->remaining_duration;

	//cause QTimer::remainingTime() returns milliseconds
	//need to convert to milliseconds (we store minutes)
	return configs_->work_ * 60 * 1000;
}
