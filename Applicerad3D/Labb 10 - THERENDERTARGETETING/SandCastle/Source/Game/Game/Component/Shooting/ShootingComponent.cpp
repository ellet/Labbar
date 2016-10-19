#include "stdafx.h"
#include "ShootingComponent.h"
#include <Engine\GameObject\GameObject.h>
#include <Engine\Scene\Scene.h>
#include "Engine/Model/CubeModel.h"
#include "../Engine/Engine/SoundManager/SoundManger.h"
#include "ShotComponent.h"
#include "Engine\Component\Collider\ColliderComponent.h"
#include "Engine\Physics\PhysicsComponent.h"

ShootingComponent::ShootingComponent()
{
	myTimesFired = 0;
}


ShootingComponent::~ShootingComponent()
{
}

void ShootingComponent::Update(const SB::Time &aDeltaTime)
{

}

void ShootingComponent::Initialize()
{
	myModel = std::make_shared<SB::CubeModel>(nullptr);
}

int ShootingComponent::GetTimesFired() const
{
	return myTimesFired;
}

void ShootingComponent::Shoot()
{
	Shoot(myObject->GetRotation().GetForward());
	myTimesFired++;

}

void ShootingComponent::Shoot(const SB::Vector3f & aDirection)
{
	myTimesFired++;
	SB::ObjectPtr shot;

	const SB::Vector3f shotSize = SB::Vector3f(0.1f, 0.1f, 1.5f) * 2.f;

	SB::Engine::GetSoundManager().PostEvent("Play_Derp");

	shot = myObject->GetScene().CreateObjectWithModel("Shot", myModel, myObject->GetPosition(), shotSize, myObject->GetRotation());
	//shot->CreateComponent<ShotComponent>()->SetSpeed(aDirection * 100.f);
	shot->CreateComponent<SB::ColliderComponent>();
	shot->CreateComponent<SB::PhysicsComponent>();

	shot->Initialize();
}
