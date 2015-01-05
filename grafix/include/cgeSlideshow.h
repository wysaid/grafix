/*
* cgeSlideshow.h
*
*  Created on: 2014-9-9
*      Author: Wang Yang
*        Mail: admin@wysaid.org
*/

#ifndef _CGESLIDESHOW_H_
#define _CGESLIDESHOW_H_

#include "cgeAction.h"
#include "cgeAnimation.h"
#include "cgeSprite2d.h"

namespace CGE
{
	template<class AnimationType, class SpriteType>
 	class AnimationLogicSpriteInterface : public AnimationType, public virtual SpriteType
	{
	public:
		AnimationLogicSpriteInterface(float start, float end) : AnimationType(start, end), SpriteType() {}
		virtual ~AnimationLogicSpriteInterface() {}

		typedef SpriteType SpriteInterfaceType;
		typedef AnimationType AnimationInterfaceType;

		virtual void render()
		{
			for(typename std::vector<AnimationType*>::iterator iter = this->m_children2Run.begin(); iter != this->m_children2Run.end(); ++iter)
			{
				(*iter)->_renderWithFather(this);
			}
		}

	protected:

		virtual float _getZ() const 
		{
			return this->getZ();
		}

		virtual void _renderWithFather(AnimationType* father)
		{
			CGE_LOG_ERROR("LogicSprite should not be added as child sprite!\n");
		}
	};

	//////////////////////////////////////////////////////////////////////////

	//InheritedSpriteType 必须是 FatherType::SpriteInterfaceType 的虚子类
	template<class FatherType, class InheritedSpriteType>
	class AnimationSpriteInterface2d : public FatherType, public InheritedSpriteType
	{
	public:
		AnimationSpriteInterface2d(float start, float end) : FatherType(start, end) {}
		AnimationSpriteInterface2d(float start, float end, GLuint texID, int w, int h) : FatherType(start, end), InheritedSpriteType(texID, w, h) {}
		AnimationSpriteInterface2d(float start, float end, SharedTexture& tex) : FatherType(start, end), InheritedSpriteInterfaceType(tex) {}

		typedef InheritedSpriteType InheritedSpriteInterfaceType;

		virtual void render()
		{
            InheritedSpriteType::render();
            for(typename std::vector<typename FatherType::AnimationInterfaceType*>::iterator iter = this->m_children2Run.begin(); iter != this->m_children2Run.end(); ++iter)
			{
				(*iter)->_renderWithFather(this);
			}
		}

		static void drawFunc(InheritedSpriteType* sprite)
		{
			sprite->_drawFunc();
		}

		static void _renderWithFather(AnimationSpriteInterface2d* sprite, typename FatherType::AnimationInterfaceType* father)
		{
			sprite->_renderWithFather(father);
		}

	protected:
		virtual void _renderWithFather(typename FatherType::AnimationInterfaceType* father)
		{
			if(!this->m_shouldRender)
				return ;

			FatherType* f = dynamic_cast<FatherType*>(father);
			assert(f != NULL);
			Vec2f pos = this->m_pos * f->getScaling() + f->getPosition();
			Vec2f scaling = this->m_scaling * f->getScaling();
			float rot = this->m_rotation + f->getRotation();

			this->m_program.bind();
			glUniform2f(this->m_translationLocation, pos[0], pos[1]);
			glUniform2f(this->m_scalingLocation, scaling[0], scaling[1]);
			glUniform1f(this->m_rotationLocation, rot);
			this->_drawFunc();

			CGE_LOG_CODE(
				if(!this->m_children2Run.empty())
				{
					CGE_LOG_ERROR("A children with children is not supported by now\n");
				}
			)
		}
	};

