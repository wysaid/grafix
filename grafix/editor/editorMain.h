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

enum class EditorFunctions{
	Basic_Adjusts,
	Advanced_Adjusts,
	Prebuilt_Adjusts,
	Image_Crop,
	Image_Liquidation,
	Image_Frame,
	Stickers,
	Painting
};

class GrafixEditorWindow : public QMainWindow
{
	Q_OBJECT

public:
	GrafixEditorWindow(QWidget* parent = 0);
	~GrafixEditorWindow();

	void useCanvasContext();

	CGE::CGEImageHandler& getImageHandler();

protected:
	void init();

	// events
	void resizeEvent(QResizeEvent *);

	void commonMenuSwitch(EditorFunctions enumFunc);

protected slots:
	void backtoHomePage();

	void toggleBasicAdjusts();
	
private:
	Ui::EditorWindowClass m_ui;

	CanvasWidget* m_canvas;

	QWidget* m_menuWidget;
};


#endif