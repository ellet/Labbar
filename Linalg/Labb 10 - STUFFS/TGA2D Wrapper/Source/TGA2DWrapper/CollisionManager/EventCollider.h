#pragma once
#include "CollisionShapes\BaseCollisionShape.h"
//#include "../../Game/EventManager/Events/Event.h"

class Event;

struct EventCollider
{
public:
	EventCollider(const BaseCollisionShape * const aCollisionShape, Event * const aEvent);
	~EventCollider();

	const BaseCollisionShape * myCollider;
	Event * myEvent;	
};