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
#include <QSound>

#include "settingsdialog.h"
#include "requestdialog.h"

class Tomato:public QObject
{
 Q_OBJECT
private:
 QSystemTrayIcon *ptray;
 QMenu *pmenu;
 QAction *padisplay;
 QAction *parounds;
 QAction *pastart;
 QAction *pastop;
 QTimer *ptimer;
 QTime *ptime;
 QSound *psound;


 int
 workDuration      =20,
 shortRestDuration =5,
 longRestDuration  =15,
 reps=1,
 round=0,
 total=0;

 bool turnLongRest=false;
 bool showAgainDialog=true;

 enum TYPE{WORK=0, SHORTREST, LONGREST}type=WORK;

 void updateInfo();
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
