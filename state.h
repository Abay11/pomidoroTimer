#ifndef ABSTRACTSTATE_H
#define ABSTRACTSTATE_H

class Pomidoro;

class QString;

class State
{
public:
	enum class STATES;

	State(STATES s, Pomidoro* context);

	virtual ~State();

	virtual void start();

	virtual void pause();

	virtual void reset();

	virtual void stop();

	virtual void timerElapsed();

	STATES type() const;

	enum class STATES {INACTIVE, ACTIVE, PAUSED, SHORT_REST, LONG_REST};

	QString getLog() const;

	virtual void doLog(QString comment);

protected:
	Pomidoro* context;

	//for the tests to check workflow
	static QString log;

private:

	const STATES type_;
};

#endif // ABSTRACTSTATE_H
