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

void Active::stop()
{
	context->setNewState(context->getInactiveState());
}

void Active::timerElapsed()
{
	static int& rounds = context->rounds();

	rounds += 1;

	if(rounds < 4)
	{
		//switch to shortRest state
		context->setNewState(context->getShortRestState());

		context->slotStartTimer(context->getRestDuration());
	}
	//TODO: else if() - for longRest
	else
	{
		context->setNewState(context->getInactiveState());
	}
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

void Paused::stop()
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

void ShortRest::stop()
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

void LongRest::stop()
{

}

void LongRest::timerElapsed()
{

}
