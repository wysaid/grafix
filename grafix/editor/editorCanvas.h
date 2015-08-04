/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-6-6
*/

#ifndef _EDITOR_CANVAS_H_
#define _EDITOR_CANVAS_H_

#include <QGLWidget>

#include "main.h"

//�����÷��� Shared Texture ����Ƶ���滻�� ���Բ�ֱ��ʹ�����û����ͷ�
class DisplaySprite : public CGE::Sprite2d
{
public:
	//	DisplaySprite(GLuint texID, int width, int height) : CGE::Sprite2d(CGE::SharedTexture())
	//	{
	//		m_texture.width = width;
	//		m_texture.height = height;
	//		m_textureID = texID;
	//	}

	DisplaySprite(CGE::SharedTexture& tex) : CGE::Sprite2d(tex)
	{
		m_textureID = tex.texID();
	}

	//ѡ����ͼƬ�� �л�
	void assignTexture(GLuint texID, int w, int h)
	{
		if(texID != 0)
			m_textureID = texID;
		m_texture.width = w;
		m_texture.height = h;
		m_program.bind();
		glUniform2f(m_halfTexLocation, m_texture.width / 2.0f, m_texture.height / 2.0f);
	}

	~DisplaySprite() {}

protected:
	void _drawFunc()
	{
		glBindBuffer(GL_ARRAY_BUFFER, CGE::CGEGlobalConfig::sVertexBufferCommon);
		glEnableVertexAttribArray(m_posAttribLocation);
		glVertexAttribPointer(m_posAttribLocation, 2, GL_FLOAT, false, 0, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}


protected:
	GLuint m_textureID;
};

class GrafixEditorWindow;

class GrafixEditorCanvas : public QGLWidget
{
	Q_OBJECT

public:
	explicit GrafixEditorCanvas(QWidget* parent = nullptr);
	~GrafixEditorCanvas();

	bool openImage(const QString& filename);

	CGE::CGEImageHandler& getHandler() { return  m_handler;	}

	DisplaySprite* getDisplaySprite() { return m_sprite; }

	void imageZoom(float scaling);

public slots:

	void setToOriginImage();
	void setToCurrentImage();

	void restoreImage();
	void fitImage();

	void imageZoomIn();
	void imageZoomOut();

	void bgDefault();
	void bgWhite();
	void bgBlack();
	void bgGray();

	void copyImgToClipBoard();
	void saveImage();
	void saveImageAs();

protected:
	void paintGL();
	void initializeGL();
	void resizeGL(int w, int h);
	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void wheelEvent(QWheelEvent *);
	void keyReleaseEvent(QKeyEvent *);

	void dragEnterEvent(QDragEnterEvent *);
	void dropEvent(QDropEvent *);

	void contextMenuEvent(QContextMenuEvent *);

	static CGEConstString paramTexSizeName;

	void setContextMenuIcons();

	void fixSpritePos();

private:
	DisplaySprite* m_sprite;
	int m_lastX, m_lastY;
	bool m_isMoving;

	GLint m_bgTextureLocation;
	GLuint m_posAttribLocation;
	CGE::ProgramObject* m_program;
	CGE::SharedTexture m_bgTexture;

	CGE::CGEImageHandler m_handler;	
	CGE::Vec4f m_bgColor;
	QMenu* m_contextMenu;
	QAction* m_bgActive;

	GrafixEditorWindow* m_editorWindow;
};

CGE::SharedTexture genSharedTextureWidthImageName(const char* filename, GLenum filter = GL_LINEAR);



#endif