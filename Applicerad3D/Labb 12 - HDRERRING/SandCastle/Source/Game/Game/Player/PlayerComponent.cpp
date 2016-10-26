#include "stdafx.h"
#include "PlayerComponent.h"
#include "Engine/Component/Collider/CollisionEvent.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/Physics/CollisionData.h"
#include "Engine/ParticleSystem/ParticleComponent.h"
#include "Game/Component/Health/HealthComponent.h"
#include "Game/Component/Shooting/ShotComponent.h"
#include "Game/Component/Health/ObjectOutOfHealthMessage.h"
#include "Game/Player/PlayerMessages.h"

PlayerComponent::PlayerComponent()
{
}


PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Initialize()
{
	myObject->AddEventSubscriber(SB::EventSubscriber<SB::CollisionEvent>::GetTypeIndex(), SB::EventSubscriber<SB::CollisionEvent>::GetInstanceIndex());
	myObject->AddEventSubscriber(SB::EventSubscriber<ObjectOutOfHealthMessage>::GetTypeIndex(), SB::EventSubscriber<ObjectOutOfHealthMessage>::GetInstanceIndex());
}

void PlayerComponent::RecieveEvent(const ObjectOutOfHealthMessage & aEvent)
{
	//myObject->Remove();
}

void PlayerComponent::RecieveEvent(const SB::CollisionEvent & aEvent)
{
	if (aEvent.myCollisionData->myGameObject->GetComponentCount<ShotComponent>() > 0)
	{
		const float Damage = aEvent.myCollisionData->myGameObject->GetComponent<ShotComponent>()->GetDamage();

		myObject->GetComponent<HealthComponent>()->RemoveHealth(Damage);
		
		SB::PostMaster::Post<PlayerHealthChangedMessage>(PlayerHealthChangedMessage(myObject->GetComponent<HealthComponent>()->GetHealth()));
	}
}
