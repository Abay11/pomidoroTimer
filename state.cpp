#include "state.h"
#include "pomidoro.h"

#include <QString>

QString State::log;

ConfigParams* State::configs_ = nullptr;

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
	context->setNewState(context->getInactiveState());

	//notify GUI to change icon
	context->emit_inactive();
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

void State::setParams(ConfigParams* configs)
{
	configs_ = configs;
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
