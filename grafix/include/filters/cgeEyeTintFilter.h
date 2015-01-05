﻿/*
* cgeEyeTintFilter.h
*
*  Created on: 2014-4-23
*      Author: Wang Yang
*/

#ifndef _CGE_EYETINT_H_
#define _CGE_EYETINT_H_

#include "cgeBeautyEffectsCommon.h"

namespace CGE
{
	class CGEEyeTintFilter : public CGEImageFilterInterface
	{
	public:

		bool init();

		//range: [0.0, 1.0]
		void setTintColor(float r, float g, float b);

	protected:
		static ParamType paramTintName;
	};

}

#endif