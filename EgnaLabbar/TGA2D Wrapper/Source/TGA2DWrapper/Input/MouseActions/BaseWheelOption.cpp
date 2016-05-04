#include "BaseWheelOption.h"

#include "../../../Game/EventManager/Events/WheelOptionEvent/UseWheelOption.h"
#include "../../CollisionManager/TriggerColliders/OnMouseClickTriggerCollider.h"
#include "../../CollisionManager/EventCollider.h"
#include "../../CollisionManager/CollisionManager.h"

#include "../MouseInput/MouseStates.h"

BaseWheelOption::BaseWheelOption()
{
	SetPosition(Vector2f(0.f, 0.f));
	LoadSprite("Sprites/palm.dds");

	bool myIsActivated = false;

	myOnTriggeredEvent = nullptr;

	myEventCollider = nullptr;
	myTriggerCollider = nullptr;

	SetPivot(Vector2f(0.5f, 0.5f));

	SetRenderPriority(3000.f);
}


BaseWheelOption::~BaseWheelOption()
{
}

void BaseWheelOption::Update(Object * aObjectPointer)
{
	if (myIsActivated == true)
	{
		myEventCollider->myObject = aObjectPointer;
		CollisionManager::AddAInterfaceCollider(*myEventCollider);

		myEventCollider->DrawCollisionBox();
	}
}

void BaseWheelOption::Draw() const
{
	if (myIsActivated == true)
	{
		BaseGameObject::Draw();
	}
}

void BaseWheelOption::SetWheelSprite(std::string &aFilePath)
{
	LoadSprite(aFilePath);
}
