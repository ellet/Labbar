#pragma once
#include "../CommonUtilities/Vectors/Vector.h"
#include "../Game/BaseGameStructure/Rendering/WorldSpace.h"


class BaseGameObject;

class DotGameObject
{
public:
	DotGameObject();
	~DotGameObject();

	virtual void Init(Vector3<float> aPosition, const WorldSpace * aWorldSpace = nullptr, const char * aFilePath = "sprites/DotFORGUBBEWITHHAT.png");

	Vector3<float> GetPosition();

	void SetPosition(Vector3<float> aPosition);

	//void inline SetDotShouldRender();


private:
	BaseGameObject & GetMyBaseGameObject();

	size_t myBaseGameObjectIndex;
};

//inline void DotGameObject::SetDotShouldRender()
//{
//	GetMyBaseGameObject().ActiveRenderThisFrame();
//}