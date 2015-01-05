/*
* cgeLightFilter.h
*
*  Created on: 2014-6-3
*      Author: liu hailong
*/

#ifndef  _CGE_LIGHT_H_
#define  _CGE_LIGHT_H_

#include "cgeBeautyEffectsCommon.h"

namespace CGE
{
	class CGELightFilter : public CGEBeautyEffectOneStepFilterHelper
	{
	public:
		bool init();
		void setColor(float r,float g,float b);
		void setCentrePosition(float x,float y);
	protected:
		static ParamType paramColorName;
		static ParamType paramCentrePositionName;

	};

}


#endif