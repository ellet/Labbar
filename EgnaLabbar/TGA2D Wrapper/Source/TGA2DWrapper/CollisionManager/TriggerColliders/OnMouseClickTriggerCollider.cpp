#include "OnMouseClickTriggerCollider.h"
#include "../../../Game/EventManager/Events/Event.h"
#include "../EventCollider.h"

OnMouseClickTriggerCollider::~OnMouseClickTriggerCollider()
{
}

void OnMouseClickTriggerCollider::TriggerEvent(const EventCollider & aEventToTrigger) const
{
	aEventToTrigger.myEvent->OnMouseClickEvent();
}
