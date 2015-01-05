/*
 * cgeRandomBlurFilter.h
 *
 *  Created on: 2013-12-29
 *      Author: Wang Yang
 */

#ifndef _CGERANDOMBLUR_H_
#define _CGERANDOMBLUR_H_

#include "cgeBeautyEffectsCommon.h"

namespace CGE
{
	class CGERandomBlurFilter : public CGEBeautyEffectOneStepFilterHelper
	{
	public:
		CGERandomBlurFilter(){}
		~CGERandomBlurFilter(){}

		void setIntensity(float value);
		void setSamplerScale(float value);

		bool init();

	protected:
		static ParamType paramIntensity;
		static ParamType paramSamplerScale;
		static ParamType paramSamplerRadius;
	};
}

#endif 