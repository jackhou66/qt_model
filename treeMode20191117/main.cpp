#include "Treemode20191117.h"
#include <QtWidgets/QApplication>
#include  <QTranslator>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTranslator qtTranslator;

	qtTranslator.load("treemode20191117_zh.qm");
	a.installTranslator(&qtTranslator);
	TreeMode20191117 w;
	w.show();
	return a.exec();
}
