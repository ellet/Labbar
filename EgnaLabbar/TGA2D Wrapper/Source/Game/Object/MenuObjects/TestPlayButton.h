#pragma once

#include <BaseClasses/BaseGameObject/BaseGameObject.h>
#include <Intersection/Intersection2D.h>
#include "../../EventManager/Events/OnClickEvent.h"
#include "../../EventManager/Events/ChangeGameStateEvent.h"
#include <CollisionManager/CollisionShapes/BoxShape.h>

class TestPlayButton : public BaseGameObject
{
public:
	TestPlayButton();
	~TestPlayButton();


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

	ChangeGameStateEvent * myFirstEvent;
	OnClickEvent myEvent;

	bool myHasCollided;
};

