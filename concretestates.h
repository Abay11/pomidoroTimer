#ifndef CONCRETESTATES_H
#define CONCRETESTATES_H

#include "abstractstate.h"

class Pomidoro;

class Inactive : public AbstractState
{
	// AbstractState interface
public:
	Inactive(int reps, Pomidoro* context);
	~Inactive();

	void start() override;
};

class Active : public AbstractState
{
	Active(int reps, Pomidoro* context);
	~Active();

	// AbstractState interface
public:
	void pause() override;
	void reset() override;
	void stop() override;
	void timerElapsed() override;
};

class Paused : public AbstractState
{
	Paused(int reps, Pomidoro* context);
	~Paused();

	// AbstractState interface
public:
	void start() override;
	void reset() override;
	void stop() override;
	void timerElapsed() override;
};

class ShortRest : public AbstractState
{

	ShortRest(int reps, Pomidoro* context);
	~ShortRest();

	// AbstractState interface
public:
	void pause() override;
	void reset() override;
	void stop() override;
	void timerElapsed() override;
};

class LongRest : public AbstractState
{

	LongRest(int reps, Pomidoro* context);
	~LongRest();

	// AbstractState interface
public:
	void pause() override;
	void reset() override;
	void stop() override;
	void timerElapsed() override;
};



#endif // CONCRETESTATES_H
