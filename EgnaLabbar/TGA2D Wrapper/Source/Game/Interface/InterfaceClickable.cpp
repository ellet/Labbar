#include "stdafx.h"
#include "InterfaceClickable.h"


InterfaceClickable::InterfaceClickable()
{
	myActiveEvents.Init(20);
}


InterfaceClickable::~InterfaceClickable()
{
	myActiveEvents.DeleteAll();
}

void InterfaceClickable::OnMouseClickEvent()
{
	for (int i = 0; i < static_cast<int>(myActiveEvents.Size()); i++)
	{
		myActiveEvents[static_cast<unsigned short>(i)]->OnMouseClickEvent();
	}
}

void InterfaceClickable::AddEvent(Event *aEvent)
{
	myActiveEvents.Add(aEvent);
}

