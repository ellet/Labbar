#include "BaseTriggerCollider.h"


BaseTriggerCollider::~BaseTriggerCollider()
{
}

BaseTriggerCollider::BaseTriggerCollider(const BaseCollisionShape & aCollisionShape)
{
	myShape = &aCollisionShape;
}