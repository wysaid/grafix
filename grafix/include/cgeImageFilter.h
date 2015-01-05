/*﻿
* cgeImageFilter.h
*
*  Created on: 2013-12-13
*      Author: Wang Yang
*/

#ifndef _CGEIMAGEFILTER_H_
#define _CGEIMAGEFILTER_H_

#include "cgeGLFunctions.h"
#include "cgeShaderFunctions.h"
#include "cgeImageHandler.h"

#define CGE_CURVE_PRECISION 256

namespace CGE
{

	extern const char* const g_vshDefault;
	extern const char* const g_vshDefaultWithoutTexCoord;
	extern const char* const g_vshDrawToScreen;
	extern const char* const g_vshDrawToScreenRot90;
	extern const char* const g_fshDefault;
	extern const char* const g_fshFastAdjust;
	extern const char* const g_fshFastAdjustRGB;
	extern const char* const g_fshCurveMapNoIntensity;

	extern const char* const g_vshTest;
	extern const char* const g_fshTest;

	extern const char* const g_paramFastAdjustArrayName;
	extern const char* const g_paramFastAdjustRGBArrayName;
	extern const char* const g_paramCurveMapTextureName;


	class CGEImageHandlerInterface;

	class CGEImageFilterInterfaceAbstract
	{
	public:
		CGEImageFilterInterfaceAbstract() { cgeEnableGlobalGLContext(); }
		virtual ~CGEImageFilterInterfaceAbstract() {}
		virtual void render2Texture(CGE::CGEImageHandlerInterface* handler, GLuint srcTexture, const GLfloat* posVertices) = 0;
		typedef const char* const ParamType;
	};

	class CGEImageFilterInterface : public CGE::CGEImageFilterInterfaceAbstract
	{
	public:
		CGEImageFilterInterface();
		virtual ~CGEImageFilterInterface();

		virtual void render2Texture(CGE::CGEImageHandlerInterface* handler, GLuint srcTexture, const GLfloat* posVertices);

		//////////////////////////////////////////////////////////////////////////
		virtual bool initShadersFromString(const char* vsh, const char* fsh);
		//	virtual bool initShadersFromFile(const char* vshFileName, const char* fshFileName);

		virtual void setAdditionalUniformParameter(UniformParameters* param);

		virtual bool init() { return false; }

		ProgramObject& getProgram() { return m_program; }

	protected:
		//////////////////////////////////////////////////////////////////////////
		virtual bool initVertexShaderFromString(const char* vsh);
		//	virtual bool initVertexShaderFromFile(const char* vshFileName);

		virtual bool initFragmentShaderFromString(const char* fsh);	
		//	virtual bool initFragmentShaderFromFile(const char* fshFileName);

		virtual bool finishLoadShaders(); //如果单独调用上方函数初始化，请在结束后调用本函数。	

	protected:
		ProgramObject m_program;

		//See the description of "UniformParameters" to know "How to use it".
		UniformParameters* m_uniformParam;


		//////////////////////////////////////////////////////////////////////////
	protected:

		static ParamType paramInputImageName;
		static ParamType paramPositionIndexName;
	};

	class CGEFastAdjustFilter : public CGE::CGEImageFilterInterface
	{
	public:

		typedef struct CurveData
		{
			float data[3];

			float& operator[](int index)
			{
				return data[index];
			}

			const float& operator[](int index) const
			{
				return data[index];
			}
		}CurveData;

		bool init();

	protected:
		static ParamType paramArray;
		void assignCurveArrays();
		void initCurveArrays();

	protected:
		std::vector<CurveData> m_curve;
	};

	class CGEFastAdjustRGBFilter : public CGE::CGEImageFilterInterface
	{
	public:

		bool init();

	protected:
		static ParamType paramArrayRGB;
		void assignCurveArray();
		void initCurveArray();

	protected:
		std::vector<float> m_curveRGB;
	};

}

#endif
