/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-6-3
*/

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "main.h"
#include "ui_mainwindow.h"

class GrafixMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	GrafixMainWindow(QWidget *parent = 0);
	~GrafixMainWindow();

private:
	Ui::MainWindowClass ui;
};

#endif // MAINWINDOW_H
