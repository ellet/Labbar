#include "ClickForNextText.h"

#include "../../../../Game/EventManager/Events/NextTextEvent.h"

ClickForNextText::ClickForNextText()
{
}


ClickForNextText::~ClickForNextText()
{
}

void ClickForNextText::DoOnRelease()
{
	NextTextEvent temp;

	temp.OneShotEvent();
}
