#include "OnMouseHoverTriggerCollider.h"
#include "../EventCollider.h"
#include "../../Input/MouseInput/MouseInput.h"
#include "../../Input/MouseInput/MouseStates.h"



OnMouseHoverTriggerCollider::~OnMouseHoverTriggerCollider()
{
}

void OnMouseHoverTriggerCollider::TriggerEvent(const EventCollider & aEventToTrigger) const
{
	if (aEventToTrigger.myMouseHoverType != enumMouseStates::enumlength)
	{
		MouseInput::SetMouseState(aEventToTrigger.myMouseHoverType);
		MouseInput::MouseCollided();


		if (MouseInput::GetWheelState() == false)
		{
			if (aEventToTrigger.myMouseHoverType == enumMouseStates::eActivateWheel)
			{
				MouseInput::SetObjectRefrenceOnWheel(aEventToTrigger.myObject);
			}
		}
	}
}
