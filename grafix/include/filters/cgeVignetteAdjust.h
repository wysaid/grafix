﻿/*
 * cgeVignetteAdjust.h
 *
 *  Created on: 2014-1-22
 *      Author: Wang Yang
 */

#ifndef _CGEVIGNETTEADJUST_H_
#define _CGEVIGNETTEADJUST_H_

#include "cgeGLFunctions.h"

namespace CGE
{

	class CGEVignetteFilter : public CGEImageFilterInterface
	{
	public:

		virtual bool init();

		void setVignetteCenter(float x, float y); //Range: [0, 1], and 0.5 for the center.
		void setVignette(float start, float range); //Range: [0, 1]

	protected:
		static ParamType paramVignetteCenterName;
		static ParamType paramVignetteName;
	};

	class CGEVignetteExtFilter : public CGEVignetteFilter
	{
	public:	
		bool init();

		void setVignetteColor(float r, float g, float b);

	protected:
		static ParamType paramVignetteColor;
	};

}

#endif