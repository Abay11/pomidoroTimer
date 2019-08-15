#ifndef DATASAVER_H
#define DATASAVER_H

class ConfigParams;

class QString;
class QJsonObject;

class DataSaver
{
	const char* WORK = "work";
	const char* SH_REST = "short_rest";
	const char* L_REST = "long_rest";
	const char* REPS = "reps_count";

public:
	DataSaver(ConfigParams* configs);

	bool saveData();

	bool restoreData();

private:
	ConfigParams* configs_;
};

#endif // DATASAVER_H
