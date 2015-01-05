/*
 * cgeSaturationAdjust.h
 *
 *  Created on: 2013-12-26
 *      Author: Wang Yang
 */

#ifndef _CGESATURATION_ADJUST_H_
#define _CGESATURATION_ADJUST_H_

#include "cgeGLFunctions.h"
#include "CGEImageFilter.h"
#include "cgeImageHandler.h"
#include "cgeCurveAdjust.h"

namespace CGE
{
	//This one is based on HSL.
	class CGESaturationHSLFilter : public CGEImageFilterInterface
	{
	public:
		CGESaturationHSLFilter(){}
		~CGESaturationHSLFilter(){}

		void setSaturation(float value); // range [-1, 1]

		void setHue(float value); // range [-1, 1]

		void setLum(float lum); // range [-1, 1]

		bool init();

	protected:
		static const char* const paramSaturationName;
		static const char* const paramHueName;
		static const char* const paramLuminanceName;
	};

	// You can use the fast one instead(of the one above). 
	class CGESaturationFilter : public CGEImageFilterInterface
	{
	public:
		CGESaturationFilter() {}
		~CGESaturationFilter() {}
		bool init();

		//range: >0, 1 for origin, and saturation would increase if value > 1
		void setIntensity(float value);

	protected:
		static const char* const paramIntensityName;
	};

	//This one is based on HSV
	class CGESaturationHSVFilter : public CGEImageFilterInterface
	{
	public:
		CGESaturationHSVFilter(){}
		~CGESaturationHSVFilter(){}

		bool init();

		void setAdjustColors(float red, float green, float blue,
							float magenta, float yellow, float cyan);

	protected:
		static ParamType paramColor1;
		static ParamType paramColor2;
	};
}

#endif