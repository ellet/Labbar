#pragma once
#include "BaseMouseAction.h"
#include "../../../CollisionManager/CollisionShapes/PointShape.h"
#include "../../../CollisionManager/TriggerColliders/OnTriggerCombineObjects.h"

class UseHeldObjectOnObject : public BaseMouseAction
{
public:
	UseHeldObjectOnObject();
	~UseHeldObjectOnObject();

	void virtual DoOnRelease() override;

private:
	PointShape myPointShape;
	OnTriggerCombineObjects* myTriggerCollider;
};

