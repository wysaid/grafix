#ifndef _CGE_REDEYEREMOVE_H_
#define _CGE_REDEYEREMOVE_H_

#include "cgeBeautyEffectsCommon.h"

namespace CGE
{
	class CGERedeyeRemoveFilter : public CGEBeautyEffectOneStepFilterHelper
	{
	public:
		bool init();

		void setEyePostion(float x, float y);

		void setRadius(float radius);

		void setAlpha(float alpha);

	protected:
		static ParamType paramRadiusName;
		static ParamType paramEyePostionName;
		static ParamType  paramAlphaName;
	};
}

#endif