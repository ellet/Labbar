#include "stdafx.h"
#include "TestPlayButton.h"
#include <tga2d\engine.h>
#include <InputWrapper\InputWrapper.h>
#include <CollisionManager/EventCollider.h>
#include <CollisionManager/CollisionShapes/BoxShape.h>
#include <CollisionManager/CollisionManager.h>


TestPlayButton::TestPlayButton()
{
}


TestPlayButton::~TestPlayButton()
{
}

void TestPlayButton::Update(const float aDeltaTime)
{
	(aDeltaTime);

	CollisionManager::AddAEventCollider(*myEventCollider);

	myEventCollider->DrawCollisionBox();
}

void TestPlayButton::Inut()
{
	LoadSprite("Sprites/menutemp.dds");

	myBox.SetPositionAndSize(GetPosition(), GetSize() * 100);

	myFirstEvent = new ChangeGameStateEvent(enumGameStates::eTestMainLoop);

	myEvent.AddEvent(myFirstEvent);

	BoxShape shape(myBox.myMainPoint, myBox.myExtents);

	myCollisionBox = shape;

	myEventCollider = new EventCollider(&myCollisionBox, &myEvent, nullptr, enumMouseStates::eClickOnStuffMode);
}
