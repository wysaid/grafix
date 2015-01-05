/*
* cgeScene.h
*
*  Created on: 2014-10-27
*      Author: Wang Yang
*        Mail: admin@wysaid.org
*/

#ifndef _CGE_SCENE_H_
#define _CGE_SCENE_H_

/*

cgeScene 提供场景漫游辅助接口（非必须）

特别注意， cgeScene 使用 xOy 平面作为漫游地面， z正方向为向上方向
cgeScene 仅提供相关矩阵和向量, 不提供任何渲染接口。

*/

#include "cgeMat.h"
#include "cgeCommonDefine.h"

namespace CGE
{
	class SceneInterface
	{

	public:
		SceneInterface() : m_eye(0.0f, 0.0f), m_lookDir(0.0f, 1000.0f), m_eyeZ(0.0f), m_lookZ(0.0f), m_dirLen(1000.0f), m_fovyRad(M_PI / 3.0f), m_zNear(1.0f), m_zFar(10000.0f) {}
		~SceneInterface() {}

		inline void init(float w = 0.0f, float h = 0.0f)
		{
			updateView();
			resize(800.0f, 600.0f);
		}

		inline void resize(float w, float h)
		{
			m_projectionMatrix = Mat4::makePerspective(m_fovyRad, w / h, m_zNear, m_zFar);
		}

		inline void updateView()
		{
			Vec2f center(m_eye + m_lookDir);
			float len = center.length();
			float tmp = -m_lookZ / len;
			Vec2f dirBack(center * tmp);
			m_modelViewMatrix = Mat4::makeLookAt(m_eye[0], m_eye[1], m_eyeZ, center[0], center[1], m_lookZ, dirBack[0], dirBack[1], len);
		}

		//转动视角， rad(弧度) > 0 时 为向右方向
		inline void turn(float rad)
		{
			m_lookDir = Mat2::makeRotation(rad) * m_lookDir;
		}

		//转动视角， rad(弧度) > 0 时 为右边。
		inline void turnTo(float rad)
		{
			m_lookDir[0] = sinf(rad);
			m_lookDir[1] = cosf(rad);
		}

		//向上观察， motion计算关系
		//向上观察弧度计算公式为: arctan(tan("当前向上弧度") + motion) - "当前向上弧度"
		inline void lookUp(float motion)
		{
			const float lookUpMax = m_dirLen * 3.732f; // tan(PI / 75);
			m_lookZ = CGE_MID(m_lookZ + motion * m_dirLen, -lookUpMax, lookUpMax);
		}

		//向上观察到(弧度), 直接仰视到所看弧度
		//范围[-PI/2.4, PI/2.4], 约正负75度角
		inline void lookUpTo(float rad)
		{
			m_lookZ = tanf(CGE_MID<float>(rad, -M_PI / 2.4f, M_PI / 2.4f)) * m_dirLen;
		}

		inline void lookIn(float rad)
		{
			m_fovyRad = CGE_MID<float>(m_fovyRad + rad, M_PI / 10.0f, m_fovyRad / 2.4f);
		}

		inline void lookInTo(float rad)
		{
			m_fovyRad = CGE_MID<float>(rad, M_PI / 10.0f, m_fovyRad / 2.4f);
		}

		inline void goForward(float motion)
		{
			m_eye += m_lookDir * (motion / m_dirLen);
		}

		inline void goBack(float motion)
		{
			m_eye -= m_lookDir * (motion / m_dirLen);
		}

		inline void goLeft(float motion)
		{
			float m = motion / m_dirLen;
			m_eye[0] -= m_lookDir[1] * m;
			m_eye[1] += m_lookDir[0] * m;
		}

		inline void goRight(float motion)
		{
			float m = motion / m_dirLen;
			m_eye[0] += m_lookDir[1] * m;
			m_eye[1] -= m_lookDir[0] * m;
		}

		inline Mat4& modelViewMatrix() { return m_modelViewMatrix; }
		inline Mat4& projectionMatrix() { return m_projectionMatrix; }

	protected:
		Mat4 m_modelViewMatrix, m_projectionMatrix;
		Vec2f m_eye, m_lookDir;
		float m_eyeZ, m_lookZ;
		float m_dirLen;

		//视景体的视野角度（弧度）， 透视投影近裁剪面， 透视投影远裁剪面
		float m_fovyRad, m_zNear, m_zFar;
	};
}

#endif