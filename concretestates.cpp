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
	context->setNewState(context->getInactiveState());
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
