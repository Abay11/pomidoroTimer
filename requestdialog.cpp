#include "requestdialog.h"

RequestDialog::RequestDialog(bool *showAgain, QWidget *p)
 :QDialog(p)
 ,pshowAgain(showAgain)
 ,pchshowAgain(new QCheckBox)
 ,pcmdOk(new QPushButton("Ok"))
 ,pcmdCancel(new QPushButton("Cancel"))
{
 QFormLayout *pflay=new QFormLayout;
 pflay->addRow(new QLabel("Start new pomidoro after long break?"));
 pflay->addRow(new QLabel("Don't show this again"), pchshowAgain);
 pflay->addRow(pcmdOk, pcmdCancel);

 setLayout(pflay);

 connect(pcmdOk, SIGNAL(clicked()), SLOT(slotAccept()));
 connect(pcmdCancel, SIGNAL(clicked()), qApp, SLOT((quit())));
}

void RequestDialog::slotAccept()
{
 *pshowAgain=!pchshowAgain->isChecked();
 return accept();
}
