#ifndef ABSTRACTSTATE_H
#define ABSTRACTSTATE_H

class Pomidoro;

class State
{
public:
	enum class STATES;

	State(int repetitions, STATES s, Pomidoro* context);

	virtual ~State();

	virtual void start();

	virtual void pause();

	virtual void reset();

	virtual void stop();

	virtual void timerElapsed();

	STATES type() const;

	enum class STATES {INACTIVE, ACTIVE, PAUSED, SHORT_REST, LONG_REST};

protected:
	Pomidoro* context;

private:

	int repetitions;

	const STATES type_;
};

#endif // ABSTRACTSTATE_H
