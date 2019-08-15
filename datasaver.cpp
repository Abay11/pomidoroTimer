#include "datasaver.h"
#include "utility.h"
#include "pomidoro.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

DataSaver::DataSaver(ConfigParams* configs)
	: configs_(configs)
{
}

bool DataSaver::saveData()
{
	QFile file(CONFIG_PATH);

	if(!file.open(QFile::WriteOnly))
		return false;

	QJsonObject obj;
	obj[WORK] = configs_->work_;
	obj[SH_REST] = configs_->sh_rest_;
	obj[L_REST] = configs_->l_rest_;
	obj[REPS] = configs_->reps_;

	QJsonDocument doc(obj);

	file.write(doc.toJson());

	file.flush();
	file.close();

	return true;
}

bool DataSaver::restoreData()
{
	QFile file(CONFIG_PATH);

	if(!file.open(QFile::ReadOnly))
		return false;

	auto doc = QJsonDocument::fromJson(file.readAll());

	file.close();

	QJsonObject obj = doc.object();

	configs_->work_ = obj[WORK].toInt();
	configs_->sh_rest_ = obj[SH_REST].toInt();
	configs_->l_rest_ = obj[L_REST].toInt();
	configs_->reps_ = obj[REPS].toInt();

	return true;
}
