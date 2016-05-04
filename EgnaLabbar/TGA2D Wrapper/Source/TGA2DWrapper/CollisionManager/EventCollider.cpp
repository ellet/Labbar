#include "EventCollider.h"
#include "CollisionShapes/BaseCollisionShape.h"

EventCollider::EventCollider(BaseCollisionShape * const aCollisionShape, Event * const aEvent, Object* aObjectPointer, const enumMouseStates aMouseState)
{
	myCollider = aCollisionShape;
	myEvent = aEvent;

	myMouseHoverType = aMouseState;
	myObject = aObjectPointer;
}
EventCollider::~EventCollider()
{

}

void EventCollider::ChangePosition(const Vector2f & aPosition)
{
	myCollider->ChangePosition(aPosition);
}

void EventCollider::DrawCollisionBox()
{
	myCollider->DrawCollisionBox();
}