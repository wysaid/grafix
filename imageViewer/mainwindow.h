/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-5-27
*/

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QtWidgets/QMainWindow>
#include <QString>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QLabel>

#include "main.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(const QString& imageFile, QWidget *parent = 0);
	~MainWindow();

	bool openImage(const QString& filename);

	void imageZoom(float scaling, const QPoint& pnt);

protected slots:

	void quitViewer();
	void scalingLabelFadeout();

	void editImage();
	void copyImage();

protected:

	void init(const QString& imageFile);

	void paintEvent(QPaintEvent *);
	
	void wheelEvent(QWheelEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void keyReleaseEvent(QKeyEvent *);

	void focusOutEvent(QFocusEvent *);
	void focusInEvent(QFocusEvent *);

	void dragEnterEvent(QDragEnterEvent *);
	void dropEvent(QDropEvent *);

	void contextMenuEvent(QContextMenuEvent *);

	void fixViewArea();

private:
	QTimer m_quitTimer, m_scalingTimer;
	QImage m_image;
	QLabel m_scalingLabel;

private:
	
	QRect m_imageShowArea;
	QPoint m_lastPos;
	QSize m_screenSize;
	float m_imageScaling;
	bool m_hasMotion, m_isTracking, m_forceMotion;
	bool m_notQuitThisTime, m_imageOutofRange;
};

#endif // MAINWINDOW_H
