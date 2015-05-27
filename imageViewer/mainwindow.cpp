/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-5-27
*/

#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include <QDesktopWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QMessageBox>

MainWindow::MainWindow(const QString& imageFile, QWidget *parent)
	: QMainWindow(parent), m_imageScaling(1.0f)
{
	m_screenSize = QApplication::desktop()->size();
	setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	init(imageFile);
	setAcceptDrops(true);
}

MainWindow::~MainWindow()
{

}

void MainWindow::init(const QString& imageFile)
{
	if(!imageFile.isEmpty())
	{
		m_image = QImage(imageFile);
	}

	if(m_image.isNull())
	{
		m_image = QImage(":grafix/res/logo.png");
	}

	if(!m_image.isNull())
	{
		if(m_image.width() < m_screenSize.width() &&
			m_image.height() < m_screenSize.height())
		{
			setFixedSize(m_image.size());
			m_imageScaling = 1.0f;
			m_imageShowArea = m_image.rect();
		}
		else
		{
			setFixedSize(m_screenSize);
			m_imageScaling = std::min(m_screenSize.width() / (float)m_image.width(), m_screenSize.height() / (float)m_image.height());
			QSize newSize = m_image.size() * m_imageScaling;
			QSize diffSize = (m_screenSize - newSize) / 2.0;
			m_imageShowArea = QRect(diffSize.width(), diffSize.height(), newSize.width(), newSize.height());
		}
	}
}

bool MainWindow::openImage(const QString& filename)
{
	perror(filename.toLocal8Bit());
	return false;
}

void MainWindow::imageZoom(float scaling)
{

}

void MainWindow::paintEvent(QPaintEvent *)
{
	if(m_image.isNull())
	{
		return;
	}

	QPainter painter(this);
	painter.drawImage(m_imageShowArea , m_image);
}

void MainWindow::wheelEvent(QWheelEvent *)
{

}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
	m_lastPos = e->globalPos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{

}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
	auto&& evPos = e->globalPos();
	move(this->pos() + (evPos - m_lastPos));
	m_lastPos = evPos;
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
	switch (e->key())
	{
	case Qt::Key_Escape:
		QApplication::quit();
		break;
	default:
		break;
	}
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
	auto&& mimedata = e->mimeData();
	perror(mimedata->text().toLocal8Bit());
	if(mimedata->hasImage() || mimedata->hasText())
	{
		e->acceptProposedAction();
	}
}

void MainWindow::dropEvent(QDropEvent *e)
{
	auto names = e->mimeData()->urls();
	if(names.empty())
		return;
	auto url = names.first();
	auto filename = url.toLocalFile();
	if(filename.isEmpty())
	{
		QMessageBox::warning(this, "Invalid Image!", QString::fromLocal8Bit("%1 不是本地图像文件!").arg(url.toString()));
		return ;
	}
	openImage(filename);
}