#include "stdafx.h"
#include "TestObject.h"
#include <CollisionManager/CollisionManager.h> 
#include <CollisionManager/CollisionData/CollisionData.h>
#include <CollisionManager/CollisionShapes/CircleShape.h>
#include <CollisionManager/CollisionShapes/LineShape.h>

const Vector2f gravitation = Vector2f(0.f, 500.82f);

TestObject::TestObject()
{
}


TestObject::~TestObject()
{
}

void TestObject::Init(const Vector2f & aPosition, const Vector2f & aSpeed)
{
	LoadSprite("Sprites/palm.dds");
	SetPosition(aPosition);
	mySpeed = aSpeed;
	myCollisionShape = SweptCircle(myPosition, Vector2f::One, 16.f);
	SetCollisionData(&myCollisionShape);
	myPreviousPosition = myPosition;
}

void TestObject::OnCollision(const CollisionData & aCollisonData)
{
	myPosition = myPreviousPosition;
	//mySpeed = -mySpeed;

	LineShape collidedWithLine = *dynamic_cast<LineShape*>(aCollisonData.myCollisionShape);

	Vector2f lineNormal = collidedWithLine.GetNormal();

	mySpeed = mySpeed - lineNormal * ((lineNormal.Dot(mySpeed)) * 2);
	
	mySpeed *= 0.95f;
}

void TestObject::MoveObject(const float aDeltaTime)
{
	myPreviousPosition = myPosition;
	myPosition += mySpeed * aDeltaTime;
	UpdateCollisionBox(myPreviousPosition);
}

void TestObject::ApplyGravitation(const float aDeltaTime)
{
	mySpeed += gravitation * aDeltaTime;
}

void TestObject::UpdateCollisionBox(Vector2f aPreviousPosition)
{
	myCollisionShape.ChangePosition(aPreviousPosition, myPosition);
}

void TestObject::Update(const float aDeltaTime)
{
	ApplyGravitation(aDeltaTime);
	MoveObject(aDeltaTime);
	CollisionManager::AddCollisionData(*myCollisionData);
}

