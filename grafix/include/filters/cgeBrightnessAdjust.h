/*
 * cgeBrightnessAdjust.h
 *
 *  Created on: 2013-12-26
 *      Author: Wang Yang
 */

#ifndef _CGEBRIGHTNESSADJUST_H_
#define _CGEBRIGHTNESSADJUST_H_

#include "cgeGLFunctions.h"

namespace CGE
{
	class CGEBrightnessFilter : public CGEImageFilterInterface
	{
	public:
		CGEBrightnessFilter(){}
		~CGEBrightnessFilter(){}

		void setIntensity(float value); // range: [-1, 1]

		bool init();

	protected:
		static const char* const paramName;
	};

	class CGEBrightnessFastFilter : public CGEFastAdjustRGBFilter
	{
	public:
		CGEBrightnessFastFilter() {}
		~CGEBrightnessFastFilter() {}

		void setIntensity(float value);

		bool init();

	};

}

#endif