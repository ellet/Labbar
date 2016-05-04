#pragma once
#include "BaseMouseAction.h"
#include "../../../CollisionManager/CollisionShapes/PointShape.h"
#include "../../../CollisionManager/TriggerColliders/OnMouseClickTriggerCollider.h"

class ClickOnObject : public BaseMouseAction
{
public:
	ClickOnObject();
	~ClickOnObject();

	void virtual DoOnRelease() override;

protected:
	PointShape myPointShape;
	OnMouseClickTriggerCollider * myTriggerCollider;
};

