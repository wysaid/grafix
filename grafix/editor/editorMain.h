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

	void enableWaitingStatus(bool);

	// events
	void resizeEvent(QResizeEvent *);

protected slots:
	void backtoHomePage();
	
private:
	QTimer m_waitingTimer;
	QLabel* m_waitingAnim;

private:
	Ui::EditorWindowClass m_ui;

	GrafixEditorCanvas* m_canvas;
};


#endif