#ifndef ABSTRACTSTATE_H
#define ABSTRACTSTATE_H

class Pomidoro;
class ConfigParams;

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

	static QString getLog();

	virtual void doLog(QString comment);

	static void clearLog();

	static void setParams(ConfigParams* configs);

private:
	QString toString();

protected:
	Pomidoro* context;
	//cause all states relative to the one pomidoro
	//configs are same for all states
	static ConfigParams* configs_;

	//for the tests to check workflow
	static QString log;

private:

	const STATES type_;
};

#endif // ABSTRACTSTATE_H
