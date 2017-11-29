#include "colordetector.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ColorDetector w;
	w.show();
	return a.exec();
}
