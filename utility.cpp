#include "utility.h"

Utility::Utility()
{
}

const QString Utility::VERSION = "1.3";

std::pair<int, QTime> Utility::count_possible_repetitions(int pomidoroDuration, int shortRest, int longRest, QTime time)
{
	int hour = time.hour();
	int  minute = time.minute();

	int remainHours = 23 - hour;
	int remainMinutes = 60 - minute;

	int totalDurationMinutes = remainHours * 60 + remainMinutes;

	int minutesPerTomato = pomidoroDuration * 4 + shortRest * 3 + longRest;

	int maxTomatoes = 0;
	maxTomatoes = totalDurationMinutes / minutesPerTomato;

	int durationMinutesForMaxTomatoes = totalDurationMinutes % minutesPerTomato;

	int remainingHours = durationMinutesForMaxTomatoes / 60;
	int remainingMinutes = durationMinutesForMaxTomatoes % 60;

	int finishHour = remainingMinutes > 0 ? 23 - remainingHours : 24 - remainingHours;
	finishHour %= 24;

	int finishMinute = 60 - remainingMinutes;
	finishMinute = 60 == finishMinute ? 0 : finishMinute;

	QTime finishTime(finishHour, finishMinute);

	return std::make_pair(maxTomatoes, finishTime);
}

QTime Utility::next_completion(int pomidoroDuration, int shortRest, QTime time)
{
	int total_minutes = 4 * pomidoroDuration + 3 * shortRest;
	int hours = total_minutes / 60;
	int remainder_minutes = total_minutes % 60;

	int res_minutes = (time.minute() + remainder_minutes) % 60;
	int res_hours = (time.hour() + hours + (time.minute() + remainder_minutes) / 60) % 24;

	return QTime(res_hours,
			res_minutes);
}

