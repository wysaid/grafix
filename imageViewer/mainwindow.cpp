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

#define MID(n, minValue, maxValue) std::min(std::max(n, minValue), maxValue)

MainWindow::MainWindow(const QString& imageFile, QWidget *parent)
	: QMainWindow(parent), m_imageScaling(1.0f), m_focusOut(true)
{
	m_screenSize = QApplication::desktop()->size();
	setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setFocusPolicy(Qt::TabFocus);
	init(imageFile);
	setAcceptDrops(true);
	setCursor(Qt::CursorShape::OpenHandCursor);
	connect(&m_timer, SIGNAL(timeout()), SLOT(quitViewer()));
	//QPalette pal = palette();
	//pal.setColor(QPalette::Background, QColor(0, 0, 0, 0x10));
	//setPalette(pal);
}

MainWindow::~MainWindow()
{

}

void MainWindow::init(const QString& imageFile)
{
	if(!imageFile.isEmpty())
	{
		openImage(imageFile);
	}

	if(m_image.isNull())
	{
		openImage(":grafix/res/logo.png");
	}
}

bool MainWindow::openImage(const QString& filename)
{
	m_image = QImage(filename);

	if(!m_image.isNull())
	{
		if(m_image.width() <= m_screenSize.width() &&
			m_image.height() <= m_screenSize.height())
		{
			setFixedSize(m_image.size());
			m_imageScaling = 1.0f;
			m_imageShowArea = m_image.rect();
			m_imageOutofRange = false;
		}
		else
		{
			setFixedSize(m_screenSize);
			m_imageScaling = std::min(m_screenSize.width() / (float)m_image.width(), m_screenSize.height() / (float)m_image.height());
			auto&& newSize = m_image.size() * m_imageScaling;
			auto&& diffSize = (m_screenSize - newSize) / 2;
			m_imageShowArea = QRect(diffSize.width(), diffSize.height(), newSize.width(), newSize.height());
			m_imageOutofRange = true;
		}
		
		auto&& sz = (m_screenSize - size()) / 2;
		setGeometry(sz.width(), sz.height(), width(), height());
		update();
		return true;
	}

	return false;
}

void MainWindow::imageZoom(float scaling)
{
	auto&& sz = m_image.size();
	auto&& newSz = sz * scaling;
	auto&& viewSz = (size() - newSz) / 2;
	m_imageShowArea.setRect(viewSz.width(), viewSz.height(), newSz.width(), newSz.height());

	if(newSz.width() <= width() && newSz.height() <= height())
		m_imageOutofRange = false;
	else
		m_imageOutofRange = true;

	update();
}

void MainWindow::quitViewer()
{
	QApplication::quit();
}

void MainWindow::paintEvent(QPaintEvent *)
{
	if(m_image.isNull())
	{
		return;
	}

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.drawImage(m_imageShowArea , m_image);
}

void MainWindow::wheelEvent(QWheelEvent *e)
{
	m_imageScaling *= (e->delta() > 0) ? 1.1 : 0.9;
	m_imageScaling = MID(m_imageScaling, 0.0f, 20.0f);
	imageZoom(m_imageScaling);
	CGE_LOG_INFO("Current Scaling: %g\n", m_imageScaling);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
	setCursor(Qt::CursorShape::OpenHandCursor);
	m_lastPos = e->globalPos();
	m_hasMotion = false;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
	setCursor(Qt::CursorShape::ClosedHandCursor);

	if(m_focusOut)
	{
		m_focusOut = false;
	}
	else if(!m_hasMotion)
	{
		quitViewer();
	}
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
	auto&& evPos = e->globalPos();
	if(m_imageOutofRange)
	{
		move(m_imageShowArea.topLeft() + (evPos - m_lastPos));
	}
	else
	{
		move(this->pos() + (evPos - m_lastPos));
	}
	m_lastPos = evPos;
	m_hasMotion = true;
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
	switch (e->key())
	{
	case Qt::Key_Enter:
	case Qt::Key_Return:
	case Qt::Key_Space:
	case Qt::Key_Escape:
		quitViewer();
		break;
	default:
		break;
	}
}

void MainWindow::focusOutEvent(QFocusEvent *)
{
	m_focusOut = true;
	setWindowOpacity(0.7);
	m_timer.start(3600000);
}

void MainWindow::focusInEvent(QFocusEvent *)
{
	setWindowOpacity(1.0);
	m_timer.stop();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
	auto&& mimedata = e->mimeData();
	CGE_LOG_INFO("dragEvent: %s\n", mimedata->text().toLocal8Bit().constData());
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