#include "stdafx.h"
#include "DoUseOnObject.h"
#include "../../Object/Object.h"


DoUseOnObject::DoUseOnObject()
{
	myObjectToDoUseOn = nullptr;
}


DoUseOnObject::~DoUseOnObject()
{
}

void DoUseOnObject::OnMouseClickEvent()
{
	myObjectToDoUseOn->TriggerOnUse();
}