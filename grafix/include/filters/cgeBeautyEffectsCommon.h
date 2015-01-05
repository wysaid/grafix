/*
 * cgeBeautyEffectsCommon.h
 *
 *  Created on: 2013-12-13
 *      Author: Wang Yang
 */

#ifndef _CGEBEAUTYEFFECTSCOMMON_H_
#define _CGEBEAUTYEFFECTSCOMMON_H_

#include "cgeGLFunctions.h"
#include "cgeImageFilter.h"
#include "cgeImageHandler.h"

namespace CGE
{
	class CGEBeautyEffectOneStepFilterHelper : public CGEImageFilterInterface
	{
	public:
		CGEBeautyEffectOneStepFilterHelper(){}
		~CGEBeautyEffectOneStepFilterHelper(){}
		virtual void render2Texture(CGEImageHandlerInterface* handler, GLuint srcTexture, const GLfloat* posVertices);

	protected:
		static const char* const paramStepsName;
	};

	class CGEBeautyEffectTwoStepFilterHelper : public CGEImageFilterInterface
	{
	public:
		CGEBeautyEffectTwoStepFilterHelper() {}
		~CGEBeautyEffectTwoStepFilterHelper() {}

		virtual void render2Texture(CGEImageHandlerInterface* handler, GLuint srcTexture, const GLfloat* posVertices);

	protected:
		static const char* const paramStepsName;
	};

}

#endif