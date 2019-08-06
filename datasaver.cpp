#include "datasaver.h"
#include "utility.h"
#include "pomidoro.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

DataSaver::DataSaver(Pomidoro* context)
	: context_(context)
{
}

bool DataSaver::saveData()
{
	QFile file(CONFIG_PATH);

	if(!file.open(QFile::WriteOnly))
		return false;

	QJsonObject obj;
	obj[WORK] = context_->work_;
	obj[SH_REST] = context_->sh_rest_;
	obj[L_REST] = context_->l_rest_;
	obj[REPS] = context_->reps_;

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

	context_->work_ = obj[WORK].toInt();
	context_->sh_rest_ = obj[SH_REST].toInt();
	context_->l_rest_ = obj[L_REST].toInt();
	context_->reps_ = obj[REPS].toInt();

	return true;
}
