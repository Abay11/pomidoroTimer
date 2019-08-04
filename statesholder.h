#ifndef STATESHOLDER_H
#define STATESHOLDER_H

class Pomidoro;
class State;

class StatesHolder
{
public:
	StatesHolder(Pomidoro* context);

	State* getState();

	State* getInactiveState();

	State* getActiveState();

	State* getPausedState();

	State* getShortRestState();

	State* getLongRestState();

	void setNewState(State* state);

protected:
	State* inactiveState;
	State* activeState;
	State* pausedState;
	State* shortRestState;
	State* longRestState;
	State* state_;

};

#endif // STATESHOLDER_H
