#pragma once
#include "tga2d\math\color.h"

inline Tga2D::Vector2f To(const SB::Vector2f & aVector)
{
	return Tga2D::Vector2f(aVector.x, aVector.y);
}

inline SB::Vector2f To(const Tga2D::Vector2f & aVector)
{
	return SB::Vector2f(aVector.x, aVector.y);
}

inline SB::Vector2f To(const Tga2D::Vector2ui & aVector)
{
	return SB::Vector2f(static_cast<float>( aVector.x), static_cast<float>( aVector.y));
}

inline Tga2D::CColor To(const SB::Color & aColor)
{
	return Tga2D::CColor(aColor.r, aColor.g, aColor.b, aColor.a);
}