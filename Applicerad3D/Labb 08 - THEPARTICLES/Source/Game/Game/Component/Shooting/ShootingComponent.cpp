#include "stdafx.h"
#include "ShootingComponent.h"
#include <Engine\GameObject\GameObject.h>
#include <Engine\Scene\Scene.h>
#include "Engine/Model/CubeModel.h"
#include "../Engine/Engine/SoundManager/SoundManger.h"
#include "ShotComponent.h"

ShootingComponent::ShootingComponent()
{
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

void ShootingComponent::Shoot()
{
	std::shared_ptr<SB::GameObject> shot;

	const SB::Vector3f shotSize(0.1f, 0.1f, 1.5f);

	shot = myObject->GetScene().CreateObjectWithModel(myModel, myObject->GetPosition(), shotSize, myObject->GetRotation());

	SB::Engine::GetSoundManager().PostEvent("Play_Derp");

	auto shotComponent = myObject->GetScene().GetComponentFactory<ShotComponent>()->CreateComponent();
	shotComponent->SetSpeed(myObject->GetRotation().GetForward() * 100.f);
	shot->AddComponent(shotComponent);
}

void ShootingComponent::Shoot(const SB::Vector3f & aDirection)
{
	std::shared_ptr<SB::GameObject> shot;

	const SB::Vector3f shotSize(0.1f, 0.1f, 1.5f);

	shot = myObject->GetScene().CreateObjectWithModel(myModel, myObject->GetPosition(), shotSize, myObject->GetRotation());

	SB::Engine::GetSoundManager().PostEvent("Play_Derp");

	auto shotComponent = myObject->GetScene().GetComponentFactory<ShotComponent>()->CreateComponent();
	shotComponent->SetSpeed(aDirection * 100.f);
	shot->AddComponent(shotComponent);
}
