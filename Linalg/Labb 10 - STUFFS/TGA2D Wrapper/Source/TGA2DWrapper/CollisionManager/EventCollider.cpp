#include "EventCollider.h"

EventCollider::EventCollider(const BaseCollisionShape * const aCollisionShape, Event * const aEvent)
{
	myCollider = aCollisionShape;
	myEvent = aEvent;
}
EventCollider::~EventCollider()
{

}
