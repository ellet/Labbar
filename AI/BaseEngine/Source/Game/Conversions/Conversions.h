#pragma once

inline DX2D::Vector2f To(const SB::Vector2f & aVector)
{
	return DX2D::Vector2f(aVector.x, aVector.y);
}

inline SB::Vector2f To(const DX2D::Vector2f & aVector)
{
	return SB::Vector2f(aVector.x, aVector.y);
}

inline SB::Vector2f To(const DX2D::Vector2ui & aVector)
{
	return SB::Vector2f(static_cast<float>( aVector.x), static_cast<float>( aVector.y));
}