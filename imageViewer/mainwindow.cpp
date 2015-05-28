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
#include <QContextMenuEvent>
#include <QMenu>
#include <QClipboard>

#define MID(n, minValue, maxValue) std::min(std::max(n, minValue), maxValue)

MainWindow::MainWindow(const QString& imageFile, QWidget *parent)
	: QMainWindow(parent), m_quitTimer(this), m_scalingTimer(this), m_scalingLabel(this), m_imageScaling(1.0f), m_isTracking(false), m_forceMotion(false), m_notQuitThisTime(true)
{
	m_screenSize = QApplication::desktop()->size();
	setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setFocusPolicy(Qt::TabFocus);
	init(imageFile);
	setAcceptDrops(true);
	setMouseTracking(true);
	setCursor(Qt::OpenHandCursor);
	setContextMenuPolicy(Qt::DefaultContextMenu);

	connect(&m_quitTimer, SIGNAL(timeout()), SLOT(quitViewer()));
	connect(&m_scalingTimer, SIGNAL(timeout()), SLOT(scalingLabelFadeout()));
	
	m_scalingLabel.setFixedSize(100, 30);
	m_scalingLabel.setText("100%");
	m_scalingLabel.setStyleSheet("background-color:rgba(30, 30, 30, 150);color:#fff;font-size:30px;font-weight:blod;border-radius:10px;");
	m_scalingLabel.setAlignment(Qt::AlignCenter);
	m_scalingLabel.setEnabled(false);
	m_scalingLabel.setFocusPolicy(Qt::FocusPolicy::NoFocus);
	m_scalingLabel.hide();
}

MainWindow::~MainWindow()
{
	quitViewer();
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
			if(m_image.width() < 600 || m_image.height() < 400)
			{
				int w = std::max(m_image.width(), 600);
				int h = std::max(m_image.height(), 400);

				setFixedSize(w, h);

				auto&& newSz = (size() - m_image.size()) / 2;

				m_imageScaling = 1.0f;
				m_imageShowArea.setRect(newSz.width(), newSz.height(), m_image.width(), m_image.height());
			}
			else
			{
				setFixedSize(m_image.size());
				m_imageScaling = 1.0f;
				m_imageShowArea = m_image.rect();
				
			}
		}
		else
		{
			setFixedSize(m_screenSize);
			m_imageScaling = std::min(m_screenSize.width() / (float)m_image.width(), m_screenSize.height() / (float)m_image.height());
			auto&& newSize = m_image.size() * m_imageScaling;
			auto&& diffSize = (m_screenSize - newSize) / 2;
			m_imageShowArea = QRect(diffSize.width(), diffSize.height(), newSize.width(), newSize.height());
		}
		
		m_imageOutofRange = false;
		auto&& sz = (m_screenSize - size()) / 2;
		setGeometry(sz.width(), sz.height(), width(), height());
		CGE_LOG_INFO("Image Size: %d x %d, View Area: x: %d, y: %d, w:%d, h: %d\n", m_image.width(), m_image.height(), m_imageShowArea.left(), m_imageShowArea.top(), m_imageShowArea.width(), m_imageShowArea.height());
		m_scalingLabel.move((width() - m_scalingLabel.width()) / 2, (height() - m_scalingLabel.height()) / 2);
		raise();
		update();
		return true;
	}

	return false;
}

void MainWindow::imageZoom(float scaling, const QPoint& pos)
{
	auto&& oldPos = m_imageShowArea.topLeft();
	auto&& newPos = (oldPos - pos) * (scaling / m_imageScaling) + pos;
	auto&& newSz = m_image.size() * scaling;
	m_imageShowArea.setRect(newPos.x(), newPos.y(), newSz.width(), newSz.height());

	if(newSz.width() <= width() && newSz.height() <= height())
		m_imageOutofRange = false;
	else
		m_imageOutofRange = true;

	fixViewArea();
	m_imageScaling = scaling;
	m_scalingLabel.setText(tr("%1%").arg(int(m_imageScaling*100)));
	m_scalingLabel.show();
	m_scalingTimer.start(1000);
	update();
}

void MainWindow::quitViewer()
{
	QApplication::quit();
}

void MainWindow::scalingLabelFadeout()
{
	m_scalingLabel.hide();
//	update();
}

void MainWindow::editImage()
{
	CGE_LOG_INFO("Start Editing...\n");
}

void MainWindow::copyImage()
{
	CGE_LOG_INFO("Copying Image...\n");
	auto clipboard = QApplication::clipboard();
	clipboard->setImage(m_image);
}

