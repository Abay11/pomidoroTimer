#include "abstractstate.h"

AbstractState::AbstractState(int reps, Pomidoro* context)
	: context(context)
	, repetitions(reps)
{
}

void AbstractState::start()
{

}

void AbstractState::pause()
{

}

void AbstractState::reset()
{

}

void AbstractState::stop()
{

}

void AbstractState::timerElapsed()
{

}
