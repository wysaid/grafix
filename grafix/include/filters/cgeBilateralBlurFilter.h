/*
* cgeBilateralBlurFilter.h
*
*  Created on: 2014-4-1
*      Author: Wang Yang
*/

#ifndef _CGE_BLIATERALBLUR_H_
#define _CGE_BLIATERALBLUR_H_

#include "cgeBeautyEffectsCommon.h"

namespace CGE
{
    //blur with fixed radius.
	class CGEBilateralBlurFilter : public CGEBeautyEffectTwoStepFilterHelper
	{
	public:
		CGEBilateralBlurFilter() {}
		~CGEBilateralBlurFilter() {}

		bool init();

		//Range: value >= 0.0, and 0.0 for the origin. Default: 4.0
        virtual void setBlurScale(float value);

		//Range: [4.0, 12.0], none for the origin. Default: 8.0  (It'll show the origin when blurScale value is 1.0
		void setDistanceNormalizationFactor(float value);

	protected:
		static ParamType paramDistanceFactorName;
		static ParamType paramBlurSamplerScaleName;
		static ParamType paramBlurFactorsName;
	};

    //not blur with fixed radius.
    class CGEBilateralBlurBetterFilter : public CGEBilateralBlurFilter
    {
    public:
        bool init();
        void setSamplerRadiusLimit(int limit);
        virtual void setBlurScale(float value);

    protected:
        static ParamType paramBlurRadiusName;
        int m_limit;
    };

    class BilateralWrapper : public CGEImageFilterInterface
    {
    public:
        bool init()
        {
            proc1 = new CGEBilateralBlurBetterFilter;
            proc2 = new CGEBilateralBlurBetterFilter;
            return proc1->init() && proc2->init();
        }

        virtual void render2Texture(CGEImageHandlerInterface* handler, GLuint srcTexture, const GLfloat* posVertices)
        {
            proc1->render2Texture(handler, srcTexture, posVertices);
            handler->swapBufferFBO();
            proc2->render2Texture(handler, srcTexture, posVertices);
        }

        virtual void setBlurScale(float value)
        {
            proc1->setBlurScale(value);
            proc2->setBlurScale(value);
        }

        //Range: [4.0, 12.0], none for the origin. Default: 8.0  (It'll show the origin when blurScale value is 1.0
        void setDistanceNormalizationFactor(float value)
        {
            proc1->setDistanceNormalizationFactor(value);
            proc2->setDistanceNormalizationFactor(value);
        }

        CGEBilateralBlurBetterFilter *proc1, *proc2;
    };
}

#endif