void MainWindow::paintEvent(QPaintEvent *)
{
	if(m_image.isNull())
	{
		return;
	}

	QPainter painter(this);
	painter.setRenderHint(QPainter::SmoothPixmapTransform);
	painter.fillRect(rect(), QColor(0, 0, 0, 0x50));
	painter.drawImage(m_imageShowArea , m_image);
}

void MainWindow::wheelEvent(QWheelEvent *e)
{
	float newScaling = m_imageScaling * ((e->delta() > 0) ? 1.1f : 0.9f);
	newScaling = MID(newScaling, 0.0f, 20.0f);
	if(abs(newScaling - 1.0f) < 0.05f)
		newScaling = 1.0f;
	else if(newScaling < 0.01f)
		newScaling = 0.01f;
	imageZoom(newScaling, e->pos());
	CGE_LOG_INFO("Current Scaling: %g\n", newScaling);
	m_notQuitThisTime = true;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
	if(e->button() != Qt::MouseButton::LeftButton)
	{
		return;
	}

	if(e->y() < 50 || !m_imageOutofRange)
	{
		setCursor(Qt::SizeAllCursor);
		m_forceMotion = true;
	}
	else
	{
		setCursor(Qt::ClosedHandCursor);
		m_forceMotion = false;
	}
	m_lastPos = e->globalPos();
	m_hasMotion = false;
	m_isTracking = true;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
	if(e->button() != Qt::MouseButton::LeftButton)
	{
		return;
	}

	if(e->y() >= 50 && m_imageOutofRange)
		setCursor(Qt::ClosedHandCursor);

	m_isTracking = false;
	if(m_notQuitThisTime)
	{
		m_notQuitThisTime = false;
	}
	else if(!m_hasMotion)
	{
		quitViewer();
	}

	if(m_imageOutofRange)
	{
		fixViewArea();
		update();
	}
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
	if(!m_isTracking)
	{
		if(e->y() < 50 || !m_imageOutofRange)
		{
			if(cursor().shape() != Qt::SizeAllCursor)
				setCursor(Qt::SizeAllCursor);
		}
		else if(cursor().shape() != Qt::OpenHandCursor)
		{
			setCursor(Qt::OpenHandCursor);
		}
		return;
	}

	auto&& evPos = e->globalPos();
	if(m_imageOutofRange && !m_forceMotion)
	{
		auto&& newPos = (m_imageShowArea.topLeft() + (evPos - m_lastPos));
		m_imageShowArea.setRect(newPos.x(), newPos.y(), m_imageShowArea.width(), m_imageShowArea.height());
		fixViewArea();
		update();
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
	m_notQuitThisTime = true;
	setWindowOpacity(0.85);
	m_quitTimer.start(3600000);
}

void MainWindow::focusInEvent(QFocusEvent *)
{
	setWindowOpacity(1.0);
	m_quitTimer.stop();
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

void MainWindow::contextMenuEvent(QContextMenuEvent *e)
{
	if(!underMouse())
		return;

	QMenu menu(this);
	menu.addAction(QString::fromLocal8Bit("复制图片"), this, SLOT(copyImage()));
	menu.addAction(QString::fromLocal8Bit("编辑图片"), this, SLOT(editImage()));
	menu.addAction(QString::fromLocal8Bit("退出"), this, SLOT(quitViewer()));
	menu.exec(e->globalPos());
}

void MainWindow::fixViewArea()
{
	if(m_imageShowArea.width() <= width())
	{
		m_imageShowArea.setRect((width() - m_imageShowArea.width()) / 2, m_imageShowArea.top(), m_imageShowArea.width(), m_imageShowArea.height());
	}
	else
	{
		if(m_imageShowArea.left() > 0)
			m_imageShowArea.setRect(0, m_imageShowArea.top(), m_imageShowArea.width(), m_imageShowArea.height());
		else if(m_imageShowArea.right() < width())
			m_imageShowArea.setRect(width() - m_imageShowArea.width(), m_imageShowArea.top(), m_imageShowArea.width(), m_imageShowArea.height());
	}

	if(m_imageShowArea.height() <= height())
	{
		m_imageShowArea.setRect(m_imageShowArea.left(), (height() - m_imageShowArea.height()) / 2, m_imageShowArea.width(), m_imageShowArea.height());
	}
	else
	{
		if(m_imageShowArea.top() > 0)
			m_imageShowArea.setRect(m_imageShowArea.left(), 0, m_imageShowArea.width(), m_imageShowArea.height());
		else if(m_imageShowArea.bottom() < height())
			m_imageShowArea.setRect(m_imageShowArea.left(), height() - m_imageShowArea.height(), m_imageShowArea.width(), m_imageShowArea.height());
	}
}