#include "utility.h"

Utility::Utility()
{
}

std::pair<int, QTime> Utility::count_possible_repetitions(int pomidoroDuration, int shortRest, int longRest, QTime time)
{
	int hour = time.hour();
	int  minute = time.minute();

	int remainHours = 23 - hour;
	int remainMinutes = 60 - minute;

	int totalRemainMinutes = remainHours * 60 + remainMinutes;

	int minutesPerSession = pomidoroDuration * 4 + shortRest * 3 + longRest;

	int tomatoes = 0;
	tomatoes = totalRemainMinutes / minutesPerSession;

	int totalMinutesForAllPossibleTomatoes = totalRemainMinutes % minutesPerSession;

	int tillHour = totalMinutesForAllPossibleTomatoes / 60;
	int tillMinutes = totalMinutesForAllPossibleTomatoes % 60;

	int resHour = tillMinutes > 0 ? 23 - tillHour : 24 - tillHour;
	resHour = resHour == 24 ? 0 : resHour;

	int resMinutes = 60 - tillMinutes;
	resMinutes = 60 == resMinutes ? 0 : resMinutes;

	QTime tillTime(resHour, resMinutes);

	return std::make_pair(tomatoes, tillTime);
}
