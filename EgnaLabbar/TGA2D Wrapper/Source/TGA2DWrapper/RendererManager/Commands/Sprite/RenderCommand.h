#pragma once

#include <Vectors\vector2.h>
#include <Vectors\vector4.h>

namespace DX2D
{
	class CSprite;
}

class RenderCommand
{
public:

	RenderCommand();
	RenderCommand(DX2D::CSprite *aSprite, const Vector2f &aPosition, const Vector2f &aSize, const Vector2f &aPivot, const float aRotation, const Vector4f aColors, const Vector4f aRectangle);
	~RenderCommand();

	void Render(const Vector2f &aParentPosition, const Vector2f &aParentSize);

private:

	DX2D::CSprite *mySprite;

	Vector2f myPosition;
	Vector2f mySize;
	Vector2f myPivot;
	
	float myRotation;

	Vector4f myColors;
	Vector4f myRectangle;

};
