#include "stdafx.h"
#include "ShotComponent.h"
#include <Engine\GameObject\GameObject.h>
#include "Engine\ParticleSystem\ParticleComponent.h"
#include "..\Engine\Engine\Component\Collider\CollisionEvent.h"
#include "..\Engine\Engine\Physics\CollisionData.h"
#include "..\Engine\Engine\Component\Collider\TriggerCollisionEvent.h"
#include "ShotHitEvent.h"

ShotComponent::ShotComponent()
{
	myAge = 0.f;
	mySpeed = SB::Vector3f::Zero;
	myDamage = 0.f;
	myLifeTime = 10.f;
}

void ShotComponent::SetSpeed(const SB::Vector3f & aSpeed)
{
	mySpeed = aSpeed;
	myHasHit = false;
}

ShotComponent::~ShotComponent()
{
}

void ShotComponent::RecieveEvent(const SB::TriggerCollisionEvent & aEvent)
{
	if (myObject->IsRemoved() == true)
	{
		return;
	}

	SB::Vector3f tempLengthDifference = aEvent.mySphereCollider->GetPosition() - GetGameObject().GetPosition();
	SB::Vector3f tempPoint = aEvent.mySphereCollider->GetPosition() - tempLengthDifference.GetNormalized() * aEvent.mySphereCollider->GetRadius();

	
	myShooterParent->TriggerEvent(ShotHitEvent(*aEvent.myGameObject));

	
 	CreateImpactParticles(tempPoint);
	myObject->Remove();
}


void ShotComponent::RecieveEvent(const SB::EndOfFrameMessage & aEvent)
{
	if (myObject->IsRemoved() == true)
	{
		myShooterParent = nullptr;
	}
}

void ShotComponent::Update(const SB::Time & aDeltaTime)
{
	myAge += aDeltaTime;

	if (myAge.InSeconds() >= myLifeTime)
	{
		myObject->Remove();
	}
}

void ShotComponent::SetParentShooter(const SB::ObjectPtr aShooter)
{
	myShooterParent = aShooter;
}

const SB::ObjectPtr ShotComponent::GetParentShooter() const
{
	return myShooterParent;
}

void ShotComponent::Initialize()
{
	myObject->AddEventSubscriber(SB::EventSubscriber<SB::TriggerCollisionEvent>::GetTypeIndex(), SB::EventSubscriber<SB::TriggerCollisionEvent>::GetInstanceIndex());
}

void ShotComponent::OnRemoved()
{
	//myShooterParent = nullptr;
}

void ShotComponent::CreateImpactParticles(const SB::Vector3f & aPosition)
{
	{
		SB::ObjectPtr tempInpactParticles = GetGameObject().GetScene().CreateGameObject("PARICLUS");
		tempInpactParticles->SetPosition(aPosition);

		SB::ComponentPtr<SB::ParticleComponent> particleees = tempInpactParticles->CreateComponent<SB::ParticleComponent>();
		particleees->SetEmitter("GatlingGunFireSparks", false);

		tempInpactParticles->Initialize();
	}
	{
		SB::ObjectPtr tempInpactParticles = GetGameObject().GetScene().CreateGameObject("PARICLUSFIRE");
		tempInpactParticles->SetPosition(aPosition);

		SB::ComponentPtr<SB::ParticleComponent> particleees = tempInpactParticles->CreateComponent<SB::ParticleComponent>();
		particleees->SetEmitter("GatlingGunFireExplosion", false);

		tempInpactParticles->Initialize();
	}
}
