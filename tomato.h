#ifndef TOMATO_H
#define TOMATO_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <QApplication>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QFile>
#include <QDataStream>

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
 bool showAgainDialog=true;

 enum TYPE{WORK=0, SHORTREST, LONGREST}type=WORK;

 void updateDisplay();
 void saveSettings();
 void restoreSettings();
public:
 Tomato(QObject *p=nullptr);
 ~Tomato();

private slots:
 void slotStart();
 void slotStop();
 void slotUpdate();

 void slotOpenSettings();
};

#endif // TOMATO_H
