/*
 * cgeZoomBlurAdjust.h
 *
 *  Created on: 2014-9-17
 *      Author: wxfred
 */

#ifndef _CGEZOOMBLURADJUST_H
#define _CGEZOOMBLURADJUST_H

#include "cgeGLFunctions.h"

namespace CGE
{
	//�ʺ�������ɢ�����
	class CGEZoomBlurFilter : public CGEImageFilterInterface
	{
	public:
		CGEZoomBlurFilter(){}
		~CGEZoomBlurFilter(){}

		virtual void setCenter(float x, float y); // texture coordinate
		virtual void setIntensity(float strength); // range: [0, 1]

		bool init();

	protected:
		static const char* const paramCenterName;
		static const char* const paramIntensityName;
	};

	//���з����� �������������
	class CGEZoomBlur2Filter : public CGEZoomBlurFilter
	{
	public:
		CGEZoomBlur2Filter() {}
		~CGEZoomBlur2Filter() {}

		bool init();

	protected:
		static CGEConstString paramStepsName;

	};

}

#endif