#include "stdafx.h"
#include "UseWheelOption.h"
#include <CollisionManager/CollisionManager.h>

UseWheelOption::UseWheelOption(const BaseTriggerCollider * const aTriggerCollider)
{
	myTriggerColliderToAdd = aTriggerCollider;
	
}

UseWheelOption::~UseWheelOption()
{
}

void UseWheelOption::OnMouseClickEvent()
{
	
	CollisionManager::AddATriggerCollider(*myTriggerColliderToAdd);
	
}
