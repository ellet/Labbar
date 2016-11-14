#include "stdafx.h"
#include "EnemyMineComponent.h"

#include "Game\Component\Health\HealthComponent.h"
#include "..\Engine\Engine\Component\Collider\CollisionEvent.h"
#include "..\Engine\Engine\Component\Collider\ColliderComponent.h"
#include "../Engine/Engine/Component/Collider/RenderColliderComponent.h"
#include "..\Health\ObjectOutOfHealthMessage.h"
#include "..\Engine\Engine\GameObject\GameObject.h"
#include "..\Shooting\Projectiles\ShotComponent.h"
#include "..\Engine\Engine\Physics\CollisionData.h"
#include "..\Engine\Engine\ParticleSystem\ParticleComponent.h"
#include "..\Engine\Engine\Component\Collider\TriggerCollisionEvent.h"
#include "Game\Component\Enemy\ExplosionComponent.h"

EnemyMineComponent::EnemyMineComponent()
{
	myExplosionData = new ExplosionData();
}


EnemyMineComponent::~EnemyMineComponent()
{
	delete myExplosionData;
	myExplosionData = nullptr;
}

void EnemyMineComponent::Initialize()
{
	myObject->AddEventSubscriber(SB::EventSubscriber<SB::TriggerCollisionEvent>::GetTypeIndex(), SB::EventSubscriber<SB::TriggerCollisionEvent>::GetInstanceIndex());
	myObject->AddEventSubscriber(SB::EventSubscriber<ObjectOutOfHealthMessage>::GetTypeIndex(), SB::EventSubscriber<ObjectOutOfHealthMessage>::GetInstanceIndex());
}

void EnemyMineComponent::RecieveEvent(const ObjectOutOfHealthMessage & aEvent)
{
	//Create MineExplosion Object
	SB::ObjectPtr explosion = myObject->GetScene().CreateGameObject("MineExplosion");

	explosion->SetPosition(myObject->GetWorldPosition());
	explosion->CreateComponent<ExplosionComponent>()->SetExplosionData(*myExplosionData);
	explosion->CreateComponent<SB::ColliderComponent>()->SetRadius(1.0f);
	explosion->GetComponent<SB::ColliderComponent>()->SetColliderLayerID(CollisionFilter::eEnemy);
	explosion->GetComponent<SB::ColliderComponent>()->SetCollisionFilter(CollisionFilter::ePlayer | CollisionFilter::eEnemy);
	explosion->GetComponent<SB::ColliderComponent>()->SetIsTrigger();
	explosion->CreateComponent<SB::RenderColliderComponent>();
	explosion->Initialize();
	
	myObject->Remove();
}

void EnemyMineComponent::RecieveEvent(const SB::TriggerCollisionEvent & aEvent)
{
	if (aEvent.myGameObject->GetComponentCount<ShotComponent>() > 0)
	{
		const float Damage = aEvent.myGameObject->GetComponent<ShotComponent>()->GetDamage();

		GetGameObject().GetComponent<HealthComponent>()->RemoveHealth(Damage);
	}
}

void EnemyMineComponent::LoadData(SB::DataNode aProperties)
{
	myExplosionData->myExplosionDamage = aProperties["explosionDamage"].GetFloat();
	myExplosionData->myMaxRadius = aProperties["maxExplosionRadius"].GetFloat();
	myExplosionData->myLifeTime = aProperties["lifetime"].GetFloat();
}

void EnemyMineComponent::ToJson() const
{
	SB::JsonSerializer& serializer = SB::Engine::GetJsonSerializer();
	serializer.WriteObject("properties");

	serializer.WriteNode("explosionDamage", myExplosionData->myExplosionDamage);
	serializer.WriteNode("maxExplosionRadius", myExplosionData->myMaxRadius);
	serializer.WriteNode("lifetime", myExplosionData->myLifeTime);

	serializer.StepOut();
	serializer.WriteNode("type", "EnemyMineComponent");
}
