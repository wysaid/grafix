/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-6-3
*/

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::WindowCloseButtonHint);
	setFixedSize(size());
}

MainWindow::~MainWindow()
{

}
