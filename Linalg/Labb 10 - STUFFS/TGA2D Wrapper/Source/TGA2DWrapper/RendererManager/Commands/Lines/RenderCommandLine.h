#pragma once

#include <Vectors\vector2.h>
#include <Vectors\vector4.h>

namespace DX2D
{
	class CSprite;
}

class RenderCommandLine
{
public:

	RenderCommandLine();
	RenderCommandLine(const Vector2f &aStartPosition, const Vector2f &anEndPosition, const Vector4f aColors);
	~RenderCommandLine();

	void Render(const Vector2f &aParentPosition, const Vector2f &aParentSize);

private:

	Vector2f myStartPosition;
	Vector2f myEndPosition;

	Vector4f myColors;

};
