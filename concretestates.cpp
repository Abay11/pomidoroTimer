#include "concretestates.h"

Inactive::Inactive(int reps, Pomidoro* context)
	: State(reps, context)
{

}

Inactive::~Inactive()
{

}

void Inactive::start()
{

}

Active::Active(int reps, Pomidoro* context)
	: State(reps, context)
{

}

Active::~Active()
{

}

void Active::pause()
{

}

void Active::reset()
{

}

void Active::stop()
{

}

void Active::timerElapsed()
{

}

Paused::Paused(int reps, Pomidoro* context)
	: State(reps, context)
{

}

Paused::~Paused()
{

}

void Paused::start()
{

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
	: State(reps, context)
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
	: State(reps, context)
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
