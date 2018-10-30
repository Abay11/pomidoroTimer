#include "settingsdialog.h"

SettingsDialog::SettingsDialog(int *w, int *s, int *l, int *r, bool *turnLongRest, QWidget *p)
 :QDialog(p)
 ,pwork(w)
 ,pshort(s)
 ,plong(l)
 ,preps(r)
 ,pturnLongRest(turnLongRest)
 ,plework(new QLineEdit)
 ,pleshort(new QLineEdit)
 ,plelong(new QLineEdit)
 ,plereps(new QLineEdit)
 ,pchturnLongRest(new QCheckBox)
 ,pcmdOk(new QPushButton("Accept and reset timer"))
 ,pcmdCancel(new QPushButton("Cancel"))
{

 plework->setText(QString::number(*w));
 pleshort->setText(QString::number(*s));
 plelong->setText(QString::number(*l));
 plereps->setText(QString::number(*r));
 pchturnLongRest->setChecked(*turnLongRest);

 QFormLayout *pflay=new QFormLayout;
 pflay->addRow(new QLabel("Work duration"), plework);
 pflay->addRow(new QLabel("Short rest duration"), pleshort);
 pflay->addRow(new QLabel("Long rest duration"), plelong);
 pflay->addRow(new QLabel("Reps count"), plereps);
 pflay->addRow(new QLabel("Enabling long duration duration"), pchturnLongRest);
 pflay->addRow(pcmdOk, pcmdCancel);

 setLayout(pflay);
 connect(pcmdOk, SIGNAL(clicked()), SLOT(slotAccept()));
 connect(pcmdCancel, SIGNAL(clicked()), SLOT(slotReject()));
}

void SettingsDialog::slotAccept()
{
 *pwork=plework->text().toInt();
 *pshort=pleshort->text().toInt();
 *plong=plelong->text().toInt();
 *preps=plereps->text().toInt();
 *pturnLongRest=pchturnLongRest->isChecked();
 accept();
}

void SettingsDialog::slotReject()
{
 reject();
}
