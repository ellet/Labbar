#pragma once


#include <BaseClasses/BaseGameObject/BaseGameObject.h>
#include <Intersection/Intersection2D.h>
#include "../EventManager/Events/OnClickEvent.h"
#include "../Game/EventManager/Events/ChangeLevelEvent.h"
#include "../../TGA2DWrapper/CollisionManager/CollisionShapes/BoxShape.h"

struct EventCollider;

class TestCollisionObject : public BaseGameObject
{
public:
	TestCollisionObject();
	~TestCollisionObject();

	void Inut();

	void Update(const float aDeltaTime);

	const BoxShape & GetCollisionBox()
	{
		myBox.SetPosition(GetPosition());
		return myCollisionBox;
	}

	void Collided();
	void CollisionReset();
	

private:
	Intersection2D::AABB2D myBox;
	BoxShape myCollisionBox;

	EventCollider * myEventCollider;

	ChangeLevelEvent * myFirstEvent;
	OnClickEvent myEvent;

	bool myHasCollided;
	
};