#pragma once
#include "../CommonUtilities/Vectors/vector3.h"
#include "WorldSpace.h"
#include "Camera.h"

namespace DX2D
{
	class CSprite;
	class CColor;
}

class WorldSpace;

struct RenderSolution
{
	float myZPosition;
	DX2D::CSprite * mySprite;
};

class RenderCommands
{
public:
	RenderCommands();
	~RenderCommands();

	void Init(DX2D::CSprite * const aSprite, Vector3<float> aPosition, const WorldSpace * aWorldSpace, const Vector4<float> aColour, const Vector3f aNormal);

	RenderSolution Render(const Camera & aCamera);

	DX2D::CColor CalculateLight(const Camera & aCamera);

	float CLAMPYCLAMPY(const float aValue, const float aMin = 0.f, const float aMax = 1.f);

	Vector4f MultiplyVector4(Vector4f aFirstVector, Vector4f aSecondVector);

private:
	
	DX2D::CSprite * mySprite;
	Vector3<float> myPosition;
	Vector4<float> myColour;
	Vector3f myNormal;

	const WorldSpace * myLocalSpace;
};

