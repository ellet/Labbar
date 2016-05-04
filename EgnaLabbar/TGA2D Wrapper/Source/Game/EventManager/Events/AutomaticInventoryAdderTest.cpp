#include "stdafx.h"
#include "AutomaticInventoryAdderTest.h"
#include "PickUpEvent.h"
#include "../../Inventory/Inventory.h"
#include "../../Player/Player.h"
#include <Vectors\Vector.h>

#include <iostream>

AutomaticInventoryAdderTest::AutomaticInventoryAdderTest()
{
	myTimeElapsed = 0.f;
	myName = "AutomaticInventoryAdderTest";
	myActiveEvents.Init(2);
	Object *test = new Object();
	std::string name = "Test Object";
	test->Init(name);
//	myActiveEvents.Add(new PickUpEvent(new Inventory(),test, test, true));
	Vector2f v = Vector2f::Zero;
	myActiveEvents.Add(new ChangeLevelEvent(*new std::string("RandomName"), *new Player(), v));
}


AutomaticInventoryAdderTest::~AutomaticInventoryAdderTest()
{
}

bool AutomaticInventoryAdderTest::Update(const float aDeltaTime)
{
	myTimeElapsed += aDeltaTime;

	if (myTimeElapsed > 2.f)
	{
		std::cout << "Time elapsed > 2.f seconds! AutomaticInventoryAdderTest" << std::endl;
		for (unsigned short i = 0; i < myActiveEvents.Size(); i++)
		{
			myActiveEvents[i]->OneShotEvent();
		}
		myIsActive = false;
	}

	return myIsActive;
}