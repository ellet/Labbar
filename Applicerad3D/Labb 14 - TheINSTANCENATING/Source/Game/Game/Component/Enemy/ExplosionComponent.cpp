#include "stdafx.h"
#include "ExplosionComponent.h"
#include "Engine\Component\Collider\TriggerCollisionEvent.h"
#include "..\Engine\Engine\Component\Collider\ColliderComponent.h"
#include "..\Engine\Engine\CollisionHandling\ColliderData.h"
#include "..\Health\HealthComponent.h"
#include "..\Engine\Engine\ParticleSystem\ParticleComponent.h"

ExplosionComponent::ExplosionComponent()
{
	myExplosionData.myLifeTime = 0.0f;
	myExplosionData.myExplosionDamage = 0.0f;
	myExplosionData.myMaxRadius = 0.0f;
	myCurrentLifeTime = myExplosionData.myLifeTime;
}


ExplosionComponent::~ExplosionComponent()
{
}


void ExplosionComponent::LoadData(SB::DataNode aProperties)
{
	ExplosionData data;
	data.myExplosionDamage = aProperties["explosionDamage"].GetFloat();
	data.myLifeTime = aProperties["lifeTime"].GetFloat();
	data.myMaxRadius = aProperties["maxRadius"].GetFloat();

	if (aProperties.HasMember("currentLifeTime") == true)
	{
		myCurrentLifeTime = aProperties["currentLifeTime"].GetFloat();
	}
}

void ExplosionComponent::ToJson() const
{
	SB::JsonSerializer& serializer = SB::Engine::GetJsonSerializer();
	serializer.WriteObject("properties");

	serializer.WriteNode("explosionDamage", myExplosionData.myExplosionDamage);
	serializer.WriteNode("lifeTime", myExplosionData.myLifeTime);
	serializer.WriteNode("maxRadius", myExplosionData.myMaxRadius);
	serializer.WriteNode("currentLifeTime", myCurrentLifeTime);

	serializer.StepOut();
	serializer.WriteNode("type", "ExplosionComponent");
}


void ExplosionComponent::Update(const SB::Time & aDeltaTime)
{
	if (myCurrentLifeTime <= 0.f)
	{
		for (unsigned short i = 0; i < myNearbyObjects.Size(); i++)
		{
			if (myNearbyObjects[i]->GetComponent<HealthComponent>() != nullptr)
			{
				myNearbyObjects[i]->GetComponent<HealthComponent>()->GetGameObject().GetComponent<HealthComponent>()->RemoveHealth(myExplosionData.myExplosionDamage);
			}
		}
		myObject->Remove();
	}
	myObject->GetComponent<SB::ColliderComponent>()->SetRadius(45.f * (1.0f - (myCurrentLifeTime / myExplosionData.myLifeTime)));
	myCurrentLifeTime -= aDeltaTime.InSeconds();
	myNearbyObjects.RemoveAll();
}
void ExplosionComponent::Initialize()
{
	myExplosionData.myMaxRadius = 30.f;
	myExplosionData.myExplosionDamage = 50.f;
	myExplosionData.myLifeTime = .25f;
	myCurrentLifeTime = myExplosionData.myLifeTime;
	myObject->AddEventSubscriber(SB::EventSubscriber<SB::TriggerCollisionEvent>::GetTypeIndex(), SB::EventSubscriber<SB::TriggerCollisionEvent>::GetInstanceIndex());
	GraphicExplosion(myObject->GetWorldPosition());
}

void ExplosionComponent::RecieveEvent(const SB::TriggerCollisionEvent & aEvent)
{
	myNearbyObjects.Add(aEvent.myGameObject);
}

void ExplosionComponent::SetExplosionData(const ExplosionData & aExplosionData)
{
	myExplosionData = aExplosionData;
	myCurrentLifeTime = myExplosionData.myLifeTime;
}

void ExplosionComponent::GraphicExplosion(const SB::Vector3f & aPosition) const
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
