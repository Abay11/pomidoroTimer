#include "concretestates.h"

Inactive::Inactive(int reps, Pomidoro* context)
	: AbstractState(reps, context)
{

}

Active::Active(int reps, Pomidoro* context)
	: AbstractState(reps, context)
{

}

Paused::Paused(int reps, Pomidoro* context)
	: AbstractState(reps, context)
{

}

ShortRest::ShortRest(int reps, Pomidoro* context)
	: AbstractState(reps, context)
{
}

ShortRest::~ShortRest()
{

}

LongRest::LongRest(int reps, Pomidoro* context)
	: AbstractState(reps, context)
{

}
