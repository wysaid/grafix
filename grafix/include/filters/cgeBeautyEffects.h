/*
 * cgeBeautyEffects.h
 *
 *  Created on: 2013-12-13
 *      Author: Wang Yang
 */

#ifndef _CGEBEAUTYEFFECTS_H_
#define _CGEBEAUTYEFFECTS_H_

#include "cgeEmbossFilter.h"
#include "cgeEdgeFilter.h"
#include "cgeRandomBlurFilter.h"
#include "cgeBilateralBlurFilter.h"
#include "cgeMosaicBlurFilter.h"
#include "cgeEnlargeEyeFilter.h"
#include "cgeEyeTintFilter.h"
#include "cgeEyeBrightenFilter.h"
#include "cgeTeethWhitenFilter.h"
#include "cgeMarscaraFilter.h"
#include "cgeWrinkleRemoverFilter.h"
#include "cgeRedeyeRemoveFilter.h"
#include "cgeLiquidationFilter.h"
#include "cgeLightFilter.h"

namespace CGE
{
	extern const int g_htNewEffectsNum;
	CGEEmbossFilter* getEmbossFilter();
	cgeEdgeFilter* getEdgeFilter();
	CGERandomBlurFilter* getRandomBlurFilter();
	CGEBilateralBlurFilter* getBilateralBlurFilter();
    CGEBilateralBlurBetterFilter* getBilateralBlurBetterFilter();
	CGEMosaicBlurFilter* getMosaicBlurFilter();
	CGEEnlargeEyeFilter* getEnlargeEyeFilter();
	CGEEyeTintFilter* getEyeTintFilter();
	CGEEyeBrightenFilter* getEyeBrightenFilter();
	CGETeethWhitenFilter* getTeethWhitenFilter();
	CGEMarscaraFilter* getMarscaraFilter();
	CGEWrinkleRemoveFilter* getWrinkleRemoveFilter();
	CGERedeyeRemoveFilter* getRedeyeRemoveFilter();
	CGELightFilter* getLightFilter();
	CGELiquidationFilter* getLiquidationFilter(float ratio, float stride);
	CGELiquidationFilter* getLiquidationFilter(float width, float height , float stride);

	CGELiquidationNicerFilter* getLiquidationNicerFilter(float ratio, float stride);
	CGELiquidationNicerFilter* getLiquidationNicerFilter(float width, float height , float stride);

}

#endif 
