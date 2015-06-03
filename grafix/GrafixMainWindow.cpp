/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-6-3
*/

#include "GrafixMainWindow.h"

#include "editor/editorMain.h"
#include "collage/collageMain.h"
#include "batch/batchMain.h"

GrafixMainWindow::GrafixMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	m_ui.setupUi(this);
	setWindowFlags(Qt::WindowCloseButtonHint);
	setFixedSize(size());
	init();
}

GrafixMainWindow::~GrafixMainWindow()
{
	QApplication::quit();
}

void GrafixMainWindow::init()
{
	connect(m_ui.editBtn, SIGNAL(clicked()), SLOT(startEditor()));
	connect(m_ui.collageBtn, SIGNAL(clicked()), SLOT(startCollage()));
	connect(m_ui.batchBtn, SIGNAL(clicked()), SLOT(startBatch()));
}

void GrafixMainWindow::startEditor()
{
	CGE_LOG_INFO("startEditor...\n");

	hide();
	GrafixEditorWindow* editorWindow = new GrafixEditorWindow;
	editorWindow->show();
}

void GrafixMainWindow::startCollage()
{
	CGE_LOG_INFO("startCollage...\n");
}

void GrafixMainWindow::startBatch()
{
	CGE_LOG_INFO("startBatch...\n");
}