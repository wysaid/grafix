/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-6-3
*/

#include "GrafixMainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GrafixMainWindow w;
	GlobalStaticVars::mainWindow = &w;
	w.show();
	return a.exec();
}

GrafixMainWindow* GlobalStaticVars::mainWindow;

void GlobalStaticVars::showMainWindow()
{
	if(mainWindow != nullptr)
		mainWindow->show();
}