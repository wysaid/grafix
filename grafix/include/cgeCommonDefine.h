/*
* cgeCommonDefine.h
*
*  Created on: 2013-12-6
*      Author: Wang Yang
*        Mail: admin@wysaid.org
*/

#ifndef _CGECOMMONDEFINE_H_
#define _CGECOMMONDEFINE_H_

#ifdef GLEW_USED
#include "cgePlatform_GLEW.h"
#elif defined(ANDROID_NDK)
#include "cgePlatforms_ANDROID.h"
#elif defined(IOS_SDK)
#include "cgePlatform_IOS.h"
#elif defined(LIBCGE4QT_LIB)
#include "cgePlatform_QT.h"
#endif

#define CGE_VERSION "1.8.1"

#ifdef CGE_LOG_ERROR
#define cgeCheckGLError(name) CGE::_cgeCheckGLError(name, __FILE__, __LINE__);
#else
#define cgeCheckGLError(name)
#endif
#ifndef _CGE_GET_MACRO_STRING_HELP
#define _CGE_GET_MACRO_STRING_HELP(x) #x
#endif
#ifndef CGE_GET_MACRO_STRING
#define CGE_GET_MACRO_STRING(x) _CGE_GET_MACRO_STRING_HELP(x)
#endif
#define CGE_FLOATCOMP0(x)	(x < 0.001f && x > -0.001f)

#define CGE_UNIFORM_MAX_LEN 32

typedef const char* const CGEConstString;

#define CGE_DELETE(p) do { delete p; p = NULL; } while(0)
#define CGE_DELETE_ARR(p) do { delete[] p; p = NULL; } while(0)

namespace CGE
{
	const char* cgeGetVersion();

	enum CGEBufferFormat
	{
		CGE_FORMAT_RGB_INT8,
		CGE_FORMAT_RGB_INT16,
		CGE_FORMAT_RGB_FLOAT32,
		CGE_FORMAT_RGBA_INT8,
		CGE_FORMAT_RGBA_INT16,
		CGE_FORMAT_RGBA_FLOAT32,
#ifdef GL_BGR
		CGE_FORMAT_BGR_INT8, 
		CGE_FORMAT_BGR_INT16,
		CGE_FORMAT_BGR_FLOAT32,
#endif
#ifdef GL_BGRA
		CGE_FORMAT_BGRA_INT8,		
		CGE_FORMAT_BGRA_INT16,		
		CGE_FORMAT_BGRA_FLOAT32,
#endif
#ifdef GL_RED_EXT
		CGE_FORMAT_R_INT8,
#endif
#ifdef GL_RG_EXT
		CGE_FORMAT_RG_INT8,
#endif

	};

	enum CGETextureBlendMode
	{
		CGE_BLEND_MIX,			// 0
		CGE_BLEND_OVERLAY,		// 1
		CGE_BLEND_HARDLIGHT,		// 2
		CGE_BLEND_SOFTLIGHT,		// 3
		CGE_BLEND_SCREEN,		// 4
		CGE_BLEND_LINEARLIGHT,	// 5
		CGE_BLEND_VIVIDLIGHT,	// 6
		CGE_BLEND_MULTIPLY,		// 7
		CGE_BLEND_EXCLUDE,		// 8
		CGE_BLEND_COLORBURN,		// 9
		CGE_BLEND_DARKEN,		// 10
		CGE_BLEND_LIGHTEN,		// 11
		CGE_BLEND_COLORDODGE,	// 12
		CGE_BLEND_COLORDODGEADOBE,// 13
		CGE_BLEND_LINEARDODGE,	// 14
		CGE_BLEND_LINEARBURN,	// 15
		CGE_BLEND_PINLIGHT,		// 16
		CGE_BLEND_HARDMIX,		// 17
		CGE_BLEND_DIFFERENCE,	// 18
		CGE_BLEND_ADD,			// 19
		CGE_BLEND_COLOR,			// 20

		/////////////    Special blend mode below     //////////////

		CGE_BLEND_ADD_REVERSE,	// 21
		CGE_BLEND_COLOR_BW,		// 22

		/////////////    Special blend mode above     //////////////

		CGE_BLEND_TYPE_MAX_NUM //Its value defines the max num of blend.
	};

	const char* cgeGetBlendModeName(CGETextureBlendMode mode);

	void cgePrintGLString(const char*, GLenum);
	void _cgeCheckGLError(const char* name, const char* file, int line);



	struct CGESizei
	{
		CGESizei(): width(0), height(0) {}
		CGESizei(int w, int h) : width(w), height(h) {}
		void set(int w, int h)
		{
			width = w;
			height = h;
		}
		GLint width;
		GLint height;
	};

	struct CGESizef
	{
		CGESizef() : width(0.0f), height(0.0f) {}
		CGESizef(float w, float h) : width(w), height(h) {}
		void set(float w, float h)
		{
			width = w;
			height = h;
		}
		GLfloat width;
		GLfloat height;
	};

#ifndef CGE_MIN

	template<typename Type>
	inline Type CGE_MIN(Type a, Type b)
	{
		return a < b ? a : b;
	}

#endif

#ifndef CGE_MAX

	template<typename Type>
	inline Type CGE_MAX(Type a, Type b)
	{
		return a > b ? a : b;
	}

#endif

#ifndef CGE_MID

	template<typename Type>
	inline Type CGE_MID(Type n, Type vMin, Type vMax)
	{
		if(n < vMin)
			n = vMin;
		else if(n > vMax)
			n = vMax;
		return n;
	}

#endif

}
#endif /* _CGECOMMONDEFINE_H_ */
