/*
 * cgeMultipleEffectsCommon.h
 *
 *  Created on: 2014-1-2
 *      Author: Wang Yang
 */

#ifndef _CGEMUTIPLEEFFECTSCOMMON_H_
#define _CGEMUTIPLEEFFECTSCOMMON_H_

#include "cgeGLFunctions.h"
#include "cgeCurveAdjust.h"

namespace CGE
{
	void cgeEnableColorScale();
	void cgeDisableColorScale();

	//"CGEBlendInterface" should not be used as instances.
	class CGEBlendInterface : public CGEImageFilterInterface
	{
	public:
		virtual ~CGEBlendInterface() {}
		virtual bool initWithMode(CGETextureBlendMode mode) = 0;
		virtual bool initWithMode(const char* modeName) = 0;
		virtual void setIntensity(float value);

		static CGETextureBlendMode getBlendModeByName(const char* modeName);
		static const char* getShaderFuncByBlendMode(const char* modeName);
		static const char* getShaderFuncByBlendMode(CGETextureBlendMode mode);
		static const char* getBlendWrapper();
		static const char* getBlendKrWrapper();
		static const char* getBlendPixWrapper();
		static const char* getBlendSelfWrapper();

		static bool initWithModeName(const char* modeName, CGEBlendInterface* blendIns);		
		static ParamType paramIntensityName;
	};

	class CGEBlendFilter : public CGEBlendInterface
	{
	public:
		CGEBlendFilter() : m_blendTexture(0) {}
		~CGEBlendFilter() { glDeleteTextures(1, &m_blendTexture); }

		virtual bool initWithMode(CGETextureBlendMode mode);
		virtual bool initWithMode(const char* modeName);

		void setSamplerID(GLuint texID) { m_blendTexture = texID; }

	protected:
		static ParamType paramBlendTextureName;
		void initSampler();

	protected:
		GLuint m_blendTexture; //The texture would be deleted by this filter;
	};

	class CGEBlendWithResourceFilter : public CGEBlendFilter
	{
	public:
        CGEBlendWithResourceFilter() : m_loadFunc(NULL), m_unloadFunc(NULL), m_loadParam(NULL), m_unloadParam(NULL) {}
		~CGEBlendWithResourceFilter() { }

		
		bool loadResources(const char* textureName);

		void setLoadFunction(CGEBufferLoadFun fLoad, void* loadParam, CGEBufferUnloadFun fUnload, void* unloadParam);

		void setTexSize(int w, int h) { m_blendTextureSize.set(w, h); }
		CGESizei& getTexSize() { return m_blendTextureSize; }

	protected:		
		CGEBufferLoadFun m_loadFunc;
		CGEBufferUnloadFun m_unloadFunc;
		void* m_loadParam;
		void* m_unloadParam;
		CGESizei m_blendTextureSize;
	};

	class CGEBlendKeepRatioFilter : public CGEBlendWithResourceFilter
	{
	public:
		bool initWithMode(CGETextureBlendMode mode);
		bool initWithMode(const char* modeName);
	protected:
		static ParamType paramAspectRatioName;
	};

	class CGEBlendTileFilter : public CGEBlendWithResourceFilter
	{
	public:
		bool initWithMode(CGETextureBlendMode mode);
		bool initWithMode(const char* modeName);
		void render2Texture(CGEImageHandlerInterface* handler, GLuint srcTexture, const GLfloat* posVertices);
	protected:
		static ParamType paramScalingRatioName;
	};

	class CGEPixblendFilter : public CGEBlendInterface
	{
	public:
		CGEPixblendFilter() {}
		~CGEPixblendFilter() {}

		virtual bool initWithMode(CGETextureBlendMode mode);
		virtual bool initWithMode(const char* modeName);
		
		void setBlendColor(float r, float g, float b, float a = 1.0f);

	protected:
		static ParamType paramBlendColorName;
	};

	class CGEBlendWithSelfFilter : public CGEBlendInterface
	{
	public:
		CGEBlendWithSelfFilter() {}
		~CGEBlendWithSelfFilter() {}

		bool initWithMode(CGETextureBlendMode mode);
		bool initWithMode(const char* modeName);

	};

	class CGEBlendVignetteFilter : public CGEPixblendFilter
	{
	public:
		virtual bool initWithMode(CGETextureBlendMode mode);

