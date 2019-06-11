#ifndef ABSTRACTSTATE_H
#define ABSTRACTSTATE_H

class Pomidoro;

class State
{

public:
	State(int repetitions, Pomidoro* context);

	virtual ~State();

	virtual void start();

	virtual void pause();

	virtual void reset();

	virtual void stop();

	virtual void timerElapsed();

private:
	Pomidoro* context;

	int repetitions;
};

#endif // ABSTRACTSTATE_H
