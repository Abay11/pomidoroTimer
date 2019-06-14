#include "concretestates.h"

#include "pomidoro.h"

Inactive::Inactive(int reps, Pomidoro* context)
	: State(reps, STATES::INACTIVE, context)
{

}

void Inactive::start()
{
	context->setNewState(context->getActiveState());
}

Active::Active(int reps, Pomidoro* context)
	: State(reps, STATES::ACTIVE, context)
{

}

Active::~Active()
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

}

Paused::Paused(int reps, Pomidoro* context)
	: State(reps, STATES::PAUSED, context)
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

ShortRest::ShortRest(int reps, Pomidoro* context)
	: State(reps, STATES::SHORT_REST, context)
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

LongRest::LongRest(int reps, Pomidoro* context)
	: State(reps, STATES::LONG_REST, context)
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
