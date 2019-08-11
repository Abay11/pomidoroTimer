#include <QApplication>

#include "trayui.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	TrayUI* ui = new TrayUI;

	return a.exec();
}
