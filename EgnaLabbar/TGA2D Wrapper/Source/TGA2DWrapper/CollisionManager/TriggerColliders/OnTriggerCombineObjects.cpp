#include "OnTriggerCombineObjects.h"
#include "../../../Game/Inventory/Inventory.h"
#include "../../Input/MouseInput/MouseInput.h"

#include "../../../Game/EventManager/Events/OnCombineEvent.h"
#include "../../../Game/Object/Object.h"
#include "../../CollisionManager/EventCollider.h"


OnTriggerCombineObjects::~OnTriggerCombineObjects()
{
}

void OnTriggerCombineObjects::TriggerEvent(const EventCollider & aEventToTrigger) const
{
	aEventToTrigger.myEvent->OnCombineWithObjectEvent(MouseInput::GetInventoryPointer().GetSelectedObject()->GetName());
}
