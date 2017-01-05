#pragma once
#include <Engine\Component\Collider\TriggerCollisionEvent.h>
#include <Engine\GameObject\ObjectEventSystem\EventSubscriber.h>
#include "Game\Objective\ObjectiveMessages.h"
#include <Engine\PostMaster.h>

class GameLuaComponent;

class GameLuaSubscription : 
	//Inheritance of events
	public SB::EventSubscriber<SB::TriggerCollisionEvent>,
	public SB::EventSubscriber<SB::ObjectiveStateChangedMessage>

	//Inheritence of messages
	//public SB::Subscriber<ObjectOutOfHealthMessage>
{
public:
	GameLuaSubscription(GameLuaComponent &aLuaComponent);
	~GameLuaSubscription();

	//Receiving messages

	//Receiving Events
	void RecieveEvent(const SB::TriggerCollisionEvent & aEvent) override;
	void RecieveEvent(const SB::ObjectiveStateChangedMessage & aEvent) override;


private:
	GameLuaComponent &myLuaComponent;
};

