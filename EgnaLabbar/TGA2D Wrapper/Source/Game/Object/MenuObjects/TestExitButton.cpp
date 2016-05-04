#include "stdafx.h"
#include "TestExitButton.h"
#include <tga2d\engine.h>
#include <InputWrapper\InputWrapper.h>
#include <CollisionManager/EventCollider.h>
#include <CollisionManager/CollisionShapes/BoxShape.h>
#include <CollisionManager/CollisionManager.h>


TestExitButton::TestExitButton()
{
}


TestExitButton::~TestExitButton()
{
}

void TestExitButton::Update(const float aDeltaTime)
{
	(aDeltaTime);

	CollisionManager::AddAEventCollider(*myEventCollider);

	myEventCollider->DrawCollisionBox();
}

void TestExitButton::Inut()
{
	LoadSprite("Sprites/menuExitTemp.dds");

	myBox.SetPositionAndSize(GetPosition(), GetSize() * 100);

	myFirstEvent = new ShutdownEvent();

	myEvent.AddEvent(myFirstEvent);

	BoxShape shape(myBox.myMainPoint, myBox.myExtents);

	myCollisionBox = shape;

	myEventCollider = new EventCollider(&myCollisionBox, &myEvent, nullptr, enumMouseStates::eClickOnStuffMode);
}
