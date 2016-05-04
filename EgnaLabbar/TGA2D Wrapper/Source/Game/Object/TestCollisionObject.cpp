#include "stdafx.h"
#include "TestCollisionObject.h"
#include <tga2d\engine.h>
#include <InputWrapper\InputWrapper.h>
#include <CollisionManager/EventCollider.h>
#include "../Game/Player/Player.h"
#include "../../TGA2DWrapper/CollisionManager/CollisionShapes/BoxShape.h"
#include <CollisionManager/CollisionManager.h>



TestCollisionObject::TestCollisionObject()
{
	
}


TestCollisionObject::~TestCollisionObject()
{
}

void TestCollisionObject::Inut()
{
	myHasCollided = false;
	
	myBox.SetPositionAndSize(GetPosition(), GetSize() * 100);	
	Vector2f v = Vector2f::Zero;
	myFirstEvent = new ChangeLevelEvent(*new std::string("RandomName"), *new Player(), v);

	myEvent.AddEvent(myFirstEvent);

	BoxShape shape(myBox.myMainPoint, myBox.myExtents);

	myCollisionBox = shape;

	myEventCollider = new EventCollider(&myCollisionBox, &myEvent);
}

void TestCollisionObject::CollisionReset()
{
	if (myHasCollided == true)
	{
		myHasCollided = false;
		SetColor(Vector4f::One);
	}
}

void TestCollisionObject::Collided()
{
	if (myHasCollided == false)
	{
		myHasCollided = true;
		SetColor(Vector4f(0.5f, 0.5f, 0.5f, 1));
	}
}

void TestCollisionObject::Update(const float aDeltaTime)
{
	(aDeltaTime);

	CollisionManager::AddAEventCollider(*myEventCollider);
}

