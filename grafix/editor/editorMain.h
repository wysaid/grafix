﻿/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-6-3
*/

#ifndef _EDITOR_MAIN_H_
#define _EDITOR_MAIN_H_

#include "main.h"

#include "ui_editorWindow.h"

class GrafixEditorWindow : public QMainWindow
{
	Q_OBJECT

public:
	GrafixEditorWindow(QWidget* parent = 0);
	~GrafixEditorWindow();

protected:
	void init();

protected slots:
	void backtoHomePage();
	
private:
	Ui::EditorWindowClass m_ui;
};


#endif