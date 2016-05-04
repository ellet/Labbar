#pragma once
#include "BaseTriggerCollider.h"

class OnMouseClickTriggerCollider : public BaseTriggerCollider
{
public:
	OnMouseClickTriggerCollider(const BaseCollisionShape & aCollisionShape) :
		BaseTriggerCollider(aCollisionShape)
	{}

	virtual ~OnMouseClickTriggerCollider();

	virtual void TriggerEvent(const EventCollider & aEventToTrigger) const override;

};