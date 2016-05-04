#include "WheelElementalOption.h"
#include "../../../Game/EventManager/Events/UseMagicOnObject.h"
#include "../../CollisionManager/EventCollider.h"
#include "../../CollisionManager/CollisionManager.h"

WheelElementalOption::WheelElementalOption(const eElementType aElementType)
{
	//myTriggerPosition = PointShape(Vector2f::Zero);
	//myTriggerCollider = new OnMouseClickTriggerCollider(myTriggerPosition);
	myOnTriggeredEvent = new UseMagicOnObject(aElementType);

	myCollisionShape = BoxShape(GetPosition(), Vector2f(50.f, 50.f));
	myEventCollider = new EventCollider(&myCollisionShape, myOnTriggeredEvent, nullptr, enumMouseStates::eClickOnStuffMode);

	myIsActivated = false;
}

WheelElementalOption::~WheelElementalOption()
{

}

void WheelElementalOption::Update(Object * aObjectPointer)
{
	if (myIsActivated == true)
	{
		myEventCollider->myObject = aObjectPointer;
		dynamic_cast<UseMagicOnObject*>(myOnTriggeredEvent)->SetObjectToDoMagicOn(aObjectPointer);
		CollisionManager::AddAInterfaceCollider(*myEventCollider);

		myEventCollider->DrawCollisionBox();
	}
}
