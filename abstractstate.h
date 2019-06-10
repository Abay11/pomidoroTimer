#ifndef ABSTRACTSTATE_H
#define ABSTRACTSTATE_H

class Pomidoro;

class AbstractState
{

public:
	AbstractState(int repetitions, Pomidoro* context);

	~AbstractState();

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
