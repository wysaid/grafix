/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-6-3
*/

#include "editor/editorMain.h"

GrafixEditorWindow::GrafixEditorWindow(QWidget* parent)
{
	m_ui.setupUi(this);
	init();
}

GrafixEditorWindow::~GrafixEditorWindow()
{
	CGE_LOG_INFO("~GrafixEditorWindow...\n");
}

void GrafixEditorWindow::init()
{
	m_ui.canvasView->hide();
	m_canvas = new CanvasWidget(this->centralWidget());
	m_canvas->setGeometry(m_ui.canvasView->geometry());

	connect(m_ui.homeBtn, SIGNAL(clicked()), SLOT(backtoHomePage()));
}

void GrafixEditorWindow::backtoHomePage()
{
	CGE_LOG_INFO("GrafixEditorWindow::backtoHomePage...\n");
	deleteLater();
	GlobalStaticVars::showMainWindow();
}