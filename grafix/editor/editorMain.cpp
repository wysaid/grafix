/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-6-3
*/

#include "editorMain.h"

bool enableGLFunction(void* arg)
{
	if(arg)
	{
		((GrafixEditorWindow*)arg)->useCanvasContext();
		return true;
	}
	return false;
}

GrafixEditorWindow::GrafixEditorWindow(QWidget* parent) : m_menuWidget(nullptr)
{
	m_ui.setupUi(this);
	setMinimumSize(800, 500);
	init();
}

GrafixEditorWindow::~GrafixEditorWindow()
{
	CGE_LOG_INFO("~GrafixEditorWindow...\n");
}

void GrafixEditorWindow::init()
{
	m_ui.canvasView->hide();
	m_canvas = new CanvasWidget(centralWidget());
	CGE::cgeSetGLContextEnableFunction(enableGLFunction, this);
	m_canvas->setGeometry(m_ui.canvasView->geometry());
	connect(m_ui.homeBtn, SIGNAL(clicked()), SLOT(backtoHomePage()));
}

void GrafixEditorWindow::backtoHomePage()
{
	CGE_LOG_INFO("GrafixEditorWindow::backtoHomePage...\n");
	deleteLater();
	GlobalStaticVars::showMainWindow();
}

///////////// Events /////////////////////////////////

void GrafixEditorWindow::resizeEvent(QResizeEvent *)
{
	int w = width();
	int h = height();

	m_ui.leftView->setFixedHeight(h - m_ui.leftView->y());
	m_ui.secondMenuView->setFixedHeight(m_ui.leftView->height() - 60);

	m_canvas->setFixedWidth(w - m_canvas->x() - 5);
	m_canvas->setFixedHeight(h - m_canvas->y() - 60);

	{
		auto&& g = m_ui.bottomToolView->geometry();
		m_ui.bottomToolView->setFixedWidth(w - m_ui.bottomToolView->x() - 20);
		m_ui.bottomToolView->setGeometry(g.x(), h - g.height() - 5, w - g.x() - 20, g.height());
	}
	
}

void GrafixEditorWindow::useCanvasContext()
{
	m_canvas->makeCurrent();
}

CGE::CGEImageHandler& GrafixEditorWindow::getImageHandler()
{
	return m_canvas->getHandler();

}

void GrafixEditorWindow::commonMenuSwitch(EditorFunctions enumFunc)
{

}

void GrafixEditorWindow::toggleBasicAdjusts()
{
	CGE_LOG_INFO("Basic adjusts clicked...\n");
	commonMenuSwitch(EditorFunctions::Basic_Adjusts);
}