#include "concretestates.h"

#include "pomidoro.h"

#include <QTimer>

Inactive::Inactive(Pomidoro* context)
	: State(STATES::INACTIVE, context)
{
}

void Inactive::start()
{
	context->setNewState(context->getActiveState());

	context->slotStartTimer(context->getWorkDuration());

	//notify GUI to change icon
	context->emit_active();
}

Active::Active(Pomidoro* context)
	: State(STATES::ACTIVE, context)
{
}

void Active::pause()
{
	auto p = dynamic_cast<Paused*>(context->pausedState);
	p->previous = context->state_;

	//also save timer state
	p->remaining_duration = context->timer_->remainingTime();

	context->setNewState(context->getPausedState());

	context->timer_->stop();

	context->emit_pause();
}

void Active::reset()
{
	context->slotStartTimer(configs_->work_);
}

void Active::timerElapsed()
{
	++configs_->rounds_;

	configs_->total_ += configs_->rounds_ / 4;

	if(configs_->rounds_ < 4)
	{
		//switch on shortRest state
		context->setNewState(context->getShortRestState());

		context->slotStartTimer(context->getRestDuration());
	}
	else if(configs_->isContinuousWork_ && configs_->total_ < configs_->reps_)
	{
		//switch on longRest state
		context->setNewState(context->getLongRestState());

		context->slotStartTimer(context->getLongRestDuration());
	}
	else
	{
		//switch on inactive state
		context->setNewState(context->getInactiveState());
	}

	configs_->rounds_ %= 4;
}

Paused::Paused(Pomidoro* context)
	: State(STATES::PAUSED, context)
{
}

Paused::~Paused()
{
}

void Paused::start()
{
	context->setNewState(previous);

	//context->slotStartTimer(remaining_duration);
	context->timer_->start(remaining_duration);

	if(previous->type() == STATES::ACTIVE)
		context->emit_active();
	else if(previous->type() == STATES::SHORT_REST)
		context->emit_rest();
}

void Paused::reset()
{
}

void Paused::timerElapsed()
{
	context->setNewState(context->getActiveState());

	context->slotStartTimer(context->getWorkDuration());
}

ShortRest::ShortRest(Pomidoro* context)
	: State(STATES::SHORT_REST, context)
{
}

ShortRest::~ShortRest()
{
}

void ShortRest::pause()
{
	auto p = dynamic_cast<Paused*>(context->pausedState);
	p->previous = context->state_;

	//also save timer state
	p->remaining_duration = context->timer_->remainingTime();

	context->setNewState(context->getPausedState());

	context->timer_->stop();

	context->emit_pause();
}

void ShortRest::reset()
{
	context->slotStartTimer(configs_->sh_rest_);
}

void ShortRest::timerElapsed()
{
	context->setNewState(context->getActiveState());

	context->slotStartTimer(context->getWorkDuration());
}

LongRest::LongRest(Pomidoro* context)
	: State(STATES::LONG_REST, context)
{
}

LongRest::~LongRest()
{
}

void LongRest::pause()
{
	auto p = dynamic_cast<Paused*>(context->pausedState);
	p->previous = context->state_;

	//also save timer state
	p->remaining_duration = context->timer_->remainingTime();

	context->setNewState(context->getPausedState());

	context->timer_->stop();

	context->emit_pause();
}

void LongRest::reset()
{
	context->slotStartTimer(configs_->l_rest_);
}

void LongRest::timerElapsed()
{
	context->setNewState(context->getActiveState());

	context->slotStartTimer(context->getWorkDuration());
}
