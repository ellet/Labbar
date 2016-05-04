#pragma once
#include "../CommonUtilities/Vectors/vector3.h"
#include "WorldSpace.h"
#include "Camera.h"

namespace DX2D
{
	class CSprite;
}

class WorldSpace;

class RenderCommands
{
public:
	RenderCommands();
	~RenderCommands();

	void Init(DX2D::CSprite * const aSprite, Vector3<float> aPosition, const WorldSpace * aWorldSpace, Vector4<float> aColour = Vector4f::One, Vector2f aSize = Vector2f::One);

	void Render(const Camera & aCamera);

private:
	
	DX2D::CSprite * mySprite;
	Vector3<float> myPosition;
	Vector4<float> myColour;

	Vector2f mySize;

	const WorldSpace * myLocalSpace;
};

