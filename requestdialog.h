#ifndef REQUESTDIALOG_H
#define REQUESTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>
#include <QApplication>

class RequestDialog:public QDialog
{
 Q_OBJECT
private:
 bool *pshowAgain;
 QCheckBox *pchshowAgain;
 QPushButton *pcmdOk, *pcmdCancel;
public:
 RequestDialog(bool *showAgain, QWidget *p=nullptr);
private slots:
 void slotAccept();
};

#endif // REQUESTDIALOG_H
