///#include "stdafx.h"
#include "ISprite2D.h"

using namespace DeviceInterface;

ISprite2D::ISprite2D()
:_centerx(0.0f)
,_centery(0.0f)
,_positionx(0.0f)
,_positiony(0.0f)
,_positionz(0.0f)
,_angle(0.0f)
,_scalex(1.0f)
,_scaley(1.0f)
,_R(1.0f)
,_G(1.0f)
,_B(1.0f)
,_A(1.0f)
,_actorR(1.0f)
,_actorG(1.0f)
,_actorB(1.0f)
,_animationspeed(1.0f)
,_visible(true)
,_drawAreaON(FALSE)
{
	_draworder.y = 0;
	_draworder.z = 0;

}

ISprite2D::~ISprite2D(void)
{
}

void ISprite2D::SetDatummark(float x, float y)
{
	_centerx = x;
	_centery = y;
}

void ISprite2D::SetColor(float R, float G, float B)
{
	_R = R;
	_G = G;
	_B = B;
}

void ISprite2D::SetAlpha(float alpha)
{
	_A = alpha;
}

void ISprite2D::SetColorR(float R)
{
	_R = R;
}

void ISprite2D::SetColorG(float G)
{
	_G = G;
}

void ISprite2D::SetColorB(float B)
{
	_B = B;
}

void ISprite2D::SetActorColor(float R,float G,float B)
{
	_actorR = R;
	_actorG = G;
	_actorB = B;
}

void ISprite2D::SetPosition(float x, float y, float z /*= 0*/)
{
	_positionx = (int)x;
	_positiony = (int)y;
	_positionz = (int)z;
	//_positionx = x;
	//_positiony = y;
	//_positionz = z;
}

void ISprite2D::SetFPosition(float x, float y, float z /*= 0*/)
{
	_positionx = x;
	_positiony = y;
	_positionz = z;
}

void ISprite2D::SetScale(float x, float y)
{
	_scalex = x;
	_scaley = y;
}

void ISprite2D::SetRotation(float angle)
{
	_angle = angle;
}

void ISprite2D::SetDrawArea(float left,float top,float width,float height,BOOL on)
{
	_drawAreaON = on;
	_drawareaLeft = left;
	_drawareaTop = top;
	_drawareaWidth = width;
	_drawareaHeight = height;
}