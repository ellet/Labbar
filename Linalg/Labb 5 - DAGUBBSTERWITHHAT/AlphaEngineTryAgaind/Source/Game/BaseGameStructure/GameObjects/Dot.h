#pragma once
#include "../CommonUtilities/Vectors/Vector.h"

class BaseGameObject;
class WorldSpace;


class DotGameObject
{
public:
	DotGameObject();
	~DotGameObject();

	void Init(Vector2<float> aPosition, WorldSpace * aWorldSpace = nullptr);

	Vector2<float> GetPosition();

	void SetPosition(Vector2<float> aPosition);

private:
	BaseGameObject & GetMyBaseGameObject();

	size_t myBaseGameObjectIndex;
};

