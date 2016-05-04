#pragma once

#include <Vectors/vector2.h>
#include <Vectors/vector4.h>

namespace DX2D
{
	class CSprite;
}

class WrappedSprite
{
public:
	WrappedSprite();
	~WrappedSprite();

	void Init();

	void SetPosition(const Vector2f & aPosition);
	Vector2f GetPosition();

	void SetColor(const Vector4f& aColor);

	DX2D::CSprite * GetSprite();

private:
	DX2D::CSprite * mySprite;
	Vector2f myPosition;
};

inline void WrappedSprite::SetPosition(const Vector2f & aPosition)
{
	myPosition = aPosition;
}

inline Vector2f WrappedSprite::GetPosition()
{
	return myPosition;
}

inline DX2D::CSprite * WrappedSprite::GetSprite()
{
	return mySprite;
}