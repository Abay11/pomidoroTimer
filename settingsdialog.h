#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>

class SettingsDialog:public QDialog
{
 Q_OBJECT
private:
 int *pwork,
 *pshort,
 *plong,
 *preps;
 bool *pturnLongRest,
 *pshowAgain;

 QSpinBox *spinWork, *spinShort, *spinLong, *spinReps;

 QCheckBox *pchturnLongRest, *pchshowAgain;

 QPushButton *pcmdOk, *pcmdCancel;
public:
 SettingsDialog(int *w,
								int *s,
								int *l,
								int *r,
								bool *turnLongRest,
								bool *showAgain,
								QWidget *p=nullptr);

private slots:
 void slotAccept();
 void slotReject();

};

#endif // SETTINGSDIALOG_H
