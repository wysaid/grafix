﻿/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-6-3
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
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