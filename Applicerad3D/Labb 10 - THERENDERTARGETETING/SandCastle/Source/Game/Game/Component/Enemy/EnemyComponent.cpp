#include "stdafx.h"
#include "EnemyComponent.h"
#include "Game\Component\Health\HealthComponent.h"
#include "..\Engine\Engine\Component\Collider\CollisionEvent.h"
#include "..\Health\ObjectOutOfHealthMessage.h"
#include "..\Engine\Engine\GameObject\GameObject.h"
#include "..\Shooting\ShotComponent.h"
#include "..\Engine\Engine\Physics\CollisionData.h"
#include "..\Engine\Engine\ParticleSystem\ParticleComponent.h"


EnemyComponent::EnemyComponent()
{
}


EnemyComponent::~EnemyComponent()
{
}

void EnemyComponent::Initialize()
{
	myObject->AddEventSubscriber(SB::EventSubscriber<SB::CollisionEvent>::GetTypeIndex(), SB::EventSubscriber<SB::CollisionEvent>::GetInstanceIndex());
	myObject->AddEventSubscriber(SB::EventSubscriber<ObjectOutOfHealthMessage>::GetTypeIndex(), SB::EventSubscriber<ObjectOutOfHealthMessage>::GetInstanceIndex());
}

void EnemyComponent::RecieveEvent(const ObjectOutOfHealthMessage & aEvent)
{
	myObject->Remove();
}

void EnemyComponent::RecieveEvent(const SB::CollisionEvent & aEvent)
{
	if (aEvent.myCollisionData->myGameObject->GetComponentCount<ShotComponent>() > 0)
	{
		const float Damage = aEvent.myCollisionData->myGameObject->GetComponent<ShotComponent>()->GetDamage();

		myObject->GetComponent<HealthComponent>()->RemoveHealth(Damage);
	}
}
