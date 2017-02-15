#include "qt_practice.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	WidgetPubTalk w;
	w.show();
	return a.exec();
}
