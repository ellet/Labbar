#include "UseHeldObjectOnObject.h"

#include "../../../CollisionManager/CollisionManager.h"
#include "../MouseInput.h"

UseHeldObjectOnObject::UseHeldObjectOnObject()
{
	myTriggerCollider = new OnTriggerCombineObjects(myPointShape);
}


UseHeldObjectOnObject::~UseHeldObjectOnObject()
{
}

void UseHeldObjectOnObject::DoOnRelease()
{
	myPointShape = PointShape(MouseInput::GetMousePosition());
	if (myTriggerCollider != nullptr)
	{
		delete myTriggerCollider;
		myTriggerCollider = nullptr;
	}
	myTriggerCollider = new OnTriggerCombineObjects(myPointShape);

	CollisionManager::AddATriggerCollider(*myTriggerCollider);
}
