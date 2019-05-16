#include "settingsdialog.h"

SettingsDialog::SettingsDialog(int* w,
	int* s,
	int* l,
	int* r,
	bool* turnLongRest,
	bool* showAgain,
	QWidget* p)
	: QDialog(p)
	, pwork(w)
	, pshort(s)
	, plong(l)
	, preps(r)
	, pturnLongRest(turnLongRest)
	, pshowAgain(showAgain)
	, max_tomatoes_label(new QLabel)
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

	spinWork->setValue(*w);
	spinShort->setValue(*s);
	spinLong->setValue(*l);
	spinReps->setValue(*r);
	pchturnLongRest->setChecked(*turnLongRest);
	pchshowAgain->setChecked(*showAgain);

	QFormLayout* pflay = new QFormLayout;

	pflay->addRow(new QLabel("Work duration"), spinWork);
	pflay->addRow(new QLabel("Short rest duration"), spinShort);
	pflay->addRow(new QLabel("Long rest duration"), spinLong);
	pflay->addRow(new QLabel("Reps count"), spinReps);
	pflay->addRow(new QLabel("Automatically start new pomidoro"), pchturnLongRest);
	pflay->addRow(new QLabel("Don't show request's dialog each time"), pchshowAgain);
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

	setLabelMaxRepetitions();
	qDebug() << "showEvent";
}

void SettingsDialog::setLabelMaxRepetitions()
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

	max_tomatoes_label->setText("You can do " + QString::number(maxTomatoes)
		+ " Tomatoes till " + finishTime.toString("hh:mm"));
}


void SettingsDialog::slotAccept()
{
	*pwork = spinWork->value();
	*pshort = spinShort->value();
	*plong = spinLong->value();
	*preps = spinReps->value();
	*pturnLongRest = pchturnLongRest->isChecked();
	*pshowAgain = !pchshowAgain->isChecked();
	accept();
}

void SettingsDialog::slotReject()
{
	reject();
}

void SettingsDialog::slotParametersChanged()
{
	setLabelMaxRepetitions();
}
