#include "concretestates.h"

#include "pomidoro.h"

Inactive::Inactive(Pomidoro* context)
	: State(STATES::INACTIVE, context)
{
}

void Inactive::start()
{
	context->setNewState(context->getActiveState());

	context->slotStartTimer(context->getWorkDuration());
}

Active::Active(Pomidoro* context)
	: State(STATES::ACTIVE, context)
{
}

void Active::pause()
{
	context->setNewState(context->getPausedState());
}

void Active::reset()
{

}

void Active::timerElapsed()
{
	++context->rounds_;

	context->total_ += context->rounds_ / 4;


	if(context->rounds_ < 4)
	{
		//switch on shortRest state
		context->setNewState(context->getShortRestState());

		context->slotStartTimer(context->getRestDuration());
	}
	else if(context->isContinuousWork && context->total_ < context->reps_)
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

	context->rounds_ %= 4;
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
	context->setNewState(context->getActiveState());
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

}

void ShortRest::reset()
{

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

}

void LongRest::reset()
{

}

void LongRest::timerElapsed()
{
	context->setNewState(context->getActiveState());

	context->slotStartTimer(context->getWorkDuration());
}
