#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowFlags(Qt::WindowCloseButtonHint);
	ui.setupUi(this);
}

MainWindow::~MainWindow()
{

}