		void setVignetteCenter(float x, float y);  //Range: [0, 1], and 0.5 for the center.
		void setVignette(float start, float range); //Range: [0, 1]

	protected:
		static ParamType paramVignetteCenterName;
		static ParamType paramVignetteName;
	};

	class CGEBlendVignetteNoAlphaFilter : public CGEBlendVignetteFilter
	{
		virtual bool initWithMode(CGETextureBlendMode mode);
	};

	class CGEBlendVignette2Filter : public CGEBlendVignetteFilter
	{
	public:
		virtual bool initWithMode(CGETextureBlendMode mode);
	};

	class CGEBlendVignette2NoAlphaFilter : public CGEBlendVignetteFilter
	{
	public:
		virtual bool initWithMode(CGETextureBlendMode mode);
	};

	//////////////////////////////////////////////////////////////////////////

	class CGELomoFilter : public CGEImageFilterInterface
	{
	public:
		CGELomoFilter() : m_scaleDark(-1.0f), m_scaleLight(-1.0f), m_saturate(1.0f) {}

		bool init();

		void setVignette(float start, float end);
		void setIntensity(float value);
		void setSaturation(float value);
		void setColorScale(float low, float range);

		void render2Texture(CGEImageHandlerInterface* handler, GLuint srcTexture, const GLfloat* posVertices);


	protected:
		static ParamType paramColorScaleName;
		static ParamType paramSaturationName;
		static ParamType paramVignetteName;
		static ParamType paramAspectRatio;
		static ParamType paramIntensityName;

	private:
		GLfloat m_scaleDark, m_scaleLight, m_saturate;
	};

	class CGELomoLinearFilter : public CGELomoFilter
	{
	public:
		bool init();
	};

	//////////////////////////////////////////////////////////////////////////

	class CGELomoWithCurveFilter : public CGEMoreCurveFilter
	{
	public:
		CGELomoWithCurveFilter() : m_scaleDark(-1.0f), m_scaleLight(-1.0f), m_saturate(1.0f) {}
		virtual bool init();

		void setVignette(float start, float end);
		void setSaturation(float value);
		void setColorScale(float low, float range);

		void render2Texture(CGEImageHandlerInterface* handler, GLuint srcTexture, const GLfloat* posVertices);

	protected:
		static ParamType paramColorScaleName;
		static ParamType paramSaturationName;
		static ParamType paramVignetteName;
		static ParamType paramAspectRatio;

	private:
		GLfloat m_scaleDark, m_scaleLight, m_saturate;
	};

	class CGELomoWithCurveLinearFilter : public CGELomoWithCurveFilter
	{
	public:
		bool init();
	};

	//////////////////////////////////////////////////////////////////////////

	class CGELomoWithCurveTexFilter : public CGELomoWithCurveFilter
	{
	public:
		virtual bool init();

		virtual void flush();

	protected:
		void initSampler();

	protected:
		GLuint m_curveTexture;
	};

	class CGELomoWithCurveTexLinearFilter : public CGELomoWithCurveTexFilter
	{
	public:
		bool init();
	};

	//////////////////////////////////////////////////////////////////////////

	class CGEColorScaleFilter : public CGEImageFilterInterface
	{
	public:
		CGEColorScaleFilter() : m_scaleDark(-1.0f), m_scaleLight(-1.0f), m_saturate(1.0f) {}
		~CGEColorScaleFilter() {}

		virtual bool init();

		void setColorScale(float low, float range);
		//Set saturation value to -1.0 ( < 0.0 ) when your shader program did nothing with this value.
		void setSaturation(float value);

		virtual void render2Texture(CGEImageHandlerInterface* handler, GLuint srcTexture, const GLfloat* posVertices);

	protected:
		static ParamType paramColorScaleName;
		static ParamType paramSaturationName;
	private:
		GLfloat m_scaleDark, m_scaleLight, m_saturate;
	};

	class CGEColorMulFilter : public CGEImageFilterInterface
	{
	public:

		enum MulMode { mulFLT, mulVEC, mulMAT };

		bool initWithMode(MulMode mode);

		void setFLT(float value);
		void setVEC(float r, float g, float b);
		void setMAT(float* mat); //The lenth of "mat" must be at least 9.
	protected:
		static ParamType paramMulName;
	};

}


#endif
