#include "stdafx.h"
#include "EnemyComponent.h"
#include "Game\Component\Health\HealthComponent.h"
#include "..\Engine\Engine\Component\Collider\CollisionEvent.h"
#include "..\Health\ObjectOutOfHealthMessage.h"
#include "..\Engine\Engine\GameObject\GameObject.h"
#include "..\Shooting\Projectiles\ShotComponent.h"
#include "..\Engine\Engine\Physics\CollisionData.h"
#include "..\Engine\Engine\ParticleSystem\ParticleComponent.h"
#include "..\Engine\Engine\Component\Collider\TriggerCollisionEvent.h"


EnemyComponent::EnemyComponent()
{
}


EnemyComponent::~EnemyComponent()
{
}

void EnemyComponent::Initialize()
{
	myObject->AddEventSubscriber(SB::EventSubscriber<SB::TriggerCollisionEvent>::GetTypeIndex(), SB::EventSubscriber<SB::TriggerCollisionEvent>::GetInstanceIndex());
	myObject->AddEventSubscriber(SB::EventSubscriber<ObjectOutOfHealthMessage>::GetTypeIndex(), SB::EventSubscriber<ObjectOutOfHealthMessage>::GetInstanceIndex());
}

void EnemyComponent::TakeDamage(const float aDamageAmount)
{
	myObject->GetComponent<HealthComponent>()->RemoveHealth(aDamageAmount);
}

void EnemyComponent::RecieveEvent(const ObjectOutOfHealthMessage & aEvent)
{
	GraphicExplosion(myObject->GetWorldPosition());
	myObject->Remove();
}

void EnemyComponent::RecieveEvent(const SB::TriggerCollisionEvent & aEvent)
{
	if (aEvent.myGameObject->GetComponentCount<ShotComponent>() > 0)
	{
		const float Damage = aEvent.myGameObject->GetComponent<ShotComponent>()->GetDamage();

		TakeDamage(Damage);
	}
}

void EnemyComponent::ToJson() const
{
	SB::JsonSerializer &serializer = SB::Engine::GetJsonSerializer();
	serializer.WriteObject("properties");
	serializer.StepOut();
	serializer.WriteNode("type", "EnemyComponent");
}

void EnemyComponent::GraphicExplosion(const SB::Vector3f & aPosition) const
{
	{
		SB::ObjectPtr tempInpactParticles = GetGameObject().GetScene().CreateGameObject("PARICLUS");
		tempInpactParticles->SetPosition(aPosition);

		SB::ComponentPtr<SB::ParticleComponent> particleees = tempInpactParticles->CreateComponent<SB::ParticleComponent>();
		particleees->SetEmitter("ExplosionComponentSmoke", false);

		tempInpactParticles->Initialize();
	}
	{
		SB::ObjectPtr tempInpactParticles = GetGameObject().GetScene().CreateGameObject("PARICLUSFIRE");
		tempInpactParticles->SetPosition(aPosition);

		SB::ComponentPtr<SB::ParticleComponent> particleees = tempInpactParticles->CreateComponent<SB::ParticleComponent>();
		particleees->SetEmitter("ExplosionComponentFire", false);

		tempInpactParticles->Initialize();
	}
}
