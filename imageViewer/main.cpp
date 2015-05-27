/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-5-27
*/

#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w(argc < 2 ? nullptr : argv[1]);
	w.show();
	return a.exec();
}
