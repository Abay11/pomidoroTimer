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
	//indicate if should automatically start long rest
	const char* IS_CONTINUOUS_WORK = "is_continous_work";
	//indicate show again a dialog window
	//each time after a whole round completion
	const char* SHOW_DIALOG_AGAIN = "show_dialog_again";

public:
	DataSaver(ConfigParams* configs);

	bool saveData();

	bool restoreData();

private:
	ConfigParams* configs_;
};

#endif // DATASAVER_H
