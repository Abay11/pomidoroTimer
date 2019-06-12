#ifndef UTILITY_H
#define UTILITY_H

#include <QTime>

class Utility
{
public:
	Utility();

	static std::pair<int, QTime> count_possible_repetitions(int pomidoroDuration, int shortRest, int longRest,  QTime time);

	static QTime next_completion(int pomidoroDuration, int shortRest, QTime time = QTime::currentTime());

	static const QString VERSION;
};

#endif // UTILITY_H
