#include "stdafx.h"
#include "GameLuaSubscription.h"
#include <Engine\GameObject\GameObject.h>
#include <Engine\Component\Collider\CollisionEvent.h>
#include "GameLuaComponent.h"
#include "..\Objective\ObjectiveMessages.h"
#include "Game\Objective\Objective.h"

GameLuaSubscription::GameLuaSubscription(GameLuaComponent &aLuaComponent) :myLuaComponent(aLuaComponent)
{
	myLuaComponent.GetGameObject().AddEventSubscriber(SB::EventSubscriber<SB::TriggerCollisionEvent>::GetTypeIndex(), EventSubscriber<SB::TriggerCollisionEvent>::GetInstanceIndex());
	myLuaComponent.GetGameObject().AddEventSubscriber(SB::EventSubscriber<SB::ObjectiveStateChangedMessage>::GetTypeIndex(), EventSubscriber<SB::ObjectiveStateChangedMessage>::GetInstanceIndex());
}

GameLuaSubscription::~GameLuaSubscription()
{	
}

void GameLuaSubscription::RecieveEvent(const SB::TriggerCollisionEvent & aEvent)
{
	myLuaComponent.ReceiveLuaEvent("OnTrigger", aEvent.myGameObject->GetIdentifier());
}

void GameLuaSubscription::RecieveEvent(const SB::ObjectiveStateChangedMessage & aEvent)
{
	switch (aEvent.myState)
	{
	default:
		break;
	case SB::eObjectiveState::eStarted:
		myLuaComponent.ReceiveLuaEvent("ObjectiveStartedEvent", aEvent.myObjective->GetIdentity());
		break;
	case SB::eObjectiveState::eEnded:
		myLuaComponent.ReceiveLuaEvent("ObjectiveCompleteEvent", aEvent.myObjective->GetIdentity());
		break;
	}
}
