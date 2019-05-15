#ifndef UTILITY_H
#define UTILITY_H

#include <QDateTime>

class Utility
{
public:
	Utility();

	static int count_possible_repetitions(int pomidoroDuration, int shortRest, int longRest,  QTime time);
};

#endif // UTILITY_H
