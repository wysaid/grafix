/*
 * cgeMultipleEffects.h
 *
 *  Created on: 2013-12-13
 *      Author: Wang Yang
 *        Blog: http://wysaid.org
*/

#ifndef _CGEMUTIPLEEFFECTS_H_
#define _CGEMUTIPLEEFFECTS_H_

#include "cgeMultipleEffectsCommon.h"
#include "cgeFilterBasic.h"

namespace CGE
{
	//It's just a help class for CGEMutipleEffectFilter.
	class CGEFilterMixFilter : protected CGEImageFilterInterface
	{
		friend class CGEMutipleEffectFilter;
	protected:
		CGEFilterMixFilter() {}

		void setIntensity(float value);

		bool init();

		void render2Texture(CGEImageHandlerInterface* handler, GLuint srcTexture, const GLfloat* posVertices);

		bool needToMix();

		bool noIntensity();

	protected:
		static ParamType paramIntensityName;
		static ParamType paramOriginImageName;
		
	private:
		float m_intensity;
	};


	//This class is inherited from top filter interface and would do more processing steps
	// than "CGEImageFilter" does.
	class CGEMutipleEffectFilter : public CGEImageFilterInterfaceAbstract
	{
	public:	
		CGEMutipleEffectFilter();
		~CGEMutipleEffectFilter();
		bool initWithEffectID(int index);
		bool initWithEffectString(const char* pstr);
		bool initCustomize(); //特殊用法， 自由组合

		void setIntensity(float value);

		void render2Texture(CGEImageHandlerInterface* handler, GLuint srcTexture, const GLfloat* posVertices);

		void addFilter(CGEImageFilterInterface* proc) { if(proc != NULL) m_vecProc.push_back(proc); }
		void clearFilters();
		bool isEmpty() { return m_vecProc.empty(); }

		void setLoadFunction(CGEBufferLoadFun fLoad, void* loadParam, CGEBufferUnloadFun fUnload, void* unloadParam);

		GLuint loadResources(const char* textureName);

		CGEBufferLoadFun getLoadFunc() { return m_loadFunc; };
		CGEBufferUnloadFun getUnloadFunc() { return m_unloadFunc; }
		void* getLoadParam() { return m_loadParam; }
		void* getUnloadParam() { return m_unloadParam; }
	protected:
		CGEBufferLoadFun m_loadFunc;
		CGEBufferUnloadFun m_unloadFunc;
		void* m_loadParam;
		void* m_unloadParam;
		std::vector<CGEImageFilterInterface*> m_vecProc;
		CGEFilterMixFilter m_mixProc;
	};
}


#endif /* _CGEMUTIPLEEFFECTS_H_ */
