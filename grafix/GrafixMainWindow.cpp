/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-6-3
*/

#include "GrafixMainWindow.h"

GrafixMainWindow::GrafixMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::WindowCloseButtonHint);
	setFixedSize(size());
}

GrafixMainWindow::~GrafixMainWindow()
{

}
