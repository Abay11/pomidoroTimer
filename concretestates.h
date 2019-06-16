#ifndef CONCRETESTATES_H
#define CONCRETESTATES_H

#include "state.h"

class Pomidoro;

class Inactive : public State
{
	// AbstractState interface
public:
	Inactive(Pomidoro* context);

	void start() override;
};

class Active : public State
{
public:
	Active(Pomidoro* context);

	// AbstractState interface
	void pause() override;
	void reset() override;
	void stop() override;
	void timerElapsed() override;
};

class Paused : public State
{
public:
	Paused(Pomidoro* context);
	virtual ~Paused() override;

	// AbstractState interface
	void start() override;
	void reset() override;
	void stop() override;
	void timerElapsed() override;
};

class ShortRest : public State
{

public:
	ShortRest(Pomidoro* context);
	virtual ~ShortRest() override;

	// AbstractState interface
	void pause() override;
	void reset() override;
	void stop() override;
	void timerElapsed() override;
};

class LongRest : public State
{

public:
	LongRest(Pomidoro* context);
	virtual ~LongRest() override;

	// AbstractState interface
	void pause() override;
	void reset() override;
	void stop() override;
	void timerElapsed() override;
};



#endif // CONCRETESTATES_H
