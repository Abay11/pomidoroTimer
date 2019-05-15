#include "utility.h"

Utility::Utility()
{
}

int Utility::count_possible_repetitions(int pomidoroDuration, int shortRest, int longRest, QTime time)
{
	int hour = time.hour();
	int  minute = time.minute();

	int remainHours = 23 - hour;
	int remainMinutes = 60 - minute;

	int totalRemainMinuts = remainHours * 60 + remainMinutes;

	int minutesPerSession = pomidoroDuration * 4 + shortRest * 3 + longRest;

	int res = 0;
	res = totalRemainMinuts / minutesPerSession;

	return res;
}
