﻿/*
* cgeMosaicBlur.h
*
*  Created on: 2014-4-10
*      Author: Wang Yang
*  Description: 马赛克
*/

#ifndef _CGE_MOSAICBLUR_H_
#define _CGE_MOSAICBLUR_H_

#include "cgeBeautyEffectsCommon.h"

namespace CGE
{
	class CGEMosaicBlurFilter : public CGEBeautyEffectOneStepFilterHelper
	{
	public:
		
		bool init();

		//Range: value >= 1.0, and 1.0(Default) for the origin. Value is better with integer.
		void setBlurPixels(float value);

	protected:
		static ParamType paramBlurPixelsName;
	};
}

#endif