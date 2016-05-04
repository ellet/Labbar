#pragma once



class BaseCollisionShape;
struct EventCollider;
class Event;

class BaseTriggerCollider
{
public:
	BaseTriggerCollider(const BaseCollisionShape & aCollisionShape);
	virtual ~BaseTriggerCollider();

	virtual void TriggerEvent(const EventCollider & aEventToTrigger) const = 0;

	inline const BaseCollisionShape & GetCollisionShape() const;
	inline void SetCollisionShape(const BaseCollisionShape & aCollisionShape);

protected:
	const BaseCollisionShape * myShape;
};

const BaseCollisionShape & BaseTriggerCollider::GetCollisionShape() const
{
	return (*myShape);
}

void BaseTriggerCollider::SetCollisionShape(const BaseCollisionShape & aCollisionShape)
{
	myShape = &aCollisionShape;
}