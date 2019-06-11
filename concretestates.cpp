#include "concretestates.h"

Inactive::Inactive(int reps, Pomidoro* context)
	: State(reps, context)
{

}

Active::Active(int reps, Pomidoro* context)
	: State(reps, context)
{

}

Paused::Paused(int reps, Pomidoro* context)
	: State(reps, context)
{

}

ShortRest::ShortRest(int reps, Pomidoro* context)
	: State(reps, context)
{
}

ShortRest::~ShortRest()
{

}

LongRest::LongRest(int reps, Pomidoro* context)
	: State(reps, context)
{

}
