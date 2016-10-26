#include "stdafx.h"
#include "ShotComponent.h"
#include <Engine\GameObject\GameObject.h>
#include "Engine\ParticleSystem\ParticleComponent.h"
#include "..\Engine\Engine\Component\Collider\CollisionEvent.h"
#include "..\Engine\Engine\Physics\CollisionData.h"

ShotComponent::ShotComponent()
{
	myAge = 0.f;
	mySpeed = SB::Vector3f::Zero;
	myDamage = 0.f;
}

void ShotComponent::SetSpeed(const SB::Vector3f & aSpeed)
{
	mySpeed = aSpeed;
	myHasHit = false;
}

ShotComponent::~ShotComponent()
{

}

void ShotComponent::RecieveEvent(const SB::CollisionEvent & aEvent)
{
	CreateInpactParticles(aEvent.myCollisionData->myCollisionPoint);
	myObject->Remove();
}

void ShotComponent::Update(const SB::Time & aDeltaTime)
{

	myAge += aDeltaTime;

	if (myAge.InSeconds() >= 10.f)
	{
		// Engine::GetLogger().LogInfo("myAge{0}", myAge.InSeconds());
		myObject->Remove();
	}
}

void ShotComponent::Initialize()
{
	myObject->AddEventSubscriber(SB::EventSubscriber<SB::CollisionEvent>::GetTypeIndex(), SB::EventSubscriber<SB::CollisionEvent>::GetInstanceIndex());
}

void ShotComponent::CreateInpactParticles(const SB::Vector3f & aPosition)
{
	SB::ObjectPtr tempInpactParticles = GetGameObject().GetScene().CreateGameObject("PARICLUS");
	tempInpactParticles->SetPosition(aPosition);

	SB::ComponentPtr<SB::ParticleComponent> particleees = tempInpactParticles->CreateComponent<SB::ParticleComponent>();

	SB::ParticleSettings tempSettings;

	tempSettings.myAmountOfParticles = 100;
	tempSettings.myStartColor = SB::Vector4f::One;
	tempSettings.myEndColor = SB::Vector4f::One;
	tempSettings.myMinMaxVelocityX = SB::Vector2f(-1.f, 1.f);
	tempSettings.myMinMaxVelocityY = SB::Vector2f(-1.f, 1.f);
	tempSettings.myMinMaxVelocityZ = SB::Vector2f(-1.f, 1.f);
	tempSettings.myMinMaxLifeTime = SB::Vector2f(5.f, 5.f);
	tempSettings.myMinMaxSize = SB::Vector2f(0.01f, 0.1f);
	tempSettings.myEndSizeInPercent = 0.1f;
	tempSettings.myEmitCoolDown = 0.02f;

	tempSettings.myStartColor.x = 1.f;
	tempSettings.myStartColor.y = 0.f;
	tempSettings.myStartColor.z = 0.f;
	tempSettings.myStartColor.w = 1.f;

	tempSettings.myEndColor.x = 1.f;
	tempSettings.myEndColor.y = 1.f;
	tempSettings.myEndColor.z = 0.f;
	tempSettings.myEndColor.w = 1.f;

	particleees->SetSettings(tempSettings);

	tempInpactParticles->Initialize();

	particleees->SpawnParticles();
}
