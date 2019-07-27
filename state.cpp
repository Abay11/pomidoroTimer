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

QString State::getLog()
{
	return log;
}

void State::doLog(QString comment)
{
	if(!log.isEmpty())
		log.append("->");

	log.append(toString() + "::" + comment);
}

void State::clearLog()
{
	log.clear();
}

QString State::toString()
{
	switch(type_)
	{
		case STATES::INACTIVE:
			return "INACTIVE";

		case STATES::ACTIVE:
			return "ACTIVE";

		case STATES::PAUSED:
			return "PAUSED";

		case STATES::SHORT_REST:
			return "SHORT_REST";

		case STATES::LONG_REST:
			return "LONG_REST";
	}
}
