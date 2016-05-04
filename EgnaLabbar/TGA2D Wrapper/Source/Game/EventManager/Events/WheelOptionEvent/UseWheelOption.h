#pragma once
#include "../Event.h"

class BaseTriggerCollider;

class UseWheelOption : public Event
{
public:
	UseWheelOption(const BaseTriggerCollider * const aTriggerCollider);
	~UseWheelOption();

	virtual void OnMouseClickEvent() override;

private:
	const BaseTriggerCollider * myTriggerColliderToAdd;
	bool myImUsed;
};

