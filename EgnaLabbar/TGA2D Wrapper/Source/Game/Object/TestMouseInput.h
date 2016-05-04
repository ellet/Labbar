#pragma once


#include <BaseClasses/BaseGameObject/BaseGameObject.h>
#include <CollisionManager/TriggerColliders/OnMouseClickTriggerCollider.h>
#include <CollisionManager/CollisionShapes/PointShape.h>

class TestMouseInput : public BaseGameObject
{
public:
	TestMouseInput();
	~TestMouseInput();

	void Inut();

	void Update(const float aDeltaTime);

private:
	PointShape myPointShape;
	OnMouseClickTriggerCollider * myTriggerCollider;
};

