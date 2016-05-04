#pragma once

#include <BaseClasses/BaseGameObject/BaseGameObject.h>
#include <Intersection/Intersection2D.h>
#include "../../EventManager/Events/OnClickEvent.h"
#include "../../EventManager/Events/ShutdownEvent.h"
#include <CollisionManager/CollisionShapes/BoxShape.h>

class TestExitButton : public BaseGameObject
{
public:
	TestExitButton();
	~TestExitButton();


	void Update(const float aDeltaTime);
	void Inut();

	const BoxShape & GetCollisionBox()
	{
		myBox.SetPosition(GetPosition());
		return myCollisionBox;
	}

private:
	Intersection2D::AABB2D myBox;
	BoxShape myCollisionBox;

	EventCollider * myEventCollider;

	ShutdownEvent * myFirstEvent;
	OnClickEvent myEvent;

	bool myHasCollided;
};

