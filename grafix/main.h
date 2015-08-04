/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-6-3
*/

#ifndef _MAIN_H_
#define _MAIN_H_

#include <QtWidgets/QMainWindow>
#include <QMenu>
#include <QTimer>
#include <QLabel>
#include <QMovie>
#include "cge.h"

#define GF_STR QString::fromLocal8Bit

class GrafixMainWindow;

class GlobalStaticVars
{
public:
	static GrafixMainWindow* mainWindow;

	static void showMainWindow();
};

class GrafixLoadingWindow : public QWidget
{
	Q_OBJECT
public:
	GrafixLoadingWindow(QWidget* parent = nullptr);
	~GrafixLoadingWindow();

protected:
	QLabel m_label;
	//Q
};

#endif