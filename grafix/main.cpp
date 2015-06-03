/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-6-3
*/

#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
