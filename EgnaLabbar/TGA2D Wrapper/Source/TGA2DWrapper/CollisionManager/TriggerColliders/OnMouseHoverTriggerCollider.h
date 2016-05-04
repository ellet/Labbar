#pragma once
#include "BaseTriggerCollider.h"

class OnMouseHoverTriggerCollider : public BaseTriggerCollider
{
public:
	OnMouseHoverTriggerCollider(const BaseCollisionShape & aCollisionShape) 
		: BaseTriggerCollider(aCollisionShape)
	{};
	~OnMouseHoverTriggerCollider();

	virtual void TriggerEvent(const EventCollider & aEventToTrigger) const override;
};