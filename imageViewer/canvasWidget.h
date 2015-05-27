/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-5-27
*/

#ifndef _CANVASWIDGET_H_
#define _CANVASWIDGET_H_

#include <QtWidgets/QWidget>

class CanvasWidget : public QWidget
{
	Q_OBJECT
public:
	explicit CanvasWidget(QWidget* parent = nullptr);
	~CanvasWidget();

	bool openImage(const QString& filename);

	void imageZoom(float scaling);

protected:



};


#endif