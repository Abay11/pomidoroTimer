#ifndef CONCRETESTATES_H
#define CONCRETESTATES_H

#include "state.h"

class Pomidoro;

class Inactive : public State
{
	// AbstractState interface
public:
	Inactive(int reps, Pomidoro* context);
	virtual ~Inactive();

	void start() override;
};

class Active : public State
{
public:
	Active(int reps, Pomidoro* context);
	virtual ~Active();

	// AbstractState interface
	void pause() override;
	void reset() override;
	void stop() override;
	void timerElapsed() override;
};

class Paused : public State
{
public:
	Paused(int reps, Pomidoro* context);
	virtual ~Paused();

	// AbstractState interface
	void start() override;
	void reset() override;
	void stop() override;
	void timerElapsed() override;
};

class ShortRest : public State
{

public:
	ShortRest(int reps, Pomidoro* context);
	virtual ~ShortRest();

	// AbstractState interface
	void pause() override;
	void reset() override;
	void stop() override;
	void timerElapsed() override;
};

class LongRest : public State
{

public:
	LongRest(int reps, Pomidoro* context);
	virtual ~LongRest();

	// AbstractState interface
	void pause() override;
	void reset() override;
	void stop() override;
	void timerElapsed() override;
};



#endif // CONCRETESTATES_H
