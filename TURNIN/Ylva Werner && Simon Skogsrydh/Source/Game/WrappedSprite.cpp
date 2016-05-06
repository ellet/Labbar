#include "stdafx.h"
#include "WrappedSprite.h"
#include "tga2d/sprite/sprite.h"

WrappedSprite::WrappedSprite()
{
}


WrappedSprite::~WrappedSprite()
{
}

void WrappedSprite::Init()
{
	mySprite = new DX2D::CSprite(nullptr);
	mySprite->SetPivot(DX2D::Vector2f(0.5f, 0.5f));
}

void WrappedSprite::SetColor(const Vector4f& aColor)
{
	mySprite->SetColor(DX2D::CColor(aColor.r, aColor.g, aColor.b, aColor.a));
}