	//避免编译时产生不必要的实体化
	template<class FatherType>
	class AnimationSpriteInterface2d_InterChange : public FatherType
	{
	public:
		AnimationSpriteInterface2d_InterChange(float start, float end) : FatherType(start, end) {}
		AnimationSpriteInterface2d_InterChange(float start, float end, GLuint texID, int w, int h) : FatherType(start, end, texID, w, h) {}
		AnimationSpriteInterface2d_InterChange(float start, float end, SharedTexture& tex) : FatherType(start, end, tex) {}

		bool run(float currentTime)
		{
			this->updateByTime(currentTime);
			return FatherType::run(currentTime);
		}

		void animationStart()
		{
			this->setFrameTime(0.0f);
			return FatherType::animationStart();
		}
	};

	template<class FatherType, class InheritedSpriteType>
	class AnimationSpriteInterface2dWith3dSpace : public FatherType, public InheritedSpriteType
	{
	public:
		AnimationSpriteInterface2dWith3dSpace(float start, float end) : FatherType(start, end) {}
		AnimationSpriteInterface2dWith3dSpace(float start, float end, GLuint texID, int w, int h) : FatherType(start, end), InheritedSpriteType(texID, w, h) {}
		AnimationSpriteInterface2dWith3dSpace(float start, float end, SharedTexture& tex) : FatherType(start, end), InheritedSpriteInterfaceType(tex) {}

		typedef InheritedSpriteType InheritedSpriteInterfaceType;

		virtual void render()
		{
            InheritedSpriteType::render();
            for(typename std::vector<typename FatherType::AnimationInterfaceType*>::iterator iter = this->m_children2Run.begin(); iter != this->m_children2Run.end(); ++iter)
			{
				(*iter)->_renderWithFather(this);
			}
		}

	protected:
		virtual void _renderWithFather(typename FatherType::AnimationInterfaceType* father)
		{
			if(!this->m_shouldRender)
				return ;

			InheritedSpriteType* f = dynamic_cast<InheritedSpriteType*>(father);
			assert(f != NULL); // 类型不兼容
			Vec2f pos = this->m_pos * f->getScaling() + f->getPosition();
			Vec2f scaling = this->m_scaling * f->getScaling();
			Mat3 mRot = this->m_rotMatrix * f->getRotationMatrix();

			this->m_program.bind();
			glUniform2f(this->m_translationLocation, pos[0], pos[1]);
			glUniform2f(this->m_scalingLocation, scaling[0], scaling[1]);
			glUniformMatrix3fv(this->m_rotationLocation, 1, GL_FALSE, mRot.data[0]);
			this->_drawFunc();

			CGE_LOG_CODE(
				if(!this->m_children2Run.empty())
				{
					CGE_LOG_ERROR("A children with children is not supported by now\n");
				}
			)
		}
	};

	class TimeActionInterfaceAbstract;
	class SpriteInterface2d;
	class Sprite2d;
	class Sprite2dExt;
	class Sprite2dWith3dSpace;

	typedef AnimationWithChildrenInterface<TimeActionInterfaceAbstract> AnimAncestor;	
	typedef AnimationLogicSpriteInterface<AnimAncestor, SpriteInterface2d> AnimLogicSprite2d;
	typedef AnimationSpriteInterface2d<AnimLogicSprite2d, Sprite2d> AnimSprite2d;
	typedef AnimationSpriteInterface2d<AnimLogicSprite2d, Sprite2dExt> AnimSprite2dExt;
	typedef AnimationSpriteInterface2d<AnimLogicSprite2d, Sprite2dWithAlphaGradient> AnimSprite2dWithAlphaGradient;
	typedef AnimationSpriteInterface2dWith3dSpace<AnimLogicSprite2d, Sprite2dWith3dSpace> AnimSprite2dWith3dSpace;
	typedef AnimationSpriteInterface2d_InterChange<AnimationSpriteInterface2d<AnimLogicSprite2d, Sprite2dInterChangeExt>> AnimSprite2dInterChange;

	typedef TimeLineInterface<AnimationWithChildrenInterface<TimeActionInterfaceAbstract> > TimeLine;
}


#endif
