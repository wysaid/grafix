/*
 @ Author: wysaid
 @ Blog: blog.wysaid.org
 @ Date: 2015-6-6
*/

#include "editorCanvas.h"


#include <QMessageBox>
#include <QMouseEvent>
#include <QMimeData>

#define CLOCK_TRANSLATE (CLOCKS_PER_SEC / 1000)

CGE::SharedTexture genSharedTextureWidthImageName(const char* filename, GLenum filter)
{
	QImage&& img = QImage(filename).convertToFormat(QImage::Format_RGBA8888, Qt::ColorOnly);
	if(img.width() < 1)
	{
		CGE_LOG_ERROR("Invalid image!\n");
		return CGE::SharedTexture(0, 0, 0);
	}
	GLuint texID = CGE::cgeGenTextureWithBuffer(img.bits(), img.width(), img.height(), GL_RGBA, GL_UNSIGNED_BYTE, 4, 0, filter);
	return CGE::SharedTexture(texID, img.width(), img.height());
}

//////////////////////////////////////////////////////////////////////////

static CGEConstString s_vshBackGround = CGE_SHADER_STRING(

attribute vec4 position;
varying vec2 texCoord;

uniform vec2 texSize;

void main()
{
	gl_Position = position;
	texCoord = vec2(position.x + 1.0, 1.0 - position.y) / 2.0 * texSize;
});

static CGEConstString s_fshBackGround = CGE_SHADER_STRING_PRECISION_L(

varying vec2 texCoord;
uniform sampler2D texture;

void main()
{
	gl_FragColor = texture2D(texture, fract(texCoord));
});


//////////////////////////////////////////////////////////////////////////

CGEConstString CanvasWidget::paramTexSizeName = "texSize";

CanvasWidget::CanvasWidget(QWidget* parent) : QGLWidget(parent), m_isMoving(false), m_program(nullptr), m_contextMenu(nullptr)
{	
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoSystemBackground);
	setAutoBufferSwap(false);
	setCursor(Qt::CursorShape::OpenHandCursor);
	setFocusPolicy(Qt::ClickFocus);
	setAcceptDrops(true);
	setContextMenuPolicy(Qt::DefaultContextMenu);
}

CanvasWidget::~CanvasWidget()
{
	makeCurrent();
	delete m_program;
	CGE_LOG_INFO("Editor Canvas destruct...\n");
}

