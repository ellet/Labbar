#pragma once
#include "../CommonUtilities/Vectors/Vector.h"

namespace DX2D
{
	class CSprite;
}

class WorldSpace;

class BaseGameObject
{
public:
	BaseGameObject();
	~BaseGameObject();

	void Init(const char* aFilePath, const WorldSpace * aWorldSpace = nullptr,
		Vector3<float> aPosition = Vector3<float>(0.f, 0.f, 0.f),
		Vector4<float> aColour = Vector4<float>(1.f, 1.f, 1.f, 1.f),
		Vector3<float> aNormal = Vector3<float>(0.f, 0.f, 0.f),
		Vector2<float> aSpeed = Vector2<float>(0.f, 0.f));

	void Update(float aDeltaTime);
	void Draw();

	Vector3<float> GetPosition();
	void SetPosition(Vector3<float> aPosition);

	Vector4<float> GetColour();
	void SetColour(Vector4<float> someColours);

	Vector3<float> GetNormal();
	void SetNormal(Vector3<float> aNormal);

private:
	void PerformMovement(float aDeltaTime);

	const WorldSpace * myLocalSpace;
	
	DX2D::CSprite * mySprite;
	Vector3<float> myPosition;
	Vector3f myNormal;
	Vector4f myColour;
	Vector2<float> mySpeed;
};
