#include "state.h"

State::State(int reps, STATES type, Pomidoro* context)
	: context(context),
		repetitions(reps),
		type_(type)
{
}

State::~State()
{
}

//default ignore commands
void State::start()
{
}

void State::pause()
{
}

void State::reset()
{
}

void State::stop()
{
}

void State::timerElapsed()
{
}

State::STATES State::type() const
{
	return type_;
}
