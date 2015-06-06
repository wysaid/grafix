/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-6-3
*/

#ifndef _EDITOR_MAIN_H_
#define _EDITOR_MAIN_H_

#include "main.h"
#include "editorCanvas.h"

#include "ui_editorWindow.h"

class GrafixEditorWindow : public QMainWindow
{
	Q_OBJECT

public:
	GrafixEditorWindow(QWidget* parent = 0);
	~GrafixEditorWindow();

	void useCanvasContext();

protected:
	void init();

	// events
	void resizeEvent(QResizeEvent *);

protected slots:
	void backtoHomePage();
	
private:
	Ui::EditorWindowClass m_ui;

	CanvasWidget* m_canvas;
};


#endif