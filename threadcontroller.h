#ifndef THREADCONTROLLER_H
#define THREADCONTROLLER_H

#include <QObject>

class ThreadController : public QObject
{
 Q_OBJECT
public:
 explicit ThreadController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // THREADCONTROLLER_H