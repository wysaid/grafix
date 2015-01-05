/*
* cgeEnlargeEyeFilter.h
*
*  Created on: 2014-4-23
*      Author: Wang Yang
*/

#ifndef _CGE_ENLARGEEYE_H_
#define _CGE_ENLARGEEYE_H_

#include "cgeBeautyEffectsCommon.h"

namespace CGE
{
	class CGEEnlargeEyeFilter : public CGEBeautyEffectOneStepFilterHelper
	{
	public:
		
		bool init();

		void setEnlargeRadius(float radius); //Real radius counts by pixels.
		void setIntensity(float value); //Range: [-1.0, 1.0]
		void setCentralPosition(float x, float y); //Real position counts by pixels.

	protected:
		static ParamType paramRadiusName;
		static ParamType paramIntensityName;
		static ParamType paramCentralPosName;
	};

}

#endif