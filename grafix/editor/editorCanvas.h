/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-6-6
*/

#ifndef _EDITOR_CANVAS_H_
#define _EDITOR_CANVAS_H_

#include <QGLWidget>

#include "main.h"

//特殊用法， Shared Texture 将被频繁替换， 所以不直接使用引用或者释放
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

	//选择新图片， 切换
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
		//		glUniform1i(m_textureLocation, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}


protected:
	GLuint m_textureID;
};

class CanvasWidget : public QGLWidget
{
	Q_OBJECT

public:
	explicit CanvasWidget(QWidget* parent = nullptr);
	~CanvasWidget();

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

	static CGEConstString paramTexSizeName;

private:
	DisplaySprite* m_sprite;
	int m_lastX, m_lastY;
	bool m_isMoving;

	GLint m_bgTextureLocation;
	GLuint m_posAttribLocation;
	CGE::ProgramObject* m_program;
	CGE::SharedTexture m_bgTexture;

	CGE::CGEImageHandler m_handler;	
};

CGE::SharedTexture genSharedTextureWidthImageName(const char* filename, GLenum filter = GL_LINEAR);



#endif