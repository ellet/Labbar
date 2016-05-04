#include "SetPlayerGotoOnClick.h"

#include "../../../../Game/EventManager/Events/PlayerSetGotoEvent.h"
#include "../../MouseInput/MouseInput.h"

SetPlayerGotoOnClick::SetPlayerGotoOnClick()
{
	myEvent = new PlayerSetGotoEvent(MouseInput::GetMousePosition());
}

SetPlayerGotoOnClick::~SetPlayerGotoOnClick()
{

}

void SetPlayerGotoOnClick::DoOnRelease()
{
	
}

void SetPlayerGotoOnClick::DoOnClick()
{
	
}

void SetPlayerGotoOnClick::DoOnHeld()
{
	if (myEvent != nullptr)
	{
		delete myEvent;
		myEvent = nullptr;
	}

	myEvent = new PlayerSetGotoEvent(MouseInput::GetMousePosition());
	myEvent->OneShotEvent();
}
