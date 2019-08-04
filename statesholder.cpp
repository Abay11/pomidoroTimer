#include "statesholder.h"

#include "concretestates.h"

StatesHolder::StatesHolder(Pomidoro* context)
	:	inactiveState(new Inactive(context))
	, activeState(new Active(context))
	, pausedState(new Paused(context))
	, shortRestState(new ShortRest(context))
	, longRestState(new LongRest(context))
	, state_(inactiveState)
{
}

State* StatesHolder::getState()
{
	return state_;
}

State* StatesHolder::getLongRestState()
{
	return longRestState;
}

void StatesHolder::setNewState(State* state)
{
	state_ = state;
}

State* StatesHolder::getShortRestState()
{
	return shortRestState;
}

State* StatesHolder::getPausedState()
{
	return pausedState;
}

State* StatesHolder::getActiveState()
{
	return activeState;
}

State* StatesHolder::getInactiveState()
{
	return inactiveState;
}
