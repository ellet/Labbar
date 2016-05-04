#pragma once
#include "../CommonUtilities/Vectors/Vector.h"
#include "../Game/BaseGameStructure/Rendering/WorldSpace.h"


class BaseGameObject;

class DotGameObject
{
public:
	DotGameObject();
	~DotGameObject();

	void Init(Vector2<float> aPosition, const WorldSpace * aWorldSpace = nullptr, const char * aFilePath = "sprites/DotFORGUBBEWITHHAT.png");

	Vector2<float> GetPosition();

	void SetPosition(Vector2<float> aPosition);



private:
	BaseGameObject & GetMyBaseGameObject();

	size_t myBaseGameObjectIndex;
};

