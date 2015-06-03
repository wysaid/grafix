/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-6-3
*/

#ifndef _MAIN_H_
#define _MAIN_H_

#include <QtWidgets/QMainWindow>
#include "cge.h"

class GrafixMainWindow;

class GlobalStaticVars
{
public:
	static GrafixMainWindow* mainWindow;

	static void showMainWindow();
};


#endif