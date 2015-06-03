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
