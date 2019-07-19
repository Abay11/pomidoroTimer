#ifndef THREADCONTROLLER_H
#define THREADCONTROLLER_H

#include <QObject>

class Pomidoro;

class ThreadController : public QObject
{
	Q_OBJECT

public:
	explicit ThreadController(QObject* parent = nullptr);

signals:

public slots:

	void initPomidoro();

private:
	QThread* thread_;

	Pomidoro* pomidoro_;
};

#endif // THREADCONTROLLER_H
