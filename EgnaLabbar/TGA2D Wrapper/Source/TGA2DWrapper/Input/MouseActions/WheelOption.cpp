//#include "stdafx.h"
#include "WheelOption.h"

#include "../../../Game/EventManager/Events/WheelOptionEvent/UseWheelOption.h"
#include "../../CollisionManager/TriggerColliders/OnMouseClickTriggerCollider.h"
#include "../../CollisionManager/EventCollider.h"
#include "../../CollisionManager/CollisionManager.h"

#include "../../../Game/EventManager/Events/DoUseOnObject.h"

#include "../MouseInput/MouseStates.h"
#include "../MouseInput/MouseInput.h"

WheelOption::WheelOption()
{
	

	/*myTriggerPosition = PointShape(Vector2f::Zero);
	myTriggerCollider = new OnMouseClickTriggerCollider(myTriggerPosition);
	myOnTriggeredEvent = new UseWheelOption(myTriggerCollider);

	myCollisionShape = BoxShape(GetPosition(), Vector2f(50.f, 50.f));
	myEventCollider = new EventCollider(&myCollisionShape, myOnTriggeredEvent, nullptr, enumMouseStates::eClickOnStuffMode);

	myIsActivated = false;*/

	myOnTriggeredEvent = new DoUseOnObject();

	myCollisionShape = BoxShape(GetPosition(), Vector2f(50.f, 50.f));
	myEventCollider = new EventCollider(&myCollisionShape, myOnTriggeredEvent, nullptr, enumMouseStates::eClickOnStuffMode);

	myIsActivated = false;
}


WheelOption::~WheelOption()
{
}

void WheelOption::Update(Object * aObjectPointer)
{
	if (myIsActivated == true)
	{
		myEventCollider->myObject = aObjectPointer;
		dynamic_cast<DoUseOnObject*>(myOnTriggeredEvent)->SetObjectToDoUseOn(aObjectPointer);
		CollisionManager::AddAInterfaceCollider(*myEventCollider);

		myEventCollider->DrawCollisionBox();
	}
}
