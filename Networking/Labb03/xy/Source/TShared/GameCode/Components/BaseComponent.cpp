#include "stdafx.h"
#include "BaseComponent.h"
#include "GameCode/GameObject/GameObject.h"


unsigned int CBaseComponent::myID = 0;

void CBaseComponent::BroadcastMessage(CComponentMessageBase* aMessage)
{
	myOwner->BroadCastMessage(aMessage);
}

