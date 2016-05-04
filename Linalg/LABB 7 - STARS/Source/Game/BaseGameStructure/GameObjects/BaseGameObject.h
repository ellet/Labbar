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

	void Init(const char* aFilePath, const WorldSpace * aWorldSpace = nullptr, Vector3<float> aPosition = Vector3<float>(0.f, 0.f, 0.f), Vector2<float> aSpeed = Vector2<float>(0.f, 0.f));

	void Update(float aDeltaTime);
	void Draw();

	Vector3<float> GetPosition();
	void SetPosition(Vector3<float> aPosition);

private:
	void PerformMovement(float aDeltaTime);

	const WorldSpace * myLocalSpace;
	
	DX2D::CSprite * mySprite;
	Vector3<float> myPosition;
	Vector2<float> mySpeed;
};
