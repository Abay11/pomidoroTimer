#ifndef TOMATO_H
#define TOMATO_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <QApplication>
#include <QDebug>
#include <QTimer>
#include <QTime>

#include "settingsdialog.h"

class Tomato:public QObject
{
 Q_OBJECT
private:
 QSystemTrayIcon *ptray;
 QMenu *pmenu;
 QAction *padisplay;
 QAction *pastart;
 QAction *pastop;
 QTimer *ptimer;
 QTime *ptime;

 int
 workDuration      =20,
 shortRestDuration =5,
 longRestDuration  =15,
 reps=2,
 round=0;

 bool turnLongRest=false;

 enum TYPE{WORK=0, SHORTREST, LONGREST}type=WORK;

 void updateDisplay();
public:
 Tomato(QObject *p=nullptr);

private slots:
 void slotStart();
 void slotStop();
 void slotUpdate();

 void slotOpenSettings();
};

#endif // TOMATO_H
