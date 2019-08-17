#ifndef THREADCONTROLLER_H
#define THREADCONTROLLER_H

#include <QObject>

class Pomidoro;

class QThread;

/*
This class used to have possibility to send user's commands
to the Pomidoro class (there is an event loop
and from one thread we can't process user's commands).

Also we cannot controll QTimer from another thread.
This class should be used to controll Pomidoro class using
signals and slots.

The class create a thread and by command run() create P,
move it to that thread and run the thread.

To controll P need to to use the interface provided by this class
*/

class ThreadController : public QObject
{
	Q_OBJECT

public:
	explicit ThreadController(Pomidoro* instance = nullptr, QObject* parent = nullptr);

	//delete P and the thread
	~ThreadController();

	Pomidoro* pomidoro() const;

	//calls setConnections()
	//move P to the thread
	//and run the one
	void run();

	//quit the thread and wait until it will be stopped
	void stop();

signals:
	//these signals emits by slots in the declared above interfaces
	void cmdStart();

	void cmdStop();

	void cmdPause();

	void cmdSkip();

	void cmdQuitLoop();

public slots:
	//*****An interface to control Pomidoro states*****//
	void startPomidoro();

	void stopPomidoro();

	void pausePomidoro();

	void skipPomidoro();
	//************************************************//

private:
	QThread* thread_ = nullptr;

	Pomidoro* pomidoro_ = nullptr;
};

#endif // THREADCONTROLLER_H
