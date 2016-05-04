#pragma once



class BaseCollisionShape;
class Event;

class BaseTriggerCollider
{
public:
	BaseTriggerCollider(const BaseCollisionShape & aCollisionShape);
	virtual ~BaseTriggerCollider();

	virtual void TriggerEvent(Event & aEventToTrigger) const;

	inline const BaseCollisionShape & GetCollisionShape() const;

protected:
	const BaseCollisionShape * myShape;
};

const BaseCollisionShape & BaseTriggerCollider::GetCollisionShape() const
{
	return (*myShape);
}