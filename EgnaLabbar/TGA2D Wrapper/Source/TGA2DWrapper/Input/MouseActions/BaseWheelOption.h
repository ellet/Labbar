#pragma once
#include "../../BaseClasses/BaseGameObject/BaseGameObject.h"
#include "../../CollisionManager/CollisionShapes/BoxShape.h"
#include "../../CollisionManager/CollisionShapes/PointShape.h"

struct EventCollider;
class BaseTriggerCollider;
class Event;
class Object;

class BaseWheelOption : public BaseGameObject
{
public:
	BaseWheelOption();
	virtual ~BaseWheelOption();

	inline virtual void SetTriggerPosition(const Vector2f aTriggerPosition);

	inline void SetBoxAndObjectPosition(const Vector2f aColliderPosition);

	inline void ActiveWheelOption();
	inline void DeactiveWheelOption();

	virtual void Update(Object * aObjectPointer);

	virtual void Draw() const override;

	virtual void SetWheelSprite(std::string &aFilePath);

protected:
	bool myIsActivated;

	BoxShape myCollisionShape;

	Event* myOnTriggeredEvent;

	EventCollider *myEventCollider;
	BaseTriggerCollider *myTriggerCollider;

	PointShape myTriggerPosition;
};

inline void BaseWheelOption::SetTriggerPosition(const Vector2f aTriggerPosition)
{
	myTriggerPosition.ChangePosition(aTriggerPosition);
}

inline void BaseWheelOption::SetBoxAndObjectPosition(const Vector2f aColliderPosition)
{
	SetPosition(aColliderPosition);
	myCollisionShape.ChangePosition(aColliderPosition);
}

inline void BaseWheelOption::ActiveWheelOption()
{
	myIsActivated = true;
}

inline void BaseWheelOption::DeactiveWheelOption()
{
	myIsActivated = false;
}