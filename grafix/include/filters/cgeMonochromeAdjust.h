/*
 * cgeMonochromeAdjust.h
 *
 *  Created on: 2013-12-29
 *      Author: Wang Yang
 */

#ifndef _CGEMONOCHROME_ADJUST_H_
#define _CGEMONOCHROME_ADJUST_H_

#include "cgeGLFunctions.h"
#include "CGEImageFilter.h"
#include "cgeImageHandler.h"

namespace CGE
{
	class CGEMonochromeFilter : public CGEImageFilterInterface
	{
	public:
		CGEMonochromeFilter(){}
		~CGEMonochromeFilter(){}

		void setIntensity(float value); //[0, 1], and if value < 0, the saturation would increase.

		bool init();

	protected:
		static const char* const paramName;
	};
}

#endif 