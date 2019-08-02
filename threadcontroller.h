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

	explicit ThreadController(const ThreadController& other);

	//delete P and the thread
	~ThreadController();

	Pomidoro* pomidoro() const;

	//*****An interface to control Pomidoro states*****//
	void startPomidoro();

	void stopPomidoro();

	void pausePomidoro();
	//************************************************//

signals:
	//these signals emits by slots in the declared above interfaces
	void cmdStart();

	void cmdStop();

	void cmdPause();

	void cmdQuitLoop();

public slots:
	//calls setConnections()
	//move P to the thread
	//and run the one
	void run();

	//quit the thread and wait until it will be stopped
	void stop();

	//after init of eventloop(EL) in the P
	//a signal will be emitted and when we receive it
	//we'll call this slot
	//where we connect a signal with EL to interrupt it
	void slotSetConnections();

private:
	void quitLoop();

private:
	QThread* thread_ = nullptr;

	Pomidoro* pomidoro_ = nullptr;
};

Q_DECLARE_METATYPE(ThreadController);

#endif // THREADCONTROLLER_H
