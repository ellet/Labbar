#include "ExamineWheelOption.h"
#include "../../../Game/EventManager/Events/ExamineObject.h"
#include "../../CollisionManager/EventCollider.h"
#include "../../CollisionManager/CollisionManager.h"

ExamineWheelOption::ExamineWheelOption()
{
	myOnTriggeredEvent = new ExamineObject();

	myCollisionShape = BoxShape(GetPosition(), Vector2f(50.f, 50.f));
	myEventCollider = new EventCollider(&myCollisionShape, myOnTriggeredEvent, nullptr, enumMouseStates::eClickOnStuffMode);

	myIsActivated = true;
}


ExamineWheelOption::~ExamineWheelOption()
{
}

void ExamineWheelOption::Update(Object * aObjectPointer)
{
	myEventCollider->myObject = aObjectPointer;
	dynamic_cast<ExamineObject*>(myEventCollider->myEvent)->SetObjectToExamine(aObjectPointer);
	CollisionManager::AddAInterfaceCollider(*myEventCollider);

	myEventCollider->DrawCollisionBox();
}
