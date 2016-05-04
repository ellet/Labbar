#include "stdafx.h"
#include "UseMagicOnObject.h"
#include <DLDebug/DL_Debug.h>
#include "../../Object/Object.h"


UseMagicOnObject::UseMagicOnObject(const eElementType aElementType)
{
	myMagicType = aElementType;
	myObjectToDoMagicOn = nullptr;
}

UseMagicOnObject::~UseMagicOnObject()
{
}

void UseMagicOnObject::OnMouseClickEvent()
{
	DL_ASSERT(myObjectToDoMagicOn != nullptr, "Object to do magic on is nullptr");
	myObjectToDoMagicOn->TriggerElementEvent(myMagicType);
}

