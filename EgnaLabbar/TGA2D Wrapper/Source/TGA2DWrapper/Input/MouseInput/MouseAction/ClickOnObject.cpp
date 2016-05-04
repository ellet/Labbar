#include "ClickOnObject.h"

#include "../../../CollisionManager/CollisionManager.h"
#include "../MouseInput.h"

ClickOnObject::ClickOnObject()
{
	myTriggerCollider = new OnMouseClickTriggerCollider(myPointShape);
}


ClickOnObject::~ClickOnObject()
{
	delete myTriggerCollider;
	myTriggerCollider = nullptr;
}

void ClickOnObject::DoOnRelease()
{
	myPointShape = PointShape(MouseInput::GetMousePosition());
	if (myTriggerCollider != nullptr)
	{
		delete myTriggerCollider;
		myTriggerCollider = nullptr;
	}
	myTriggerCollider = new OnMouseClickTriggerCollider(myPointShape);

	CollisionManager::AddATriggerCollider(*myTriggerCollider);
}