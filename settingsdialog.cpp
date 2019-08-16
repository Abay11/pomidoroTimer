#include "settingsdialog.h"

#include "pomidoro.h"

SettingsDialog::SettingsDialog(ConfigParams* params,	QWidget* p)
	: QDialog(p),
		params_(params),
		next_tomato_completion(new QLabel),
		max_tomatoes_label(new QLabel)
{
	spinWork = new QSpinBox();
	spinWork->setSingleStep(5);
	spinShort = new QSpinBox();
	spinShort->setSingleStep(5);
	spinLong = new QSpinBox();
	spinLong->setSingleStep(5);
	spinReps = new QSpinBox();
	pchturnLongRest = new QCheckBox;
	pchshowAgain = new QCheckBox;
	pcmdOk = new QPushButton("Accept and reset timer");
	pcmdCancel = new QPushButton("Cancel");

	spinWork->setValue(params_->work_);
	spinShort->setValue(params_->sh_rest_);
	spinLong->setValue(params_->l_rest_);
	spinReps->setValue(params_->reps_);
	pchturnLongRest->setChecked(params_->isContinuousWork_);
	pchshowAgain->setChecked(params_->showDialogAgain_);

	QFormLayout* pflay = new QFormLayout;

	pflay->addRow(new QLabel("Work duration"), spinWork);
	pflay->addRow(new QLabel("Short rest duration"), spinShort);
	pflay->addRow(new QLabel("Long rest duration"), spinLong);
	pflay->addRow(new QLabel("Reps count"), spinReps);
	pflay->addRow(new QLabel("Automatically start new pomidoro"), pchturnLongRest);
	pflay->addRow(new QLabel("Don't show request's dialog each time"), pchshowAgain);
	pflay->addRow(next_tomato_completion);
	pflay->addRow(max_tomatoes_label);
	pflay->addRow(pcmdOk, pcmdCancel);

	setLayout(pflay);
	connect(pcmdOk, SIGNAL(clicked()), SLOT(slotAccept()));
	connect(pcmdCancel, SIGNAL(clicked()), SLOT(slotReject()));

	connect(spinWork, SIGNAL(valueChanged(int)), SLOT(slotParametersChanged()));
	connect(spinShort, SIGNAL(valueChanged(int)), SLOT(slotParametersChanged()));
	connect(spinLong, SIGNAL(valueChanged(int)), SLOT(slotParametersChanged()));
	connect(spinReps, SIGNAL(valueChanged(int)), SLOT(slotParametersChanged()));
}

void SettingsDialog::showEvent(QShowEvent* event)
{
	QWidget::showEvent(event);

	setInfoLabels();
	qDebug() << "showEvent";
}

void SettingsDialog::setInfoLabels()
{
	int maxTomatoes;
	QTime finishTime;

	int workDuration = spinWork->value();
	int shortDuration = spinShort->value();
	int longDuration = spinLong->value();

	std::tie(maxTomatoes, finishTime) = Utility::count_possible_repetitions(workDuration,
			shortDuration,
			longDuration,
			QTime::currentTime());

	next_tomato_completion->setText("If start now you will complete a session at "
		+ Utility::next_completion(workDuration, shortDuration).toString("hh:mm"));

	max_tomatoes_label->setText("You can do " + QString::number(maxTomatoes)
		+ " Tomatoes till " + finishTime.toString("hh:mm"));
}


void SettingsDialog::slotAccept()
{
	params_->work_ = spinWork->value();
	params_->sh_rest_ = spinShort->value();
	params_->l_rest_ = spinLong->value();
	params_->reps_ = spinReps->value();
	params_->isContinuousWork_ = pchturnLongRest->isChecked();
	params_->showDialogAgain_ = !pchshowAgain->isChecked();

	//QDialog virtual slot
	//close dialog and returns Accepted code
	accept();
}

void SettingsDialog::slotReject()
{
	//QDialog virtual slot
	//close dialog and returns Rejected code
	reject();
}

void SettingsDialog::slotParametersChanged()
{
	setInfoLabels();
}
