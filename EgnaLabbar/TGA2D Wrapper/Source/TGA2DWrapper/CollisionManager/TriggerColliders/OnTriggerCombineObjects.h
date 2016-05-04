#pragma once
#include "BaseTriggerCollider.h"

class OnTriggerCombineObjects : public BaseTriggerCollider
{
public:
	OnTriggerCombineObjects(const BaseCollisionShape & aCollisionShape)
		: BaseTriggerCollider(aCollisionShape)
	{};
	~OnTriggerCombineObjects();

	virtual void TriggerEvent(const EventCollider & aEventToTrigger) const override;
};