void CanvasWidget::paintGL()
{
	//The iOS device would have a framebuffer_oes object that is already binding ok.
#ifndef Q_OS_IOS
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif

	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, width() * devicePixelRatio(), height() * devicePixelRatio());

	if(m_program != nullptr && m_bgColor[3] <= 0.0f)
	{
		glDisable(GL_BLEND);
		m_program->bind();
		m_bgTexture.bindToIndex(0);

		glBindBuffer(GL_ARRAY_BUFFER, CGE::CGEGlobalConfig::sVertexBufferCommon);
		glEnableVertexAttribArray(m_posAttribLocation);
		glVertexAttribPointer(m_posAttribLocation, 2, GL_FLOAT, false, 0, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}
	else
	{
		glClearColor(m_bgColor[0], m_bgColor[1], m_bgColor[2], m_bgColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	if(m_sprite)
	{
		glEnable(GL_BLEND);	
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		m_sprite->render();
	}
	swapBuffers();
	cgeCheckGLError("paintGL");
}

void CanvasWidget::initializeGL()
{
#ifdef CGE_USE_COMPATIBLE_GL_FUNCTIONS
	g_glFunctions = this->context()->functions();
#endif

	CGE::cgePrintGLInfo();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	cgeInitialize(width(), height(), CGE::CGEGlobalConfig::InitArguments(CGE::CGEGlobalConfig::CGE_INIT_DEFAULT & ~CGE::CGEGlobalConfig::CGE_INIT_SPRITEBUILTIN));

	CGE::SharedTexture t = genSharedTextureWidthImageName(":grafix/res/logo.png");

	m_handler.initWithTexture(t.texID(), t.width, t.height, CGE::CGE_FORMAT_RGBA_INT8, true);

	m_sprite = new DisplaySprite(t);
	m_sprite->moveTo(300, 300);

	m_program = new CGE::ProgramObject;
	m_posAttribLocation = 0;
	m_program->bindAttribLocation("position", m_posAttribLocation);
	if(m_program->initWithShaderStrings(s_vshBackGround, s_fshBackGround))
	{
		m_bgTexture = genSharedTextureWidthImageName(":grafix/res/bg.png", GL_NEAREST);
		m_program->bind();
		m_program->sendUniformf(paramTexSizeName, width() * (float)m_bgTexture.width, height() * (float)m_bgTexture.height);
		m_bgTextureLocation = m_program->uniformLocation("texture");
	}
	else
	{
		delete m_program;
		m_program = nullptr;
		CGE_LOG_ERROR("初始化背景失败, 将以黑色显示背景");
	}

	//	fitImage();
}

//兼容retina 屏幕， 能使用经过deviceRatio 转换之后的 w 和 h
void CanvasWidget::resizeGL(int w, int h)
{
	m_sprite->setCanvasSize(width(), height());
	if(m_program != nullptr)
	{
		m_program->bind();
		m_program->sendUniformf(paramTexSizeName, width() / (float)m_bgTexture.width, height() / (float)m_bgTexture.height);
	}
}

void CanvasWidget::mousePressEvent(QMouseEvent *e)
{
	if(e->button() != Qt::MouseButton::LeftButton)
		return;
	setCursor(Qt::CursorShape::ClosedHandCursor);
	m_isMoving = true;
	m_lastX = e->globalX();
	m_lastY = e->globalY();
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *e)
{
	if(m_isMoving)
	{
		auto px = e->globalX(), py = e->globalY();
		m_sprite->move(px - m_lastX, py - m_lastY);
		m_lastX = px;
		m_lastY = py;
		updateGL();
	}
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *e)
{
	setCursor(Qt::CursorShape::OpenHandCursor);
	m_isMoving = false;
}

void CanvasWidget::wheelEvent(QWheelEvent *e)
{
	auto scaling = 1.0f + e->delta() / 2000.0f;

	imageZoom(scaling);

	auto s = m_sprite->getScaling();

	s[0] = CGE::CGE_MID(s[0], 0.05f, 5.0f);
	s[1] = CGE::CGE_MID(s[1], 0.05f, 5.0f);

	m_sprite->scaleTo(s[0], s[1]);
	updateGL();
}

void CanvasWidget::keyReleaseEvent(QKeyEvent *e)
{
	switch (e->key())
	{
	case Qt::Key_Space:
		fitImage();
		break;
	case Qt::Key_Enter: case Qt::Key_Return:
		restoreImage();
		break;
	default:
		break;
	}
}

void CanvasWidget::dragEnterEvent(QDragEnterEvent *e)
{
	auto mimedata = e->mimeData();
	if(mimedata->hasImage() || mimedata->hasText())
	{
		e->acceptProposedAction();
	}
}

void CanvasWidget::dropEvent(QDropEvent *e)
{
	auto names = e->mimeData()->urls();
	if(names.empty())
		return;
	auto url = names.first();
	auto filename = url.toLocalFile();
	if(filename.isEmpty())
	{
		QMessageBox::warning(this, "Invalid Image!", GF_STR("%1 不是本地图像文件!").arg(url.toString()));
		return ;
	}
	openImage(filename);
}

void CanvasWidget::contextMenuEvent(QContextMenuEvent *e)
{
	if(!underMouse())
		return;

	if(m_contextMenu == nullptr)
	{
		m_contextMenu = new QMenu(this);
		QMenu* bgMenu = new QMenu(m_contextMenu);

		bgMenu->setTitle(GF_STR("背景颜色"));
		bgMenu->addAction(GF_STR("默认"), this, SLOT(bgDefault()));
		bgMenu->addAction(GF_STR("白色"), this, SLOT(bgWhite()));
		bgMenu->addAction(GF_STR("黑色"), this, SLOT(bgBlack()));
		bgMenu->addAction(GF_STR("灰色"), this, SLOT(bgGray()));
		auto&& bgActions = bgMenu->actions();

		for(auto ac : bgActions)
		{
			ac->setCheckable(true);
		}
		m_bgActive = bgActions.first();
		m_bgActive->setChecked(true);
		m_contextMenu->addAction(GF_STR("复制"), this, SLOT(copyImgToClipBoard()));
		m_contextMenu->addAction(GF_STR("保存"), this, SLOT(saveImage()));
		m_contextMenu->addAction(GF_STR("另存为"), this, SLOT(saveImageAs()));
		m_contextMenu->addSeparator();
		m_contextMenu->addMenu(bgMenu);
	}
	m_contextMenu->exec(e->globalPos());
}

bool CanvasWidget::openImage(const QString& filename)
{
	CGE_LOG_INFO("正在打开图片 %s ...\n", (const char*)filename.toLocal8Bit());
	QImage img(filename);

#ifdef Q_OS_WIN
	const float sMaxImageSize = 30000000.0f;
#else 
	const float sMaxImageSize = 5000000.0f;
#endif

	const float sMaxTexSize = CGE::cgeGetMaxTextureSize();

	if(img.width() < 1 || img.height() < 1)
	{
		QMessageBox::information(this, GF_STR("无法打开图片"), GF_STR("%1 无法被识别为正确可支持的图片，无法打开， 请重新选择!").arg(filename));
		return false;
	}

	if(img.width() * img.height() > sMaxImageSize)
	{
		CGE_LOG_ERROR("%s", (const char*)GF_STR("你选择的图片尺寸为 %1 * %2, 总共 %3M像素, 尺寸过大不利于实时处理， 为了保证内存占用不至于过大以及不影响调整速度， 现将图片裁剪至 %4M像素以内.\n").arg(img.width()).arg(img.height()).arg(img.width() * img.height() / 1e6f).arg(sMaxImageSize / 1e6f).toLocal8Bit());
		float ratio = sqrtf(sMaxImageSize / (img.width() * img.height()));
		QSize s(img.width() * ratio, img.height() * ratio);
		img = img.scaled(s, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	}	

	if(img.format() != QImage::Format_RGBA8888)
		img = img.convertToFormat(QImage::Format_RGBA8888, Qt::ColorOnly);

	CGE_LOG_INFO("图片打开成功...\n");
	makeCurrent();
	if(m_handler.initWithRawBufferData(img.bits(), img.width(), img.height(), CGE::CGE_FORMAT_RGBA_INT8, true))
	{
		if(m_handler.getFilterNum() != 0)
			m_handler.processingFilters();
		auto sz = m_handler.getOutputFBOSize();
		m_sprite->assignTexture(m_handler.getTargetTextureID(), sz.width, sz.height);
		updateGL();
		return true;
	}
	else
	{
		QMessageBox::information(this, GF_STR("未知错误"), GF_STR("打开图片失败"));
		return false;
	}
}

void CanvasWidget::setToOriginImage()
{
	if(m_sprite != nullptr)
	{
		makeCurrent();
		auto sz = m_handler.getOutputFBOSize();
		m_sprite->assignTexture(m_handler.getSourceTextureID(), sz.width, sz.height);
		updateGL();
	}
	CGE_LOG_INFO("setToOriginImage\n");
}

void CanvasWidget::setToCurrentImage()
{
	if(m_sprite != nullptr)
	{
		makeCurrent();
		auto sz = m_handler.getOutputFBOSize();
		m_sprite->assignTexture(m_handler.getTargetTextureID(), sz.width, sz.height);
		updateGL();
	}
	CGE_LOG_INFO("setToCurrentImage\n");
}

void CanvasWidget::restoreImage()
{
	m_sprite->moveTo(width() / 2.0f, height() / 2.0f);
	m_sprite->scaleTo(1.0f, 1.0f);
	updateGL();
	CGE_LOG_INFO("restoreImage\n");
}

void CanvasWidget::fitImage()
{
	auto& tex = m_sprite->getTexture();
	auto scaling = CGE::CGE_MIN((float)width() / tex.width, (float)height() / tex.height);
	m_sprite->scaleTo(scaling, scaling);
	m_sprite->moveTo(width() / 2.0f, height() / 2.0f);
	updateGL();
}

void CanvasWidget::imageZoom(float scaling)
{
	m_sprite->scale(scaling, scaling);
}

void CanvasWidget::imageZoomIn()
{
	imageZoom(0.9f);
	updateGL();
}

void CanvasWidget::imageZoomOut()
{
	imageZoom(1.1f);
	updateGL();
}

void CanvasWidget::bgDefault()
{
	m_bgColor[3] = -1.0f; //使用格子
	m_bgActive->setChecked(false);
	QAction* ac = dynamic_cast<QAction*>(sender());
	if(ac)
	{
		ac->setChecked(true);
		m_bgActive = ac;
	}
	updateGL();
}

void CanvasWidget::bgWhite()
{
	m_bgColor = CGE::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	m_bgActive->setChecked(false);
	QAction* ac = dynamic_cast<QAction*>(sender());
	if(ac)
	{
		ac->setChecked(true);
		m_bgActive = ac;
	}
	updateGL();
}

void CanvasWidget::bgBlack()
{
	m_bgColor = CGE::Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	m_bgActive->setChecked(false);
	QAction* ac = dynamic_cast<QAction*>(sender());
	if(ac)
	{
		ac->setChecked(true);
		m_bgActive = ac;
	}
	updateGL();
}

void CanvasWidget::bgGray()
{
	m_bgColor = CGE::Vec4f(0.4f, 0.4f, 0.4f, 1.0f);
	m_bgActive->setChecked(false);
	QAction* ac = dynamic_cast<QAction*>(sender());
	if(ac)
	{
		ac->setChecked(true);
		m_bgActive = ac;
	}
	updateGL();
}

void CanvasWidget::copyImgToClipBoard()
{

}

void CanvasWidget::saveImage()
{

}

void CanvasWidget::saveImageAs()
{

}

void CanvasWidget::fixSpritePos()
{

}