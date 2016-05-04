#include "stdafx.h"
#include "ActivateMagicElementEvent.h"
#include <Input/MouseInput/MouseInput.h>

ActivateMagicElementEvent::ActivateMagicElementEvent(const eElementType aElementType)
{
	myElementType = aElementType;
}

ActivateMagicElementEvent::~ActivateMagicElementEvent()
{
}

void ActivateMagicElementEvent::OneShotEvent()
{
	MouseInput::ActiveElementOnActionWheel(myElementType);
}
