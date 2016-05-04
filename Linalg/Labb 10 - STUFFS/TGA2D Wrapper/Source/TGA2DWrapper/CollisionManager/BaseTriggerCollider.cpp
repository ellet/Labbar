#include "BaseTriggerCollider.h"
#include "CollisionShapes\BaseCollisionShape.h"
#include "../../Game/EventManager/Events/Event.h"

BaseTriggerCollider::~BaseTriggerCollider()
{
}

void BaseTriggerCollider::TriggerEvent(Event & aEventToTrigger) const
{
	aEventToTrigger.OnMouseClickEvent();
}


BaseTriggerCollider::BaseTriggerCollider(const BaseCollisionShape & aCollisionShape)
{
	myShape = &aCollisionShape;
}