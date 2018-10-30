#include <QApplication>
#include <tomato.h>

int main(int argc, char *argv[])
{
 QApplication a(argc, argv);
 Tomato w(&a);

 return a.exec();
}
