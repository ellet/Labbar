#pragma once
#include "CollisionShapes\BaseCollisionShape.h"
#include "../Input/MouseInput/MouseStates.h"
//#include "../../Game/EventManager/Events/Event.h"

class Event;
class Object;

struct EventCollider
{
public:
	EventCollider(BaseCollisionShape * const aCollisionShape, Event * const aEvent, Object* aObjectPointer = nullptr, const enumMouseStates aMouseState = enumMouseStates::eActivateWheel);
	~EventCollider();
	void ChangePosition(const Vector2f & aPosition);
	void DrawCollisionBox();

	BaseCollisionShape * myCollider;
	enumMouseStates myMouseHoverType;
	Event * myEvent;	
	Object * myObject;
};