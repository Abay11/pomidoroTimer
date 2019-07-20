#ifndef THREADCONTROLLER_H
#define THREADCONTROLLER_H

#include <QObject>

class Pomidoro;

/*
This class used to have possibility to send user's commands
to the Pomidoro class (there is an event loop
and from one thread we can't process user's commands).

The class create a thread and by command run() create P,
move it to that thread and run the thread.
To controll P need to fetch it by a getter
and use it from GUI
*/
class ThreadController : public QObject
{
	Q_OBJECT

public:
	explicit ThreadController(QObject* parent = nullptr);

	//delete P and the thread
	~ThreadController();

	Pomidoro* pomidoro() const;

signals:

public slots:

	//init the thread and P
	//then move the P to the thread
	//and run the thread
	void run();

	//quit the thread and wait until it will be stopped
	void stop();

private:
	QThread* thread_;

	Pomidoro* pomidoro_;
};

#endif // THREADCONTROLLER_H
