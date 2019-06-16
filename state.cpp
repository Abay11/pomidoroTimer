#include "state.h"

#include <QString>

QString State::log;

State::State(STATES type, Pomidoro* context)
	: context(context),
		type_(type)
{
}

State::~State()
{
	//	delete log;
}

//default ignore commands
void State::start()
{
}

void State::pause()
{
}

void State::reset()
{
}

void State::stop()
{
}

void State::timerElapsed()
{
}

State::STATES State::type() const
{
	return type_;
}

QString State::getLog() const
{
	return log;
}

void State::doLog(QString comment)
{
	QString toString;

	switch(type_)
	{
		case STATES::INACTIVE:
			toString = "INACTIVE";
			break;

		case STATES::ACTIVE:
			toString = "ACTIVE";
			break;

		case STATES::PAUSED:
			toString = "PAUSED";
			break;

		case STATES::SHORT_REST:
			toString = "SHORT_REST";
			break;

		case STATES::LONG_REST:
			toString = "LONG_REST";
			break;
	}

	if(!log.isEmpty())
		log.append("->");

	log.append(toString + "::" + comment);
}

void State::clearLog()
{
	log.clear();
}
