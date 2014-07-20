#pragma once
#include "../DeviceInterface/ITexture.h"

namespace DeviceInterface
{
	class SceneLayer;
	enum ShaderConstant
	{
		eVsConstantF,
		eVsConstantB,
		eVsConstantI,
		ePsConstantF,
		ePsConstantB,
		ePsConstantI,
	};
	SmartPointer(ISprite2D);

	// DrawZ �������� 
	// Y�����ȼ��� , Z�����ȼ���
	// Y ֵ�͵Ļᱻ�ڵ�, Zֵ�͵Ļᱻ�ڵ�.

	struct DrawZ
	{
		int y ;
		int z ;
	};

	/*
		The Sprite2D to Render Texture;
		the Center is the base of the texture position & Scale & Rotation
		if the center change the position of the sprite will be change.
		the center range is 0 ~ 1
		x 0 is left 1 is right 
		y 0 is top 1 is bottom
	*/
	class ISprite2D : public Foundation::IObject
	{
		friend SceneLayer;
	public:
		ISprite2D();
	public:
		virtual ~ISprite2D(void);
	public:
		virtual void Draw(int deltatime) = 0;
		virtual void Draw(float cameraposix,float cameraposiy,float camerasizex,float camerasizey,int deltatime) = 0;
		virtual void SetDatummark(float x,float y);		//�԰ٷֱȵ���ʽȡ�ñ�׼���λ��
		virtual void SetPosition(float x,float y,float z = 0);
		virtual void SetFPosition(float x,float y,float z = 0);

		virtual void SetScale(float x,float y);
		virtual void SetRotation(float angle);
		virtual void SetColor(float R,float G,float B);//RGBA �ķ�Χ�� 0 ~ 2  1 Ϊ�����ֵ  0 Ϊû��  2 Ϊ��ֵ
		
		//�������յ���Ч��Ⱦ����
		//ֻ������Ч��������,ͼ��Żᱻ��Ⱦ,���� Ĭ���ǹرյ� , �������κ�������Ⱦ,��Ϊ True �� ���趨�ķ�Χ����Ⱦ
		virtual void SetDrawArea(float left,float top,float width,float height,BOOL on);
		
		virtual void SetColorR(float R);//RGBA �ķ�Χ�� 0 ~ 2  1 Ϊ�����ֵ  0 Ϊû��  2 Ϊ��ֵ
		virtual void SetColorG(float G);//RGBA �ķ�Χ�� 0 ~ 2  1 Ϊ�����ֵ  0 Ϊû��  2 Ϊ��ֵ
		virtual void SetColorB(float B);//RGBA �ķ�Χ�� 0 ~ 2  1 Ϊ�����ֵ  0 Ϊû��  2 Ϊ��ֵ
		virtual void SetAlpha(float alpha);//RGBA �ķ�Χ�� 0 ~ 2  1 Ϊ�����ֵ  0 Ϊû��  2 Ϊ��ֵ
		virtual void SetActorColor(float R,float G,float B);//ʹ����һ�ɫϵͳ,
		virtual ISprite2DPtr Copy() = 0; 
		virtual void SetVisible(BOOL on)
		{
			_visible = on;
		}
		BOOL GetVisible()
		{
			return _visible;
		}
// 		virtual void SetShaderParameter(CONST void* data,ShaderConstant constatantclass,UINT startRegister,UINT size) = 0;
		
		virtual void SetDrawID(int y,int z)
		{
			_draworder.y  = y;
			_draworder.z = z;
		}
		virtual DrawZ&  GetDrawID()
		{
			return _draworder;
		}

		virtual void SetAniamtionSpeed(float speed)
		{
			_animationspeed = speed;
		}

		virtual void RestartAniamtion()
		{

		}
		virtual BOOL IsAnimationOver()
		{
			return FALSE;
		}

		float GetR()
		{
			return _R;
		}
		float GetG()
		{
			return _G;
		}
		float GetB()
		{
			return _B;
		}
		float GetPositionX()
		{
			return _positionx;
		}
		float GetPositionY()
		{
			return _positiony;
		}
		float GetScaleX()
		{
			return _scalex;
		}
		float GetScaleY()
		{
			return _scaley;
		}
		void SetTime(int time)
		{
			_currenttime = time;
		}
		int GetTime()
		{
			return _currenttime;
		}
	protected:
		float _centerx;
		float _centery;
		float _positionx;
		float _positiony;
		float _positionz;
		float _angle;
		float _scalex;
		float _scaley;
		float _R;
		float _G;
		float _B;
		float _A;

		float _actorR;
		float _actorG;
		float _actorB;
		int     _currenttime;

		DrawZ _draworder;
		BOOL  _visible;
		float _animationspeed;

		BOOL _drawAreaON;
		float _drawareaLeft;
		float _drawareaTop;
		float _drawareaWidth;
		float _drawareaHeight;
	};
}