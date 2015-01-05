/*
* cgeMarscara.h
*
*  Created on: 2014-5-5
*      Author: Wang Yang
*/

#ifndef _CGE_MARSCARA_H_
#define _CGE_MARSCARA_H_

#include "cgeBeautyEffectsCommon.h"

namespace CGE
{
	class CGEMarscaraFilter : public CGEBeautyEffectOneStepFilterHelper
	{
	public:

		bool init();

		//value >= 0
		void setSamplerScale(int value);

	protected:
		static ParamType paramSamplerScaleName;
	};
}



#endif